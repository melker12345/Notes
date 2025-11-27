#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

// ============================================================================
// Phase 1: Configuration & Emulation
// ============================================================================

#define SCREEN_HEIGHT 16
#define SCREEN_WIDTH 64
#define CHAR_WIDTH 1
#define CHAR_HEIGHT 1
#define PIXEL_ON "██"
#define PIXEL_OFF "  "

// Clock speed setting (delay in microseconds per frame)
// Lower values = faster scrolling, Higher values = slower scrolling
// Examples: 100000 = 10 FPS, 50000 = 20 FPS, 33333 = 30 FPS, 16666 = 60 FPS
#define CLOCK_SPEED_US 50000  // Default: 50ms = 20 FPS

// The Emulated Screen Buffer (1 = ON, 0 = OFF)
uint8_t screen_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

// ============================================================================
// Phase 2: Font & Scrolling Logic
// ============================================================================

// 5x7 Font Map - Each character is 5 columns wide, stored as 5 bytes
// Each byte represents one column (8 bits = 8 rows, we use top 7)
// Format: MSB is top row, LSB is bottom row
const uint8_t FONT_5x7[128][5] = {
    [' '] = {0x00, 0x00, 0x00, 0x00, 0x00}, // Space
    ['0'] = {0x3E, 0x51, 0x49, 0x45, 0x3E},
    ['1'] = {0x00, 0x42, 0x7F, 0x40, 0x00},
    ['2'] = {0x42, 0x61, 0x51, 0x49, 0x46},
    ['3'] = {0x21, 0x41, 0x45, 0x4B, 0x31},
    ['4'] = {0x18, 0x14, 0x12, 0x7F, 0x10},
    ['5'] = {0x27, 0x45, 0x45, 0x45, 0x39},
    ['6'] = {0x3C, 0x4A, 0x49, 0x49, 0x30},
    ['7'] = {0x01, 0x71, 0x09, 0x05, 0x03},
    ['8'] = {0x36, 0x49, 0x49, 0x49, 0x36},
    ['9'] = {0x06, 0x49, 0x49, 0x29, 0x1E},
    ['A'] = {0x7C, 0x12, 0x11, 0x12, 0x7C},
    ['B'] = {0x7F, 0x49, 0x49, 0x49, 0x36},
    ['C'] = {0x3E, 0x41, 0x41, 0x41, 0x22},
    ['D'] = {0x7F, 0x41, 0x41, 0x22, 0x1C},
    ['E'] = {0x7F, 0x49, 0x49, 0x49, 0x41},
    ['F'] = {0x7F, 0x09, 0x09, 0x09, 0x01},
    ['G'] = {0x3E, 0x41, 0x49, 0x49, 0x7A},
    ['H'] = {0x7F, 0x08, 0x08, 0x08, 0x7F},
    ['I'] = {0x00, 0x41, 0x7F, 0x41, 0x00},
    ['J'] = {0x20, 0x40, 0x41, 0x3F, 0x01},
    ['K'] = {0x7F, 0x08, 0x14, 0x22, 0x41},
    ['L'] = {0x7F, 0x40, 0x40, 0x40, 0x40},
    ['M'] = {0x7F, 0x02, 0x0C, 0x02, 0x7F},
    ['N'] = {0x7F, 0x04, 0x08, 0x10, 0x7F},
    ['O'] = {0x3E, 0x41, 0x41, 0x41, 0x3E},
    ['P'] = {0x7F, 0x09, 0x09, 0x09, 0x06},
    ['Q'] = {0x3E, 0x41, 0x51, 0x21, 0x5E},
    ['R'] = {0x7F, 0x09, 0x19, 0x29, 0x46},
    ['S'] = {0x46, 0x49, 0x49, 0x49, 0x31},
    ['T'] = {0x01, 0x01, 0x7F, 0x01, 0x01},
    ['U'] = {0x3F, 0x40, 0x40, 0x40, 0x3F},
    ['V'] = {0x1F, 0x20, 0x40, 0x20, 0x1F},
    ['W'] = {0x3F, 0x40, 0x38, 0x40, 0x3F},
    ['X'] = {0x63, 0x14, 0x08, 0x14, 0x63},
    ['Y'] = {0x07, 0x08, 0x70, 0x08, 0x07},
    ['Z'] = {0x61, 0x51, 0x49, 0x45, 0x43},
    ['.'] = {0x00, 0x00, 0x60, 0x60, 0x00},
    [','] = {0x00, 0x00, 0x60, 0x60, 0x00},
    ['+'] = {0x08, 0x08, 0x3E, 0x08, 0x08},
    ['-'] = {0x08, 0x08, 0x08, 0x08, 0x08},
    ['%'] = {0x63, 0x13, 0x08, 0x64, 0x63},
    ['$'] = {0x24, 0x2A, 0x7F, 0x2A, 0x12},
};

