#pragma once
#include <Windows.h>

// --HMENU id-- //
#define TITLE_ID 0

#define QUIT_BUTTON_ID 1
#define MINIMIZE_BUTTON_ID 2

#define INK_LETTER_BUTTON_ID 3
#define SEND_ID 32

#define S_INITIALIZE_BUTTON_ID 4
#define S_CONNECT_BUTTON_ID 5

#define INVISBLE_TEXTBOX_SUBCLASS_ID 101

#define TIMER_UPDATE_ID 1
// learn about enum

// --Window size-- //

#define SCREEN_WIDTH GetSystemMetrics(SM_CXFULLSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYFULLSCREEN)

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT WINDOW_WIDTH * 0.7

 // --Window Bar Settings-- //
#define TITLE_SIZE WIN_BAR_SIZE * 0.6
#define WIN_BAR_SIZE SCREEN_HEIGHT / 30
#define BAR_MARGIN  5
#define BAR_BUTTON_SIZE  20
#define BORDER_EFFECT_SIZE 4

 // --Ui Settings-- //
#define MARGIN  20
#define SMALL_MARGIN  7.5

#define LETTER_BOX_WIDTH (WINDOW_WIDTH * 0.7) //Letter writing box
#define LETTER_BOX_HEIGHT (WINDOW_HEIGHT * 0.65)

// Most of the ui elements are positioned relative to this

#define LETTER_BOX_RECT_LEFT WINDOW_WIDTH - LETTER_BOX_WIDTH - MARGIN - BAR_MARGIN // Left rect
#define LETTER_BOX_RECT_TOP MARGIN * 2.5										   // Top rect
#define LETTER_BOX_RECT_RIGHT WINDOW_WIDTH - (SMALL_MARGIN * 2)                    // Right rect
#define LETTER_BOX_RECT_BOTTOM WINDOW_HEIGHT - (MARGIN * 3)						   // Bottom rect

#define LETTER_BOX_BORDER_W ((LETTER_BOX_RECT_RIGHT) - (LETTER_BOX_RECT_LEFT))
#define LETTER_BOX_BORDER_H ((LETTER_BOX_RECT_BOTTOM) - (LETTER_BOX_RECT_TOP))
#define LETTER_BOX_CAP 1400 // Max letters in the letter box

// --Button size-- //

#define BUTTON_WIDTH 100 
#define BUTTON_HEIGHT 30

// --Ui Colors-- //


// Normal

#define BACKGROUND_COLOR RGB(159, 123, 89)

// WindowBar Colors
#define WINODW_UI_COLOR RGB(48, 41, 47)

// Letter Colors
#define LETTER_BORDER RGB(50, 0, 0)
#define PAPER_COLOR RGB(234, 180, 100)

// UI Colors
#define UI_BORDER RGB(50, 0, 0)
#define UI_BORDER_SHINE RGB(150, 100, 70)
#define UI_BORDER_SHADOW RGB(100, 50, 50)

// Server Status Colors
#define STATUS_OFFLINE_COLOR RGB(255, 100, 100)
#define STATUS_ONLINE_COLOR RGB(100, 255, 100)
#define STATUS_Server_COLOR RGB(150, 150, 255)

#define DEFULT_BUTTON_COLOR RGB(240, 220, 200)
#define DEFULT_BUTTON_COLOR_PRESSED RGB(200, 200, 255)
#define DEFULT_BUTTON_COLOR_PRESSED_TEXT RGB(255, 255, 255)



// old windows
/*
#define BACKGROUND_COLOR RGB(195,195,195)

// WindowBar Colors
#define WINODW_UI_COLOR RGB(0,0,130)

// Letter Colors
#define LETTER_BORDER RGB(0, 0, 0)
#define PAPER_COLOR RGB(255,255,233)

// UI Colors
#define UI_BORDER RGB(0, 0, 0)
#define UI_BORDER_SHINE RGB(150, 100, 70)
#define UI_BORDER_SHADOW RGB(100, 50, 50)

// Server Status Colors
#define STATUS_OFFLINE_COLOR RGB(255, 100, 100)
#define STATUS_ONLINE_COLOR RGB(100, 255, 100)
#define STATUS_Server_COLOR RGB(150, 150, 255)

#define DEFULT_BUTTON_COLOR RGB(195,195,195)
#define DEFULT_BUTTON_COLOR_PRESSED RGB(200, 200, 255)
#define DEFULT_BUTTON_COLOR_PRESSED_TEXT RGB(255, 255, 255)
*/