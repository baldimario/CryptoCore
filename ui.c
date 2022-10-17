// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: cryptocore

#include "config.h"
#include "ui.h"
#include "ui_helpers.h"
//extern char* loginScreen;
//extern char* loginStatus;

///////////////////// VARIABLES ////////////////////
void ui_event_configSwitch(lv_event_t * e);
lv_obj_t * ui_Login;
lv_obj_t * ui_LoginKeyboardPanel1;
void ui_event_keyboardLogin1(lv_event_t * e);
lv_obj_t * ui_keyboardLogin1;
lv_obj_t * ui_passwordTextArea;
lv_obj_t * ui_loginTitlePanel;
lv_obj_t * ui_loginTitle;
void ui_event_Home(lv_event_t * e);
lv_obj_t * ui_Home;
lv_obj_t * ui_homeTitlePanel;
lv_obj_t * ui_datetimeLabel;
lv_obj_t * ui_configSwitch;
lv_obj_t * ui_bluetoothLabel;
lv_obj_t * ui_batteryLabel;
void ui_event_lockButton(lv_event_t * e);
lv_obj_t * ui_lockButton;
lv_obj_t * ui_bottomPanel;
lv_obj_t * ui_otpTimeBar;
lv_obj_t * ui_itemsDropdown;
lv_obj_t * ui_sendSecretButton;
lv_obj_t * ui_Home_Label1;
void ui_event_homeButtonPress(lv_event_t * e);

/*
void onKeyboardPressCallback(lv_event_t * e)
{
  const char* ta_password = lv_textarea_get_text(ui_passwordTextArea);
  const char* password = PASSWORD;

  //if(lv_event_get_code(e) == LV_SYMBOL_NEW_LINE) {
  if(strcmp(ta_password, password) == 0) {
    _ui_screen_change(ui_Home, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0);
    lv_textarea_set_text(ui_passwordTextArea, "");
    //loginStatus = "default";
    //loginScreen = "home";
  }
  //}
}
*/
///////////////////// TEST LVGL SETTINGS ////////////////////

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_configSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        onSwitchPressCallback(e);
    }
}

void ui_event_dropdownChange(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        onDropdownPressCallback(e);
    }
}

void ui_event_homeButtonPress(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        onSendSecretPressCallback(e);
    }
}

void ui_event_keyboardLogin1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        onKeyboardPressCallback(e);
    }
}

