#include <M5Core2.h>
#include <lvgl.h>
#include "config.h"
extern "C"
{
#include "ui.h"
#include "ui_helpers.h"
}
#include "RGB.h"
//#include <ESP_Color.h>
#include <ColorConverterLib.h>
#include "globals.h"

/*If you want to use the LVGL examples,
  make sure to install the lv_examples Arduino library
  and uncomment the following line.
#include <lv_examples.h>
*/
#define CONFIG_TFT_MISO 38
#define CONFIG_TFT_MOSI 23
#define CONFIG_TFT_SCLK 18
#define CONFIG_TFT_CS 15
#define CONFIG_TFT_DC 0
#define CONFIG_TFT_RST 2
#define CONFIG_TFT_BL DC3
#define TOUCH_CS 5
#define CONFIG_TFT_SPI_READ_FREQ 1

#define TFT_eSPI_TOUCH_EMULATION

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

unsigned long int angle = 0;
//unsigned long oldTimestamp = 0;
//unsigned long timer = 0;

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX = 0, touchY = 0;


    //Event& e = M5.Buttons.event;
    //bool touched = event != oldEvent && (event & (E_RELEASE | E_TOUCH | E_MOVE));
    bool touched = M5.Lcd.getTouch(&touchX, &touchY);
    //bool touched = tft.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        //touchX = event.to.x | event.from.x;
        //touchY = event.to.y | event.from.y;
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        /*Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );*/
    }
}

void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    M5.begin();
    
    M5.Lcd.fillScreen(BLACK);

    //rgb.init();
    //rgb.setColor(30, 30, 30);
    _rgb_init();
    _rgb_set_color(30, 30, 30);
    
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print functionAlways
ready to c for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 1 ); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );


    ui_init();
    loadCredentials();
    bleKeyboard.begin();

    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    M5.update();
    unsigned long timestamp = ntp.getEpoch(); 
    if (timestamp != oldTimestamp) { 
      int progress = (((float)( (timestamp) % 30 ) / 30) ) * 100;
      lv_bar_set_value(ui_otpTimeBar, progress, LV_ANIM_OFF);
      
      if(progress == 0) {
        if(currentCredential.isOTP()) {
          lv_label_set_text(ui_Home_Label1, currentCredential.getSecret().c_str());
        }        
      }

      String batteryText = isCharging() ? String("Pwr") : String((int)getBatteryLevel()) + "%";
      lv_label_set_text(ui_batteryLabel, batteryText.c_str());

      RTC_TimeTypeDef timeStruct;
      RTC_DateTypeDef DateStruct;
      M5.Rtc.GetTime(&timeStruct);
      M5.Rtc.GetDate(&DateStruct);
      bool isDST = false;
      if(DateStruct.Month > 3 and DateStruct.Month < 10) {
        isDST = true;
      }
      //add day check
      uint8_t offsetHours = (timezone + (isDST ? 1 : 0));  
      String datetimeText = String(DateStruct.Date) + "/" + String(DateStruct.Month) + "/" + String(DateStruct.Year).substring(2) + " " + String(timeStruct.Hours + offsetHours) + ":" + String(timeStruct.Minutes) + ":" + String(timeStruct.Seconds);    
      lv_label_set_text(ui_datetimeLabel, datetimeText.c_str());

      
      if(bleKeyboard.isConnected()) {
        lv_obj_set_style_text_color(ui_bluetoothLabel, lv_color_hex(0x008000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
      else {
        lv_obj_set_style_text_color(ui_bluetoothLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
    }

    if(rgbHudEnabled && bleKeyboard.isConnected()) {
      for(int i = 0; i < 10; i++) {
        float hue = ((float) ((angle + 36*i)%361))/360.0; 
        //ESP_Color::Color color = ESP_Color::Color::FromHsv(hue, 1.0, 1.0, 1.0);
        uint8_t r, g, b;
        RGBConverter::HsvToRgb(hue, 1, 1, r, g, b);
        pixels.setPixelColor(i, pixels.Color(r, g, b)); 
      }
      pixels.show();
      angle += 1;
    }
    delay(5);
}