// Ticker buffer - large enough to hold scrolling text
#define MAX_TICKER_LENGTH 200
uint8_t ticker_buffer[MAX_TICKER_LENGTH];
int ticker_length = 0;

// Scrolling offset
int scroll_offset = 0;

// Cache for stock data to avoid hitting API on every frame
float cached_change = 0.0f;
time_t last_fetch_time = 0;
#define FETCH_INTERVAL_SECONDS 60  // Fetch new data every 60 seconds

// ============================================================================
// Phase 3: Data Fetching
// ============================================================================

// Stock to display (currently set to TSLA - Tesla)
const char* STOCK_SYMBOL = "TSLA";

// Fetch real stock price change from Yahoo Finance API
float fetch_price_change(const char* ticker) {
    char command[256];
    char response[4096];
    FILE* fp;
    float change = 0.0f;
    
    // Build curl command to fetch stock data from Yahoo Finance
    // Using the quote endpoint which returns JSON
    snprintf(command, sizeof(command), 
             "curl -s 'https://query1.finance.yahoo.com/v8/finance/chart/%s?interval=1d&range=1d' 2>/dev/null",
             ticker);
    
    // Execute curl and read response
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Failed to fetch stock data\n");
        return 0.0f;
    }
    
    // Read the response
    size_t bytes_read = fread(response, 1, sizeof(response) - 1, fp);
    response[bytes_read] = '\0';
    pclose(fp);
    
    // Parse JSON response to extract regularMarketChangePercent
    // The JSON structure: "regularMarketChangePercent":{"raw":1.2345,...}
    char* change_str = strstr(response, "\"regularMarketChangePercent\"");
    if (change_str != NULL) {
        // Find the "raw" value after regularMarketChangePercent
        char* raw_str = strstr(change_str, "\"raw\":");
        if (raw_str != NULL) {
            // Skip past "raw":
            raw_str += 6;
            // Parse the float value
            change = strtof(raw_str, NULL);
            // Convert from decimal (e.g., 0.0123) to percentage (1.23)
            change = change * 100.0f;
        }
    }
    
    // If parsing failed, try alternative method: look for "regularMarketChange"
    if (change == 0.0f) {
        char* change_alt = strstr(response, "\"regularMarketChange\"");
        if (change_alt != NULL) {
            char* raw_str = strstr(change_alt, "\"raw\":");
            if (raw_str != NULL) {
                raw_str += 6;
                float change_value = strtof(raw_str, NULL);
                // Try to find previous close to calculate percentage
                char* prev_close_str = strstr(response, "\"previousClose\"");
                if (prev_close_str != NULL) {
                    char* prev_raw = strstr(prev_close_str, "\"raw\":");
                    if (prev_raw != NULL) {
                        prev_raw += 6;
                        float prev_close = strtof(prev_raw, NULL);
                        if (prev_close > 0) {
                            change = (change_value / prev_close) * 100.0f;
                        }
                    }
                }
            }
        }
    }
    
    return change;
}

// Format stock ticker string (e.g., "TSLA +1.34% ")
void format_ticker_string(char* buffer, size_t size, const char* symbol, float change) {
    char sign = (change >= 0) ? '+' : ' ';
    snprintf(buffer, size, "%s %c%.2f%% ", symbol, sign, change);
}

// ============================================================================
// Display Functions
// ============================================================================

// Clear the screen buffer
void clear_screen() {
    memset(screen_buffer, 0, sizeof(screen_buffer));
}