void ui_event_Home(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Login, LV_SCR_LOAD_ANIM_OVER_RIGHT, 500, 0);
        swipeRight();
        //loginScreen = "login";
        //loginStatus = "default";
    }
}
void ui_event_lockButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Login, LV_SCR_LOAD_ANIM_OVER_RIGHT, 500, 0);
        onLockButtonPressCallback(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Login_screen_init(void)
{
    ui_Login = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Login, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LoginKeyboardPanel1 = lv_obj_create(ui_Login);
    lv_obj_set_height(ui_LoginKeyboardPanel1, 140);
    lv_obj_set_width(ui_LoginKeyboardPanel1, lv_pct(102));
    lv_obj_set_x(ui_LoginKeyboardPanel1, 0);
    lv_obj_set_y(ui_LoginKeyboardPanel1, 2);
    lv_obj_set_align(ui_LoginKeyboardPanel1, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_LoginKeyboardPanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_LoginKeyboardPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_keyboardLogin1 = lv_keyboard_create(ui_LoginKeyboardPanel1);
    lv_keyboard_set_mode(ui_keyboardLogin1, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_width(ui_keyboardLogin1, 300);
    lv_obj_set_height(ui_keyboardLogin1, 120);
    lv_obj_set_x(ui_keyboardLogin1, 0);
    lv_obj_set_y(ui_keyboardLogin1, 5);

    ui_passwordTextArea = lv_textarea_create(ui_Login);
    lv_obj_set_width(ui_passwordTextArea, lv_pct(90));
    lv_obj_set_height(ui_passwordTextArea, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_passwordTextArea, 0);
    lv_obj_set_y(ui_passwordTextArea, -50);
    lv_obj_set_align(ui_passwordTextArea, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_passwordTextArea, "");
    lv_textarea_set_placeholder_text(ui_passwordTextArea, "Password...");
    lv_textarea_set_password_mode(ui_passwordTextArea, true);
    lv_textarea_set_one_line(ui_passwordTextArea, true);
    lv_obj_set_style_text_align(ui_passwordTextArea, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_passwordTextArea, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_loginTitlePanel = lv_obj_create(ui_Login);
    lv_obj_set_height(ui_loginTitlePanel, 40);
    lv_obj_set_width(ui_loginTitlePanel, lv_pct(100));
    lv_obj_set_align(ui_loginTitlePanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_loginTitlePanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_loginTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_loginTitle = lv_label_create(ui_Login);
    lv_obj_set_width(ui_loginTitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_loginTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_loginTitle, 0);
    lv_obj_set_y(ui_loginTitle, 8);
    lv_obj_set_align(ui_loginTitle, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_loginTitle, "CryptoCore");
    lv_obj_set_style_text_font(ui_loginTitle, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_keyboard_set_textarea(ui_keyboardLogin1, ui_passwordTextArea);
    lv_obj_add_event_cb(ui_keyboardLogin1, ui_event_keyboardLogin1, LV_EVENT_ALL, NULL);

}
void ui_Home_screen_init(void)
{
    ui_Home = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_homeTitlePanel = lv_obj_create(ui_Home);
    lv_obj_set_height(ui_homeTitlePanel, 40);
    lv_obj_set_width(ui_homeTitlePanel, lv_pct(100));
    lv_obj_set_align(ui_homeTitlePanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_homeTitlePanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_homeTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_datetimeLabel = lv_label_create(ui_Home);
    lv_obj_set_width(ui_datetimeLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_datetimeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_datetimeLabel, 10);
    lv_obj_set_y(ui_datetimeLabel, 13);
    lv_label_set_text(ui_datetimeLabel, "13/10/22 15:17:47");
    lv_obj_set_style_text_color(ui_datetimeLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_datetimeLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_configSwitch = lv_switch_create(ui_Home);
    lv_obj_set_width(ui_configSwitch, 50);
    lv_obj_set_height(ui_configSwitch, 25);
    lv_obj_set_x(ui_configSwitch, -85);
    lv_obj_set_y(ui_configSwitch, 8);
    lv_obj_set_align(ui_configSwitch, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(ui_configSwitch, ui_event_configSwitch, LV_EVENT_ALL, NULL);

    ui_bluetoothLabel = lv_label_create(ui_Home);
    lv_obj_set_width(ui_bluetoothLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bluetoothLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_bluetoothLabel, -55);
    lv_obj_set_y(ui_bluetoothLabel, 13);
    lv_obj_set_align(ui_bluetoothLabel, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_bluetoothLabel, "BT");

    ui_batteryLabel = lv_label_create(ui_Home);
    lv_obj_set_width(ui_batteryLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_batteryLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_batteryLabel, -10);
    lv_obj_set_y(ui_batteryLabel, 13);
    lv_obj_set_align(ui_batteryLabel, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_batteryLabel, "100%");

    ui_lockButton = lv_btn_create(ui_Home);
    lv_obj_set_width(ui_lockButton, 40);
    lv_obj_set_height(ui_lockButton, 20);
    lv_obj_set_x(ui_lockButton, -5);
    lv_obj_set_y(ui_lockButton, 10);
    lv_obj_set_align(ui_lockButton, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_lockButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_lockButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_bottomPanel = lv_obj_create(ui_Home);
    lv_obj_set_height(ui_bottomPanel, 30);
    lv_obj_set_width(ui_bottomPanel, lv_pct(101));
    lv_obj_set_x(ui_bottomPanel, 0);
    lv_obj_set_y(ui_bottomPanel, 1);
    lv_obj_set_align(ui_bottomPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_bottomPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_bottomPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_otpTimeBar = lv_bar_create(ui_Home);
    lv_bar_set_value(ui_otpTimeBar, 25, LV_ANIM_OFF);
    lv_obj_set_height(ui_otpTimeBar, 10);
    lv_obj_set_width(ui_otpTimeBar, lv_pct(90));
    lv_obj_set_x(ui_otpTimeBar, 0);
    lv_obj_set_y(ui_otpTimeBar, -10);
    lv_obj_set_align(ui_otpTimeBar, LV_ALIGN_BOTTOM_MID);

    ui_itemsDropdown = lv_dropdown_create(ui_Home);
    lv_dropdown_set_options(ui_itemsDropdown, "");
    lv_obj_set_width(ui_itemsDropdown, lv_pct(90));
    lv_obj_set_height(ui_itemsDropdown, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_itemsDropdown, 0);
    lv_obj_set_y(ui_itemsDropdown, 50);
    lv_obj_set_align(ui_itemsDropdown, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_itemsDropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_add_event_cb(ui_itemsDropdown, ui_event_dropdownChange, LV_EVENT_ALL, NULL);

    ui_sendSecretButton = lv_btn_create(ui_Home);
    lv_obj_set_height(ui_sendSecretButton, 100);
    lv_obj_set_width(ui_sendSecretButton, lv_pct(90));
    lv_obj_set_x(ui_sendSecretButton, 0);
    lv_obj_set_y(ui_sendSecretButton, 100);
    lv_obj_set_align(ui_sendSecretButton, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_sendSecretButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_sendSecretButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_sendSecretButton, ui_event_homeButtonPress, LV_EVENT_ALL, NULL);

    ui_Home_Label1 = lv_label_create(ui_sendSecretButton);
    lv_obj_set_width(ui_Home_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Home_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Home_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Home_Label1, "Type");
    lv_obj_set_style_text_font(ui_Home_Label1, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_lockButton, ui_event_lockButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Home, ui_event_Home, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    //LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Login_screen_init();
    ui_Home_screen_init();
    lv_disp_load_scr(ui_Login);
}
