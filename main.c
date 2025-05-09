#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#define PASSWORD      "1234"
#define FOOTER_LINE_1 "Text can go here"
#define FOOTER_LINE_2 "Written by Michael Toolan"

void get_input(char *buffer, int max_len);
void draw_ui_box(void);
void draw_footer(void);

int main(void) {
    char input[20];

    gfx_Begin();
    gfx_FillScreen(255);           // White background
    gfx_SetTextFGColor(0);         // Black text
    gfx_SetTextBGColor(255);       // White background
    gfx_SetTextScale(1, 1);

    while (true) {
        gfx_FillScreen(255);
        draw_ui_box();
        draw_footer();

        gfx_PrintStringXY("Enter Password:", 50, 70);
        gfx_SetTextXY(50, 90);

        get_input(input, sizeof(input));

        if (strcmp(input, PASSWORD) == 0) {
            gfx_PrintStringXY("Access Granted!", 50, 110);
            break;
        } else {
            gfx_PrintStringXY("Access Denied. Try again.", 50, 110);
            delay(1500);
        }
    }

    delay(1000);
    gfx_End();
    return 0;
}

void get_input(char *buffer, int max_len) {
    int len = 0;
    buffer[0] = '\0';

    while (true) {
        kb_Scan();

        for (int row = 1; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                uint8_t key = 1 << col;
                if (kb_Data[row] & key) {
                    char c = 0;
                    if (row == 2 && col == 1) c = '1';
                    if (row == 2 && col == 2) c = '2';
                    if (row == 2 && col == 3) c = '3';
                    if (row == 3 && col == 1) c = '4';
                    if (row == 3 && col == 2) c = '5';
                    if (row == 3 && col == 3) c = '6';
                    if (row == 4 && col == 1) c = '7';
                    if (row == 4 && col == 2) c = '8';
                    if (row == 4 && col == 3) c = '9';
                    if (row == 5 && col == 2) c = '0';

                    if (c && len < max_len - 1) {
                        buffer[len++] = c;
                        buffer[len] = '\0';
                        gfx_PrintChar(c);
                        delay(150);
                    }
                }
            }
        }

        if (kb_IsDown(kb_KeyEnter)) {
            delay(300);
            break;
        }

        if (kb_IsDown(kb_KeyDel) && len > 0) {
            len--;
            buffer[len] = '\0';
            // redraw input area
            gfx_SetColor(255);
            gfx_FillRectangle(50, 90, 150, 10);
            gfx_SetTextXY(50, 90);
            gfx_SetTextFGColor(0);
            gfx_PrintString(buffer);
            delay(200);
        }
    }
}

void draw_ui_box(void) {
    gfx_SetColor(0);                // Black border
    gfx_Rectangle(40, 50, 240, 80);
}

void draw_footer(void) {
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY(FOOTER_LINE_1, 10, LCD_HEIGHT - 20);
    gfx_PrintStringXY(FOOTER_LINE_2, 10, LCD_HEIGHT - 10);
}