// Render the screen buffer to terminal
void render_screen() {
    // Move cursor to home position (top-left) without clearing entire screen
    printf("\033[H");
    
    // Print each row
    for (int row = 0; row < SCREEN_HEIGHT; row++) {
        // Print each character height
        for (int ch = 0; ch < CHAR_HEIGHT; ch++) {
            for (int col = 0; col < SCREEN_WIDTH; col++) {
                // Print each character width
                for (int cw = 0; cw < CHAR_WIDTH; cw++) {
                    if (screen_buffer[row][col]) {
                        printf(PIXEL_ON);
                    } else {
                        printf(PIXEL_OFF);
                    }
                }
            }
            // Use carriage return and line feed, or just move to next line
            // Clear the rest of the line to ensure clean overwrite
            printf("\033[K"); // Clear from cursor to end of line
            printf("\n");
        }
    }
    
    // Clear any remaining lines below our display area
    printf("\033[J"); // Clear from cursor to end of screen
    
    fflush(stdout);
}

// ============================================================================
// Font & Scrolling Functions
// ============================================================================

// Generate ticker buffer from string
void generate_ticker_buffer(const char* ticker_string, uint8_t* target_buffer, int* length) {
    int pos = 0;
    int str_len = strlen(ticker_string);
    
    for (int i = 0; i < str_len; i++) {
        unsigned char c = (unsigned char)ticker_string[i];
        
        // Get font pattern for this character
        const uint8_t* font_pattern = FONT_5x7[c < 128 ? c : ' '];
        
        // Copy character columns to buffer
        for (int col = 0; col < 5; col++) {
            if (pos < MAX_TICKER_LENGTH) {
                target_buffer[pos++] = font_pattern[col];
            }
        }
        
        // Add spacing column between characters
        if (pos < MAX_TICKER_LENGTH) {
            target_buffer[pos++] = 0x00;
        }
    }
    
    // Add extra spacing at the end for smooth looping (3 empty columns)
    for (int i = 0; i < 3 && pos < MAX_TICKER_LENGTH; i++) {
        target_buffer[pos++] = 0x00;
    }
    
    *length = pos;
}

// Update screen from ticker buffer with offset
void update_screen(uint8_t* source_buffer, int source_length, int offset, int start_row, int num_rows) {
    for (int col = 0; col < SCREEN_WIDTH; col++) {
        int source_col = (offset + col) % source_length;
        uint8_t column_data = source_buffer[source_col];
        
        // Copy column data to screen buffer rows
        for (int row = 0; row < num_rows && (start_row + row) < SCREEN_HEIGHT; row++) {
            // Extract bit for this row (LSB is top row, MSB is bottom row)
            // This fixes the upside-down text issue
            int bit_pos = row;
            screen_buffer[start_row + row][col] = (column_data >> bit_pos) & 0x01;
        }
    }
}

// ============================================================================
// Main Loop
// ============================================================================

int main() {
    // Initialize screen
    clear_screen();
    
    // Hide cursor for cleaner display
    printf("\033[?25l");
    
    // Stock ticker string
    char ticker_string[64];
    
    printf("Terminal LED Matrix Emulator - Stock Ticker\n");
    printf("Press Ctrl+C to exit\n\n");
    usleep(2000000); // 2 second delay before starting
    
    // Clear the initial messages and move to home
    printf("\033[2J\033[H");
    
    // Main animation loop
    while (1) {
        // Fetch real stock data for Tesla (with caching to avoid API rate limits)
        time_t current_time = time(NULL);
        if (current_time - last_fetch_time >= FETCH_INTERVAL_SECONDS || last_fetch_time == 0) {
            cached_change = fetch_price_change(STOCK_SYMBOL);
            last_fetch_time = current_time;
        }
        
        // Format ticker string
        format_ticker_string(ticker_string, sizeof(ticker_string), 
                           STOCK_SYMBOL, cached_change);
        
        // Generate ticker buffer
        generate_ticker_buffer(ticker_string, ticker_buffer, &ticker_length);
        
        // Clear screen buffer
        clear_screen();
        
        // Update screen with scrolling ticker (centered vertically)
        // Use rows 4-11 (8 rows) to center the 7-row font in the 16-row screen
        update_screen(ticker_buffer, ticker_length, scroll_offset, 4, 7);
        
        // Render to terminal
        render_screen();
        
        // Increment scroll offset
        scroll_offset = (scroll_offset + 1) % (ticker_length > 0 ? ticker_length : 1);
        
        // Delay for animation (controlled by CLOCK_SPEED_US)
        usleep(CLOCK_SPEED_US);
    }
    
    // Show cursor again before exiting
    printf("\033[?25h");
    printf("\033[2J\033[H"); // Clear screen on exit
    
    return 0;
}
