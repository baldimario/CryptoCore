// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: cryptocore

#include "config.h"
//extern "C"
//{
#include "ui.h"
#include "ui_helpers.h"
//}
#include "RGB.h"
//extern char* loginScreen;
//extern char* loginStatus;
#include "globals.h"

void onKeyboardPressCallback(lv_event_t * e)
{
  const char* ta_password = lv_textarea_get_text(ui_passwordTextArea);
  const char* password = PASSWORD;
  
  //rgb.init();
  _rgb_init();
  //if(lv_event_get_code(e) == LV_SYMBOL_NEW_LINE) {
  if(strcmp(ta_password, password) == 0) {
    _rgb_set_color(0, 30, 0);
    delay(250);
    _rgb_set_color(30, 30, 30);
    _ui_screen_change(ui_Home, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0);
    lv_textarea_set_text(ui_passwordTextArea, "");
    rgbHudEnabled = true;
    //loginStatus = "default";
    //loginScreen = "home";
  }
  else {
    const char * empty = "";
    if(strcmp(ta_password, empty) == 0) {
      _rgb_set_color(30, 30, 30);
    }
    else {
      _rgb_set_color(30, 0, 0);
    }
  }
  vibrate(75);
  //}
}

void onSwitchPressCallback(lv_event_t * e)
{
  _rgb_init();
  if(lv_obj_get_state(ui_configSwitch) & LV_STATE_CHECKED) {
    _rgb_set_color(0, 30, 30);
    startWiFi();
    rgbHudEnabled = false;
  }  
  else {
    _rgb_set_color(30, 30, 30);
    stopWiFi();
    rgbHudEnabled = true;
  }
  vibrate(75);
}

void onDropdownPressCallback(lv_event_t * e)
{
  _rgb_init();

  char dropdown_option[100];
  int idx = lv_dropdown_get_selected(ui_itemsDropdown);
  lv_dropdown_get_selected_str(ui_itemsDropdown, dropdown_option, 100);
  Serial.println(idx);
  Serial.println(dropdown_option);
  
  if(credentials[idx].isOTP()) {
    lv_label_set_text(ui_Home_Label1, credentials[idx].getSecret().c_str());
  }
  else {
    lv_label_set_text(ui_Home_Label1, dropdown_option);
  }


  _rgb_set_color(30, 30, 0);
  delay(150);
  _rgb_set_color(30, 30, 30);
  vibrate(75);
}

void onSendSecretPressCallback(lv_event_t * e) {
  int idx = lv_dropdown_get_selected(ui_itemsDropdown);
  Serial.println(credentials[idx].isOTP());
  Serial.println(credentials[idx].getSecret());
  Serial.println(credentials[idx].getName());
  
  vibrate(75);
  bleKeyboard.print(credentials[idx].getSecret() + "\n");
}


void onLockButtonPressCallback(lv_event_t * e) {
  vibrate(75);
  M5.shutdown();
};

void swipeRight() {
  rgbHudEnabled = false;
  _rgb_set_color(30, 30, 30);
}