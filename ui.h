// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: cryptocore

#ifndef _CRYPTOCORE_UI_H
#define _CRYPTOCORE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_Login;
extern lv_obj_t * ui_LoginKeyboardPanel1;
void ui_event_keyboardLogin1(lv_event_t * e);
extern lv_obj_t * ui_keyboardLogin1;
extern lv_obj_t * ui_passwordTextArea;
extern lv_obj_t * ui_loginTitlePanel;
extern lv_obj_t * ui_loginTitle;
void ui_event_Home(lv_event_t * e);
extern lv_obj_t * ui_Home;
extern lv_obj_t * ui_homeTitlePanel;
extern lv_obj_t * ui_datetimeLabel;
extern lv_obj_t * ui_configSwitch;
extern lv_obj_t * ui_bluetoothLabel;
extern lv_obj_t * ui_batteryLabel;
void ui_event_lockButton(lv_event_t * e);
extern lv_obj_t * ui_lockButton;
extern lv_obj_t * ui_bottomPanel;
extern lv_obj_t * ui_otpTimeBar;
extern lv_obj_t * ui_itemsDropdown;
extern lv_obj_t * ui_sendSecretButton;
extern lv_obj_t * ui_Home_Label1;
void ui_event_dropdownChange(lv_event_t * e);
void ui_event_homeButtonPress(lv_event_t * e);

void onKeyboardPressCallback(lv_event_t * e);
void onSwitchPressCallback(lv_event_t * e);
void onDropdownPressCallback(lv_event_t * e);
void onSendSecretPressCallback(lv_event_t * e);
void onLockButtonPressCallback(lv_event_t * e);
void swipeRight();


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
