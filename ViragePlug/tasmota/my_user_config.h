/*
  my_user_config.h - user specific configuration for Tasmota

  Copyright (C) 2020  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MY_USER_CONFIG_H_
#define _MY_USER_CONFIG_H_

/*********************************************************************************************\
 * This file consists of TWO sections.
 *
 * SECTION 1:
 * The first section contains PARAMETERS overriding flash settings if define CFG_HOLDER is CHANGED.
 * All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
 *   Corresponding MQTT/Serial/Console commands are shown in [brackets]
 *
 * SECTION 2:
 * The second section contains Enabled and Disabled FEATURES allowing different program size.
 *   Changes in this section do NOT need a change of define CFG_HOLDER.
 *
 * ATTENTION:
 * Users are advised to use the user_config_override.h file for most changes.
\*********************************************************************************************/

/*********************************************************************************************\
 * SECTION 1
 * - After initial load any change here only take effect if CFG_HOLDER is changed too
\*********************************************************************************************/

// -- Master parameter control --------------------
#define CFG_HOLDER             4617              // [Reset 1] Change this value (max 32000) to load SECTION1 configuration parameters to flash
                                                 // If following define is disabled it increases configuration corruption detection BUT
                                                 //  it only allows firmware upgrades starting from version 6.6.0.11

// -- Project -------------------------------------
#define PROJECT                "ViragePlug"         // PROJECT is used as the default topic delimiter

// If not selected the default will be SONOFF_BASIC
#define MODULE                 VIRAGE_PLUG  // [Module] Select default module from tasmota_template.h
#ifdef ESP8266
#define FALLBACK_MODULE        VIRAGE_PLUG      // [Module2] Select default module on fast reboot where USER_MODULE is user template
//#define USER_TEMPLATE "{\"NAME\":\"Generic\",\"GPIO\":[255,255,255,255,255,255,255,255,255,255,255,255,255],\"FLAG\":15,\"BASE\":18}"  // [Template] Set JSON template
#endif  // ESP8266
#ifdef ESP32
#define FALLBACK_MODULE        WEMOS             // [Module2] Select default module on fast reboot where USER_MODULE is user template
//#define USER_TEMPLATE "{\"NAME\":\"ESP32-DevKit\",\"GPIO\":[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1],\"FLAG\":0,\"BASE\":1}"  // [Template] Set JSON template
#endif  // ESP32

#define SAVE_DATA              1                 // [SaveData] Save changed parameters to Flash (0 = disable, 1 - 3600 seconds)
#define SAVE_STATE             true              // [SetOption0] Save changed power state to Flash (false = disable, true = enable)
#define BOOT_LOOP_OFFSET       1                 // [SetOption36] Number of boot loops before starting restoring defaults (0 = disable, 1..200 = boot loops offset)

// -- Wifi ----------------------------------------
#define WIFI_IP_ADDRESS        "0.0.0.0"         // [IpAddress1] Set to 0.0.0.0 for using DHCP or enter a static IP address
#define WIFI_GATEWAY           "192.168.1.1"     // [IpAddress2] If not using DHCP set Gateway IP address
#define WIFI_SUBNETMASK        "255.255.255.0"   // [IpAddress3] If not using DHCP set Network mask
#define WIFI_DNS               "192.168.1.1"     // [IpAddress4] If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)

#define STA_SSID1              ""                // [Ssid1] Wifi SSID
#define STA_PASS1              ""                // [Password1] Wifi password
#define STA_SSID2              ""                // [Ssid2] Optional alternate AP Wifi SSID
#define STA_PASS2              ""                // [Password2] Optional alternate AP Wifi password
#define WIFI_AP_PASSPHRASE     ""                // AccessPoint passphrase. For WPA2 min 8 char, for open use "" (max 63 char).
#define WIFI_CONFIG_TOOL       WIFI_MANAGER        // [WifiConfig] Default tool if wifi fails to connect (default option: 4 - WIFI_RETRY)
                                                 // (WIFI_RESTART, WIFI_MANAGER, WIFI_RETRY, WIFI_WAIT, WIFI_SERIAL, WIFI_MANAGER_RESET_ONLY)
                                                 // The configuration can be changed after first setup using WifiConfig 0, 2, 4, 5, 6 and 7.
#define WIFI_ARP_INTERVAL      0                 // [SetOption41] Send gratuitous ARP interval
#define WIFI_SCAN_AT_RESTART   false             // [SetOption56] Scan wifi network at restart for configured AP's
#define WIFI_SCAN_REGULARLY    false             // [SetOption57] Scan wifi network every 44 minutes for configured AP's

// -- Syslog --------------------------------------
#define SYS_LOG_HOST           ""                // [LogHost] (Linux) syslog host
#define SYS_LOG_PORT           514               // [LogPort] default syslog UDP port
#define SYS_LOG_LEVEL          LOG_LEVEL_NONE    // [SysLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#define SERIAL_LOG_LEVEL       LOG_LEVEL_INFO    // [SerialLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#define WEB_LOG_LEVEL          LOG_LEVEL_INFO    // [WebLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#define MQTT_LOG_LEVEL         LOG_LEVEL_NONE    // [MqttLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)

// -- Ota -----------------------------------------
#ifdef ESP8266
#define OTA_URL                ""  // [OtaUrl]
#endif  // ESP8266
#ifdef ESP32
#define OTA_URL                ""  // [OtaUrl]
#endif  // ESP32

// -- MQTT ----------------------------------------
#define MQTT_USE               true              // [SetOption3] Select default MQTT use (false = Off, true = On)

#define MQTT_HOST              "viragehub"                // [MqttHost]
#define MQTT_FINGERPRINT1      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  // [MqttFingerprint1] (auto-learn)
#define MQTT_FINGERPRINT2      0xDA,0x39,0xA3,0xEE,0x5E,0x6B,0x4B,0x0D,0x32,0x55,0xBF,0xEF,0x95,0x60,0x18,0x90,0xAF,0xD8,0x07,0x09  // [MqttFingerprint2] (invalid)
#define MQTT_PORT              1883              // [MqttPort] MQTT port (10123 on CloudMQTT)
#define MQTT_USER              "mqttuser"       // [MqttUser] MQTT user
#define MQTT_PASS              "mqttpass"       // [MqttPassword] MQTT password

#define MQTT_BUTTON_RETAIN     false             // [ButtonRetain] Button may send retain flag (false = off, true = on)
#define MQTT_POWER_RETAIN      false             // [PowerRetain] Power status message may send retain flag (false = off, true = on)
#define MQTT_SWITCH_RETAIN     false             // [SwitchRetain] Switch may send retain flag (false = off, true = on)
#define MQTT_SENSOR_RETAIN     false             // [SensorRetain] Sensor may send retain flag (false = off, true = on)
#define MQTT_NO_HOLD_RETAIN    false             // [SetOption62] Disable retain flag on HOLD messages
#define MQTT_NO_RETAIN         false             // [SetOption104] No Retain - disable all MQTT retained messages, some brokers don't support it: AWS IoT, Losant

#define MQTT_STATUS_OFF        "OFF"             // [StateText1] Command or Status result when turned off (needs to be a string like "0" or "Off")
#define MQTT_STATUS_ON         "ON"              // [StateText2] Command or Status result when turned on (needs to be a string like "1" or "On")
#define MQTT_CMND_TOGGLE       "TOGGLE"          // [StateText3] Command to send when toggling (needs to be a string like "2" or "Toggle")
#define MQTT_CMND_HOLD         "HOLD"            // [StateText4] Command to send when button is kept down for over KEY_HOLD_TIME * 0.1 seconds (needs to be a string like "HOLD")

// -- MQTT topics ---------------------------------
  // Example "tasmota/bedroom/%topic%/%prefix%/" up to 80 characers
#define MQTT_FULLTOPIC         "%prefix%/%topic%/" // [FullTopic] Subscribe and Publish full topic name - Legacy topic

// %prefix% token options
#define SUB_PREFIX             "cmnd"            // [Prefix1] Tasmota devices subscribe to %prefix%/%topic% being SUB_PREFIX/MQTT_TOPIC and SUB_PREFIX/MQTT_GRPTOPIC
#define PUB_PREFIX             "stat"            // [Prefix2] Tasmota devices publish to %prefix%/%topic% being PUB_PREFIX/MQTT_TOPIC
#define PUB_PREFIX2            "tele"            // [Prefix3] Tasmota devices publish telemetry data to %prefix%/%topic% being PUB_PREFIX2/MQTT_TOPIC/UPTIME, POWER and TIME
                                                 //   May be named the same as PUB_PREFIX
// %topic% token options (also ButtonTopic and SwitchTopic)
#define MQTT_TOPIC             PROJECT "_%06X"   // [Topic] unique MQTT device topic including (part of) device MAC address
#define MQTT_GRPTOPIC          "virage"        // [GroupTopic] MQTT Group topic
//#define WIFI_HOSTNAME          PROJECT "_%06X"
#define MQTT_GROUPTOPIC_FORMAT false             // [SetOption75] GroupTopic replaces %topic% (false) or fixed topic cmnd/grouptopic (true)
#define MQTT_BUTTON_TOPIC      "0"               // [ButtonTopic] MQTT button topic, "0" = same as MQTT_TOPIC, set to 'PROJECT "_BTN_%06X"' for unique topic including device MAC address
#define MQTT_SWITCH_TOPIC      "0"               // [SwitchTopic] MQTT button topic, "0" = same as MQTT_TOPIC, set to 'PROJECT "_SW_%06X"' for unique topic including device MAC address
#define MQTT_CLIENT_ID         "DVES_%06X"       // [MqttClient] Also fall back topic using last 6 characters of MAC address or use "DVES_%12X" for complete MAC address

// -- MQTT - Telemetry ----------------------------
#define TELE_PERIOD            300               // [TelePeriod] Telemetry (0 = disable, 10 - 3600 seconds)
#define TELE_ON_POWER          false             // [SetOption59] send tele/STATE together with stat/RESULT (false = Disable, true = Enable)

// -- MQTT - Domoticz -----------------------------
#define DOMOTICZ_UPDATE_TIMER  0                 // [DomoticzUpdateTimer] Send relay status (0 = disable, 1 - 3600 seconds)

// -- MQTT - Home Assistant Discovery -------------
#define HOME_ASSISTANT_DISCOVERY_ENABLE   true  // [SetOption19] Home Assistant Discovery (false = Disable, true = Enable)
#define HASS_AS_LIGHT          false             // [SetOption30] Enforce HAss autodiscovery as light
//#define DEEPSLEEP_LWT_HA_DISCOVERY             // Enable LWT topic and its payloads for read-only sensors (Status sensor not included) and binary_sensors on HAss Discovery (Commented out: all read-only sensors and binary_sensors
                                                 // won't be shown as OFFLINE on Home Assistant when the device is DeepSleeping - NOTE: This is only for read-only sensors and binary_sensors, relays will be shown as OFFLINE)

// -- MQTT - Options ------------------------------
#define MQTT_RESULT_COMMAND    false             // [SetOption4]  Switch between MQTT RESULT or COMMAND
#define MQTT_LWT_MESSAGE       false             // [SetOption10] Switch between MQTT LWT OFFLINE or empty message
#define MQTT_POWER_FORMAT      false             // [SetOption26] Switch between POWER or POWER1 for single power devices
#define MQTT_APPEND_TIMEZONE   false             // [SetOption52] Append timezone to JSON time
#define MQTT_BUTTON_SWITCH_FORCE_LOCAL   false   // [SetOption61] Force local operation when button/switch topic is set (false = off, true = on)
#define MQTT_INDEX_SEPARATOR   false             // [SetOption64] Enable "_" instead of "-" as sensor index separator
#define MQTT_TUYA_RECEIVED     false             // [SetOption66] Enable TuyaMcuReceived messages over Mqtt
#define MQTT_TLS_ENABLED       false             // [SetOption103] Enable TLS mode (requires TLS version)

// -- HTTP ----------------------------------------
#define WEB_SERVER             2                 // [WebServer] Web server (0 = Off, 1 = Start as User, 2 = Start as Admin)
#define WEB_PASSWORD           "admin"                // [WebPassword] Web server Admin mode Password for WEB_USERNAME (empty string = Disable)
#define FRIENDLY_NAME          PROJECT   
#define FRIENDLY_NAME1         "Top Plug"      // [FriendlyName] Friendlyname up to 32 characters used by webpages and Alexa
#define FRIENDLY_NAME2         "Bottom Plug"
#define FRIENDLY_NAME3         "USB Plug"
#define EMULATION              EMUL_NONE         // [Emulation] Select Belkin WeMo (single relay/light) or Hue Bridge emulation (multi relay/light) (EMUL_NONE, EMUL_WEMO or EMUL_HUE)
#define EMULATION_HUE_1ST_GEN  false             // [Emulation] Force SetOption109 1 - if you only have Echo Dot 2nd gen devices
#define CORS_DOMAIN            ""                // [Cors] CORS Domain for preflight requests

// -- HTTP Options --------------------------------
#define GUI_SHOW_HOSTNAME      false             // [SetOption53] Show hostname and IP address in GUI main menu

// -- HTTP GUI Colors -----------------------------
// HTML hex color codes. Only 3 and 6 digit hex string values are supported!! See https://www.w3schools.com/colors/colors_hex.asp
// Light theme - pre v7
// WebColor {"WebColor":["#000","#fff","#f2f2f2","#000","#fff","#000","#fff","#f00","#008000","#fff","#1fa3ec","#0e70a4","#d43535","#931f1f","#47c266","#5aaf6f","#fff","#999","#000"]}
/*
#define COLOR_TEXT                  "#000"       // [WebColor1] Global text color - Black
#define COLOR_BACKGROUND            "#fff"       // [WebColor2] Global background color - White
#define COLOR_FORM                  "#f2f2f2"    // [WebColor3] Form background color - Greyish
#define COLOR_INPUT_TEXT            "#000"       // [WebColor4] Input text color - Black
#define COLOR_INPUT                 "#fff"       // [WebColor5] Input background color - White
#define COLOR_CONSOLE_TEXT          "#000"       // [WebColor6] Console text color - Black
#define COLOR_CONSOLE               "#fff"       // [WebColor7] Console background color - White
#define COLOR_TEXT_WARNING          "#f00"       // [WebColor8] Warning text color - Red
#define COLOR_TEXT_SUCCESS          "#008000"    // [WebColor9] Success text color - Dark lime green
#define COLOR_BUTTON_TEXT           "#fff"       // [WebColor10] Button text color - White
#define COLOR_BUTTON                "#1fa3ec"    // [WebColor11] Button color - Vivid blue
#define COLOR_BUTTON_HOVER          "#0e70a4"    // [WebColor12] Button color when hovered over - Dark blue
#define COLOR_BUTTON_RESET          "#d43535"    // [WebColor13] Restart/Reset/Delete button color - Strong red
#define COLOR_BUTTON_RESET_HOVER    "#931f1f"    // [WebColor14] Restart/Reset/Delete button color when hovered over - Dark red
#define COLOR_BUTTON_SAVE           "#47c266"    // [WebColor15] Save button color - Moderate lime green
#define COLOR_BUTTON_SAVE_HOVER     "#5aaf6f"    // [WebColor16] Save button color when hovered over - Dark moderate lime green
#define COLOR_TIMER_TAB_TEXT        "#fff"       // [WebColor17] Config timer tab text color - White
#define COLOR_TIMER_TAB_BACKGROUND  "#999"       // [WebColor18] Config timer tab background color - Dark gray
#define COLOR_TITLE_TEXT            "#000"       // [WebColor19] Title text color - Whiteish
*/
// Dark theme
// WebColor {"WebColor":["#eaeaea","#252525","#4f4f4f","#000","#ddd","#65c115","#1f1f1f","#ff5661","#008000","#faffff","#1fa3ec","#0e70a4","#d43535","#931f1f","#47c266","#5aaf6f","#faffff","#999","#eaeaea"]}
#define COLOR_TEXT                  "#eaeaea"    // [WebColor1] Global text color - Very light gray
#define COLOR_BACKGROUND            "#100e23"    // [WebColor2] Global background color - Very dark gray (mostly black)
#define COLOR_FORM                  "#100e23"    // [WebColor3] Form background color - Very dark gray
#define COLOR_INPUT_TEXT            "#000"       // [WebColor4] Input text color - Black
#define COLOR_INPUT                 "#ddd"       // [WebColor5] Input background color - Very light gray
#define COLOR_CONSOLE_TEXT          "#65c115"    // [WebColor6] Console text color - Strong Green
#define COLOR_CONSOLE               "#1f1f1f"    // [WebColor7] Console background color - Very dark gray (mostly black)
#define COLOR_TEXT_WARNING          "#ff5661"    // [WebColor8] Warning text color - Brick Red
#define COLOR_TEXT_SUCCESS          "#008000"    // [WebColor9] Success text color - Dark lime green
#define COLOR_BUTTON_TEXT           "#faffff"    // [WebColor10] Button text color - Very pale (mostly white) cyan
#define COLOR_BUTTON                "#1e2848"    // [WebColor11] Button color - Vivid blue
#define COLOR_BUTTON_HOVER          "#171e36"    // [WebColor12] Button color when hovered over - Dark blue
#define COLOR_BUTTON_RESET          "#800000"    // [WebColor13] Restart/Reset/Delete button color - Strong red
#define COLOR_BUTTON_RESET_HOVER    "#4d0000"    // [WebColor14] Restart/Reset/Delete button color when hovered over - Dark red
#define COLOR_BUTTON_SAVE           "#008000"    // [WebColor15] Save button color - Moderate lime green
#define COLOR_BUTTON_SAVE_HOVER     "#004d00"    // [WebColor16] Save button color when hovered over - Dark moderate lime green
#define COLOR_TIMER_TAB_TEXT        "#faffff"    // [WebColor17] Config timer tab text color - Very pale (mostly white) cyan.
#define COLOR_TIMER_TAB_BACKGROUND  "#999"       // [WebColor18] Config timer tab background color - Dark gray
#define COLOR_TITLE_TEXT            "#eaeaea"    // [WebColor19] Title text color - Very light gray

// -- KNX -----------------------------------------
#define KNX_ENABLED            false             // [Knx_Enabled] Enable KNX protocol
#define KNX_ENHANCED           false             // [Knx_Enhanced] Enable KNX Enhanced Mode

// -- mDNS ----------------------------------------
#define MDNS_ENABLED           true             // [SetOption55] Use mDNS (false = Disable, true = Enable)

// -- Time - Up to three NTP servers in your region
#define NTP_SERVER1            "pool.ntp.org"       // [NtpServer1] Select first NTP server by name or IP address (129.250.35.250)
#define NTP_SERVER2            "nl.pool.ntp.org"    // [NtpServer2] Select second NTP server by name or IP address (5.39.184.5)
#define NTP_SERVER3            "0.nl.pool.ntp.org"  // [NtpServer3] Select third NTP server by name or IP address (93.94.224.67)

// -- Time - Start Daylight Saving Time and timezone offset from UTC in minutes
#define TIME_DST_HEMISPHERE    North             // [TimeDst] Hemisphere (0 or North, 1 or South)
#define TIME_DST_WEEK          Last              // Week of month (0 or Last, 1 or First, 2 or Second, 3 or Third, 4 or Fourth)
#define TIME_DST_DAY           Sun               // Day of week (1 or Sun, 2 or Mon, 3 or Tue, 4 or Wed, 5 or Thu, 6 or Fri, 7 or Sat)
#define TIME_DST_MONTH         Mar               // Month (1 or Jan, 2 or Feb, 3 or Mar, 4 or Apr, 5 or May, 6 or Jun, 7 or Jul, 8 or Aug, 9 or Sep, 10 or Oct, 11 or Nov, 12 or Dec)
#define TIME_DST_HOUR          2                 // Hour (0 to 23)
#define TIME_DST_OFFSET        -360           // Offset from UTC in minutes (-780 to +780)

// -- Time - Start Standard Time and timezone offset from UTC in minutes
#define TIME_STD_HEMISPHERE    North             // [TimeStd] Hemisphere (0 or North, 1 or South)
#define TIME_STD_WEEK          Last              // Week of month (0 or Last, 1 or First, 2 or Second, 3 or Third, 4 or Fourth)
#define TIME_STD_DAY           Sun               // Day of week (1 or Sun, 2 or Mon, 3 or Tue, 4 or Wed, 5 or Thu, 6 or Fri, 7 or Sat)
#define TIME_STD_MONTH         Oct               // Month (1 or Jan, 2 or Feb, 3 or Mar, 4 or Apr, 5 or May, 6 or Jun, 7 or Jul, 8 or Aug, 9 or Sep, 10 or Oct, 11 or Nov, 12 or Dec)
#define TIME_STD_HOUR          3                 // Hour (0 to 23)
#define TIME_STD_OFFSET        -300               // Offset from UTC in minutes (-780 to +780)

// -- Location ------------------------------------
#define LATITUDE               45.5017         // [Latitude] Your location to be used with sunrise and sunset
#define LONGITUDE              -73.5673          // [Longitude] Your location to be used with sunrise and sunset

// -- Application ---------------------------------
#define APP_TIMEZONE           -5                 // [Timezone] +1 hour (Amsterdam) (-13 .. 14 = hours from UTC, 99 = use TIME_DST/TIME_STD)
#define APP_LEDSTATE           LED_POWER         // [LedState] Function of led
                                                 //   (LED_OFF, LED_POWER, LED_MQTTSUB, LED_POWER_MQTTSUB, LED_MQTTPUB, LED_POWER_MQTTPUB, LED_MQTT, LED_POWER_MQTT)
#define APP_LEDMASK            0xFFFF            // [LedMask] Assign Relay to Power led (0xFFFF is default)
#define APP_ENABLE_LEDLINK     false             // [SetOption31] Enable link led blinking

#define APP_PULSETIME          0                 // [PulseTime] Time in 0.1 Sec to turn off power for relay 1 (0 = disabled)
#define APP_POWERON_STATE      POWER_ALL_SAVED   // [PowerOnState] Power On Relay state
                                                 //   (POWER_ALL_OFF, POWER_ALL_ON, POWER_ALL_SAVED_TOGGLE, POWER_ALL_SAVED, POWER_ALL_ALWAYS_ON, POWER_ALL_OFF_PULSETIME_ON)
#define APP_BLINKTIME          10                // [BlinkTime] Time in 0.1 Sec to blink/toggle power for relay 1
#define APP_BLINKCOUNT         10                // [BlinkCount] Number of blinks (0 = 32000)

#define APP_NORMAL_SLEEP       false             // [SetOption60] Enable normal sleep instead of dynamic sleep
#define APP_SLEEP              0                 // [Sleep] Sleep time to lower energy consumption (0 = Off, 1 - 250 mSec),
#define PWM_MAX_SLEEP          10                // Sleep will be lowered to this value when light is on, to avoid flickering, and when buzzer is on for better on/off period accuracy

#define KEY_DEBOUNCE_TIME      50                // [ButtonDebounce] Number of mSeconds button press debounce time
#define KEY_HOLD_TIME          20                // [SetOption32] Number of 0.1 seconds to hold Button or external Pushbutton before sending HOLD message
#define KEY_DISABLE_MULTIPRESS false             // [SetOption1]  Disable button multipress
#define KEY_SWAP_DOUBLE_PRESS  false             // [SetOption11] Swap button single and double press functionality
#define KEY_ONLY_SINGLE_PRESS  true             // [SetOption13] Enable only single press to speed up button press recognition

#define SWITCH_DEBOUNCE_TIME   50                // [SwitchDebounce] Number of mSeconds switch press debounce time
#define SWITCH_MODE            TOGGLE            // [SwitchMode] TOGGLE, FOLLOW, FOLLOW_INV, PUSHBUTTON, PUSHBUTTON_INV, PUSHBUTTONHOLD, PUSHBUTTONHOLD_INV, PUSHBUTTON_TOGGLE, TOGGLEMULTI, FOLLOWMULTI, FOLLOWMULTI_INV (the wall switch state)

#define TEMP_CONVERSION        false             // [SetOption8] Return temperature in (false = Celsius or true = Fahrenheit)
#define PRESSURE_CONVERSION    false             // [SetOption24] Return pressure in (false = hPa or true = mmHg)
#define TEMP_RESOLUTION        1                 // [TempRes] Maximum number of decimals (0 - 3) showing sensor Temperature
#define HUMIDITY_RESOLUTION    1                 // [HumRes] Maximum number of decimals (0 - 3) showing sensor Humidity
#define PRESSURE_RESOLUTION    1                 // [PressRes] Maximum number of decimals (0 - 3) showing sensor Pressure
#define ENERGY_RESOLUTION      3                 // [EnergyRes] Maximum number of decimals (0 - 5) showing energy usage in kWh
#define CALC_RESOLUTION        3                 // [CalcRes] Maximum number of decimals (0 - 7) used in commands ADD, SUB, MULT and SCALE

#define APP_FLASH_CYCLE        false             // [SetOption12] Switch between dynamic or fixed slot flash save location
#define APP_NO_RELAY_SCAN      false             // [SetOption63] Don't scan relay power state at restart
#define APP_DISABLE_POWERCYCLE false             // [SetOption65] Disable fast power cycle detection for device reset
#define DEEPSLEEP_BOOTCOUNT    false             // [SetOption76] Enable incrementing bootcount when deepsleep is enabled

#define APP_INTERLOCK_MODE     false             // [Interlock] Relay interlock mode
#define APP_INTERLOCK_GROUP_1  0xFF              // [Interlock] Relay bitmask for interlock group 1 (0xFF if undef)
//#define APP_INTERLOCK_GROUP_2  0x00              // [Interlock] Relay bitmask for interlock group 2 (0x00 if undef)
//#define APP_INTERLOCK_GROUP_3  0x00              // [Interlock] Relay bitmask for interlock group 3 (0x00 if undef)
//#define APP_INTERLOCK_GROUP_4  0x00              // [Interlock] Relay bitmask for interlock group 4 (0x00 if undef)

// -- Lights --------------------------------------
#define WS2812_LEDS            30                // [Pixels] Number of WS2812 LEDs to start with (max is 512)
#define LIGHT_MODE             true              // [SetOption15] Switch between commands PWM or COLOR/DIMMER/CT/CHANNEL
#define LIGHT_CLOCK_DIRECTION  false             // [SetOption16] Switch WS2812 clock between clockwise or counter-clockwise
#define LIGHT_COLOR_RADIX      false             // [SetOption17] Switch between decimal or hexadecimal color output (false = hexadecimal, true = decimal)
#define LIGHT_PAIRS_CO2        false             // [SetOption18] Enable Pair light signal with CO2 sensor
#define LIGHT_POWER_CONTROL    true             // [SetOption20] Enable power control in relation to Dimmer/Color/Ct changes
#define LIGHT_CHANNEL_MODE     false             // [SetOption68] Enable multi-channels PWM instead of Color PWM
#define LIGHT_SLIDER_POWER     false             // [SetOption77] Do not power off if slider moved to far left
#define LIGHT_ALEXA_CT_RANGE   false             // [SetOption82] Reduced CT range for Alexa
#define LIGHT_PWM_CT_MODE      false             // [SetOption92] Set PWM Mode from regular PWM to ColorTemp control (Xiaomi Philips ...) a.k.a. module 48 mode
#define LIGHT_WHITE_BLEND_MODE false             // [SetOption105] White Blend Mode - used to be `RGBWWTable` last value `0`, now deprecated in favor of this option
#define LIGHT_VIRTUAL_CT       false             // [SetOption106] Virtual CT - Creates a virtual White ColorTemp for RGBW lights
#define LIGHT_VIRTUAL_CT_CW    false             // [SetOption107] Virtual CT Channel - signals whether the hardware white is cold CW (true) or warm WW (false)

// -- Energy --------------------------------------
#define ENERGY_VOLTAGE_ALWAYS  false             // [SetOption21] Enable show voltage even if powered off
#define ENERGY_DDS2382_MODE    false             // [SetOption71] Enable DDS2382 different Modbus registers for Active Energy (#6531)
#define ENERGY_HARDWARE_TOTALS false             // [SetOption72] Enable hardware energy total counter as reference (#6561)

// -- Other Options -------------------------------
#define TIMERS_ENABLED         false             // [Timers] Enable Timers
#define RF_DATA_RADIX          false             // [SetOption28] RF receive data format (false = hexadecimal, true = decimal)
#define IR_DATA_RADIX          false             // [SetOption29] IR receive data format (false = hexadecimal, true = decimal)
#define TUYA_SETOPTION_20      true             // [SetOption54] Apply SetOption20 settings to Tuya device
#define IR_ADD_RAW_DATA        false             // [SetOption58] Add IR Raw data to JSON message
#define BUZZER_ENABLE          false             // [SetOption67] Enable buzzer when available
#define DS18X20_PULL_UP        false             // [SetOption74] Enable internal pullup for single DS18x20 sensor
#define COUNTER_RESET          false             // [SetOption79] Enable resetting of counters after telemetry was sent
#define SHUTTER_SUPPORT        false             // [SetOption80] Enable shutter support
#define PCF8574_INVERT_PORTS   false             // [SetOption81] Invert all ports on PCF8574 devices
#define ZIGBEE_FRIENDLY_NAMES  false             // [SetOption83] Enable Zigbee FriendlyNames instead of ShortAddresses when possible
#define ZIGBEE_RMV_ZBRECEIVED  false             // [SetOption100] Remove ZbReceived form JSON message
#define ZIGBEE_INDEX_EP        false             // [SetOption101] Add the source endpoint as suffix to attributes, ex `Power3` instead of `Power` if sent from endpoint 3

/*********************************************************************************************\
 * END OF SECTION 1
 *
 * SECTION 2
 * - Enable a feature by removing both // in front of it
 * - Disable a feature by preceding it with //
\*********************************************************************************************/

// -- Localization --------------------------------
  // If non selected the default en-GB will be used
//#define MY_LANGUAGE            bg_BG           // Bulgarian in Bulgaria
//#define MY_LANGUAGE            cs_CZ           // Czech in Czech
//#define MY_LANGUAGE            de_DE           // German in Germany
//#define MY_LANGUAGE            el_GR           // Greek in Greece
#define MY_LANGUAGE            en_GB           // English in Great Britain. Enabled by Default
//#define MY_LANGUAGE            es_ES           // Spanish in Spain
//#define MY_LANGUAGE            fr_FR           // French in France
//#define MY_LANGUAGE            he_HE           // Hebrew in Israel
//#define MY_LANGUAGE            hu_HU           // Hungarian in Hungary
//#define MY_LANGUAGE            it_IT           // Italian in Italy
//#define MY_LANGUAGE            ko_KO           // Korean in Korea
//#define MY_LANGUAGE            nl_NL           // Dutch in the Netherlands
//#define MY_LANGUAGE            pl_PL           // Polish in Poland
//#define MY_LANGUAGE            pt_BR           // Portuguese in Brazil
//#define MY_LANGUAGE            pt_PT           // Portuguese in Portugal
//#define MY_LANGUAGE            ro_RO           // Romanian in Romania
//#define MY_LANGUAGE            ru_RU           // Russian in Russia
//#define MY_LANGUAGE            sk_SK           // Slovak in Slovakia
//#define MY_LANGUAGE            sv_SE           // Swedish in Sweden
//#define MY_LANGUAGE            tr_TR           // Turkish in Turkey
//#define MY_LANGUAGE            uk_UA           // Ukrainian in Ukraine
//#define MY_LANGUAGE            vi_VN           // Vietnamese in Vietnam
//#define MY_LANGUAGE            zh_CN           // Chinese (Simplified) in China
//#define MY_LANGUAGE            zh_TW           // Chinese (Traditional) in Taiwan

// -- Wifi Config tools ---------------------------
#define WIFI_SOFT_AP_CHANNEL   1                 // Soft Access Point Channel number between 1 and 13 as used by Wifi Manager web GUI

// -- OTA -----------------------------------------
//#define USE_ARDUINO_OTA                          // Add optional support for Arduino OTA (+13k code)

// -- MQTT ----------------------------------------
#define MQTT_LWT_OFFLINE       "Offline"         // MQTT LWT offline topic message
#define MQTT_LWT_ONLINE        "Online"          // MQTT LWT online topic message

#define MQTT_TELE_RETAIN       0                 // Tele messages may send retain flag (0 = off, 1 = on)
#define MQTT_CLEAN_SESSION     1                 // Mqtt clean session connection (0 = No clean session, 1 = Clean session (default))

// -- MQTT - Domoticz -----------------------------
//#define USE_DOMOTICZ                             // Enable Domoticz (+6k code, +0.3k mem)
//  #define DOMOTICZ_IN_TOPIC    "domoticz/in"     // Domoticz Input Topic
//  #define DOMOTICZ_OUT_TOPIC   "domoticz/out"    // Domoticz Output Topic

// -- MQTT - Home Assistant Discovery -------------
#define USE_HOME_ASSISTANT                                   // Enable Home Assistant Discovery Support (+4.1k code, +6 bytes mem)
  #define HOME_ASSISTANT_DISCOVERY_PREFIX   "homeassistant"  // Home Assistant discovery prefix
  #define HOME_ASSISTANT_LWT_TOPIC   "homeassistant/status"  // home Assistant Birth and Last Will Topic (default = homeassistant/status)
  #define HOME_ASSISTANT_LWT_SUBSCRIBE    true               // Subscribe to Home Assistant Birth and Last Will Topic (default = true)

// -- MQTT - TLS - AWS IoT ------------------------
// Using TLS starting with version v6.5.0.16 compilation will only work using Core 2.4.2 and 2.5.2. No longer supported: 2.3.0
//#define USE_MQTT_TLS                             // Use TLS for MQTT connection (+34.5k code, +7.0k mem and +4.8k additional during connection handshake)
//  #define USE_MQTT_TLS_CA_CERT                   // Force full CA validation instead of fingerprints, slower, but simpler to use.  (+2.2k code, +1.9k mem during connection handshake)
                                                   // This includes the LetsEncrypt CA in tasmota_ca.ino for verifying server certificates
//  #define USE_MQTT_TLS_FORCE_EC_CIPHER           // Force Elliptic Curve cipher (higher security) required by some servers (automatically enabled with USE_MQTT_AWS_IOT) (+11.4k code, +0.4k mem)
//  #define USE_MQTT_AWS_IOT_LIGHT                 // Enable MQTT for AWS IoT in light mode, with user/password instead of private certificate
//  #define USE_MQTT_AWS_IOT                       // [Deprecated] Enable MQTT for AWS IoT - requires a private key (+11.9k code, +0.4k mem)
                                                 //   Note: you need to generate a private key + certificate per device and update 'tasmota/tasmota_aws_iot.cpp'
                                                 //   Full documentation here: https://github.com/arendst/Tasmota/wiki/AWS-IoT
//  for USE_4K_RSA (support for 4096 bits certificates, instead of 2048), you need to uncommend `-DUSE_4K_RSA` in `build_flags` from `platform.ini` or `platform_override.ini`

// -- Telegram Protocol ---------------------------
//#define USE_TELEGRAM                             // Support for Telegram protocol (+49k code, +7.0k mem and +4.8k additional during connection handshake)
//  #define USE_TELEGRAM_FINGERPRINT "\xB2\x72\x47\xA6\x69\x8C\x3C\x69\xF9\x58\x6C\xF3\x60\x02\xFB\x83\xFA\x8B\x1F\x23" // Telegram api.telegram.org TLS public key fingerpring
//  #define USE_MQTT_TLS_CA_CERT                   // Use certificate instead of fingerprint

// -- KNX IP Protocol -----------------------------
//#define USE_KNX                                  // Enable KNX IP Protocol Support (+9.4k code, +3k7 mem)
//  #define USE_KNX_WEB_MENU                       // Enable KNX WEB MENU (+8.3k code, +144 mem)

// -- HTTP ----------------------------------------
#define USE_WEBSERVER                            // Enable web server and Wifi Manager (+66k code, +8k mem)
  #define WEB_PORT             80                // Web server Port for User and Admin mode
  #define WEB_USERNAME         "admin"           // Web server Admin mode user name
//  #define USE_JAVASCRIPT_ES6                     // Enable ECMAScript6 syntax using less JavaScript code bytes (fails on IE11)
//  #define USE_WEBSEND_RESPONSE                   // Enable command WebSend response message (+1k code)
//  #define USE_EMULATION_HUE                      // Enable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
//  #define USE_EMULATION_WEMO                     // Enable Belkin WeMo emulation for Alexa (+6k code, +2k mem common)

// -- mDNS ----------------------------------------
#define USE_DISCOVERY                            // Enable mDNS for the following services (+8k code or +23.5k code with core 2_5_x, +0.3k mem)
  #define WEBSERVER_ADVERTISE                    // Provide access to webserver by name <Hostname>.local/
  #define MQTT_HOST_DISCOVERY                    // Find MQTT host server (overrides MQTT_HOST if found)

// -- Time ----------------------------------------
//#define USE_TIMERS                               // Add support for up to 16 timers (+2k2 code)
//  #define USE_TIMERS_WEB                         // Add timer webpage support (+4k5 code)
//  #define USE_SUNRISE                            // Add support for Sunrise and sunset tools (+16k)
//    #define SUNRISE_DAWN_ANGLE DAWN_NORMAL       // Select desired Dawn Angle from (DAWN_NORMAL, DAWN_CIVIL, DAWN_NAUTIC, DAWN_ASTRONOMIC)

// -- Ping ----------------------------------------
//  #define USE_PING                                 // Enable Ping command (+2k code)

// -- Compression ---------------------------------
//#define USE_UNISHOX_COMPRESSION                  // Add support for string compression in Rules or Scripts

// -- Rules or Script  ----------------------------
// Select none or only one of the below defines USE_RULES or USE_SCRIPT
//#define USE_RULES                                // Add support for rules (+8k code)
//  #define USE_EXPRESSION                         // Add support for expression evaluation in rules (+3k2 code, +64 bytes mem)
//    #define SUPPORT_IF_STATEMENT                 // Add support for IF statement in rules (+4k2 code, -332 bytes mem)

//#define USE_SCRIPT                               // Add support for script (+17k code)
  //#define USE_SCRIPT_FATFS 4                     // Script: Add FAT FileSystem Support

//  #define SUPPORT_MQTT_EVENT                     // Support trigger event with MQTT subscriptions (+3k5 code)

// -- Optional modules ----------------------------
//#define ROTARY_V1                                // Add support for Rotary Encoder as used in MI Desk Lamp (+0k8 code)
//  #define ROTARY_MAX_STEPS     10                // Rotary step boundary
//#define USE_SONOFF_RF                            // Add support for Sonoff Rf Bridge (+3k2 code)
//  #define USE_RF_FLASH                           // Add support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB (+2k7 code)
//#define USE_SONOFF_SC                            // Add support for Sonoff Sc (+1k1 code)
#define USE_TUYA_MCU                             // Add support for Tuya Serial MCU
  #define TUYA_DIMMER_ID       2                 // Default dimmer Id
//  #define USE_TUYA_TIME                          // Add support for Set Time in Tuya MCU
//#define USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
//#define USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer (+2k code)
//#define USE_SONOFF_IFAN                          // Add support for Sonoff iFan02 and iFan03 (+2k code)
//#define USE_BUZZER                               // Add support for a buzzer (+0k6 code)
//#define USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))
//#define USE_SHUTTER                              // Add Shutter support for up to 4 shutter with different motortypes (+11k code)
//#define USE_DEEPSLEEP                            // Add support for deepsleep (+1k code)
//#define USE_EXS_DIMMER                           // Add support for ES-Store WiFi Dimmer (+1k5 code)
//  #define EXS_MCU_CMNDS                          // Add command to send MCU commands (+0k8 code)
//#define USE_HOTPLUG                              // Add support for sensor HotPlug
//#define USE_DEVICE_GROUPS                        // Add support for device groups (+5k5 code)
  //#define DEVICE_GROUPS_ADDRESS 239,255,250,250  // Device groups multicast address
  //#define DEVICE_GROUPS_PORT 4447                // Device groups multicast port
  //#define USE_DEVICE_GROUPS_SEND                 // Add support for the DevGroupSend command (+0k6 code)
//#define USE_PWM_DIMMER                           // Add support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+2k3 code, DGR=0k7)
//  #define USE_PWM_DIMMER_REMOTE                  // Add support for remote switches to PWM Dimmer (requires USE_DEVICE_GROUPS) (+0k6 code)
//#define USE_KEELOQ                               // Add support for Jarolift rollers by Keeloq algorithm (+4k5 code)
//#define USE_SONOFF_D1                            // Add support for Sonoff D1 Dimmer (+0k7 code)
//#define USE_SHELLY_DIMMER                        // Add support for Shelly Dimmer (+3k code)
//  #define SHELLY_CMDS                            // Add command to send co-processor commands (+0k3 code)
//  #define SHELLY_FW_UPGRADE                      // Add firmware upgrade option for co-processor (+3k4 code)
//  #define SHELLY_VOLTAGE_MON                     // Add support for reading voltage and current measurment (-0k0 code)

// -- Optional light modules ----------------------
//#define USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
//  #define USE_WS2812_DMA                         // DMA supports only GPIO03 (= Serial RXD) (+1k mem). When USE_WS2812_DMA is enabled expect Exceptions on Pow
//  #define USE_WS2812_INVERTED                    // Use inverted data signal
//  #define USE_WS2812_HARDWARE  NEO_HW_WS2812     // Hardware type (NEO_HW_WS2812, NEO_HW_WS2812X, NEO_HW_WS2813, NEO_HW_SK6812, NEO_HW_LC8812, NEO_HW_APA106)
//  #define USE_WS2812_CTYPE     NEO_GRB           // Color type (NEO_RGB, NEO_GRB, NEO_BRG, NEO_RBG, NEO_RGBW, NEO_GRBW)
//#define USE_MY92X1                               // Add support for MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
//#define USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)
//#define USE_SM2135                               // Add support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
//#define USE_SONOFF_L1                            // Add support for Sonoff L1 led control
//#define USE_ELECTRIQ_MOODL                       // Add support for ElectriQ iQ-wifiMOODL RGBW LED controller (+0k3 code)
//#define USE_LIGHT_PALETTE                        // Add support for color palette (+0k7 code)
//#define USE_DGR_LIGHT_SEQUENCE                   // Add support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)

// -- Counter input -------------------------------
//#define USE_COUNTER                              // Enable inputs as counter (+0k8 code)

// -- Internal Analog input -----------------------
//#define USE_ADC_VCC                              // Display Vcc in Power status. Disable for use as Analog input on selected devices

// -- One wire sensors ----------------------------
//#define USE_DS18x20                              // Add support for DS18x20 sensors with id sort, single scan and read retry (+2k6 code)
//  #define W1_PARASITE_POWER                      // Optimize for parasite powered sensors

// -- I2C sensors ---------------------------------
//#define USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)

#ifdef USE_I2C
//  #define USE_SHT                                // [I2cDriver8] Enable SHT1X sensor (+1k4 code)
//  #define USE_HTU                                // [I2cDriver9] Enable HTU21/SI7013/SI7020/SI7021 sensor (I2C address 0x40) (+1k5 code)
//  #define USE_BMP                                // [I2cDriver10] Enable BMP085/BMP180/BMP280/BME280 sensors (I2C addresses 0x76 and 0x77) (+4k4 code)
//    #define USE_BME680                           // Enable support for BME680 sensor using Bosch BME680 library (+4k code)
//  #define USE_BH1750                             // [I2cDriver11] Enable BH1750 sensor (I2C address 0x23 or 0x5C) (+0k5 code)
//  #define USE_VEML6070                           // [I2cDriver12] Enable VEML6070 sensor (I2C addresses 0x38 and 0x39) (+1k5 code)
//    #define USE_VEML6070_RSET    270000          // VEML6070, Rset in Ohm used on PCB board, default 270K = 270000ohm, range for this sensor: 220K ... 1Meg
//    #define USE_VEML6070_SHOW_RAW                // VEML6070, shows the raw value of UV-A
//  #define USE_ADS1115                            // [I2cDriver13] Enable ADS1115 16 bit A/D converter (I2C address 0x48, 0x49, 0x4A or 0x4B) based on Adafruit ADS1x15 library (no library needed) (+0k7 code)
//  #define USE_INA219                             // [I2cDriver14] Enable INA219 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor (+1k code)
//  #define USE_INA226                             // [I2cDriver35] Enable INA226 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor (+2k3 code)
//  #define USE_SHT3X                              // [I2cDriver15] Enable SHT3x (I2C address 0x44 or 0x45) or SHTC3 (I2C address 0x70) sensor (+0k7 code)
//  #define USE_TSL2561                            // [I2cDriver16] Enable TSL2561 sensor (I2C address 0x29, 0x39 or 0x49) using library Joba_Tsl2561 (+2k3 code)
//  #define USE_TSL2591                            // [I2cDriver40] Enable TSL2591 sensor (I2C address 0x29) using library Adafruit_TSL2591 (+1k6 code)
//  #define USE_MGS                                // [I2cDriver17] Enable Xadow and Grove Mutichannel Gas sensor using library Multichannel_Gas_Sensor (+10k code)
//    #define MGS_SENSOR_ADDR    0x04              // Default Mutichannel Gas sensor i2c address
//  #define USE_SGP30                              // [I2cDriver18] Enable SGP30 sensor (I2C address 0x58) (+1k1 code)
//  #define USE_SI1145                             // [I2cDriver19] Enable SI1145/46/47 sensor (I2C address 0x60) (+1k code)
//  #define USE_LM75AD                             // [I2cDriver20] Enable LM75AD sensor (I2C addresses 0x48 - 0x4F) (+0k5 code)
//  #define USE_APDS9960                           // [I2cDriver21] Enable APDS9960 Proximity Sensor (I2C address 0x39). Disables SHT and VEML6070 (+4k7 code)
//    #define USE_APDS9960_GESTURE                   // Enable APDS9960 Gesture feature (+2k code)
//    #define USE_APDS9960_PROXIMITY                 // Enable APDS9960 Proximity feature (>50 code)
//    #define USE_APDS9960_COLOR                     // Enable APDS9960 Color feature (+0.8k code)
//    #define USE_APDS9960_STARTMODE  0              // Default to enable Gesture mode
//  #define USE_MCP230xx                           // [I2cDriver22] Enable MCP23008/MCP23017 - Must define I2C Address in #define USE_MCP230xx_ADDR below - range 0x20 - 0x27 (+4k7 code)
//    #define USE_MCP230xx_ADDR 0x20               // Enable MCP23008/MCP23017 I2C Address to use (Must be within range 0x20 through 0x26 - set according to your wired setup)
//    #define USE_MCP230xx_OUTPUT                  // Enable MCP23008/MCP23017 OUTPUT support through sensor29 commands (+1k5 code)
//    #define USE_MCP230xx_DISPLAYOUTPUT           // Enable MCP23008/MCP23017 to display state of OUTPUT pins on Web UI (+0k2 code)
//  #define USE_PCA9685                            // [I2cDriver1] Enable PCA9685 I2C HW PWM Driver - Must define I2C Address in #define USE_PCA9685_ADDR below - range 0x40 - 0x47 (+1k4 code)
//    #define USE_PCA9685_ADDR 0x40                // Enable PCA9685 I2C Address to use (Must be within range 0x40 through 0x47 - set according to your wired setup)
//    #define USE_PCA9685_FREQ 50                  // Define default PWM frequency in Hz to be used (must be within 24 to 1526) - If other value is used, it will rever to 50Hz
//  #define USE_MPR121                             // [I2cDriver23] Enable MPR121 controller (I2C addresses 0x5A, 0x5B, 0x5C and 0x5D) in input mode for touch buttons (+1k3 code)
//  #define USE_CCS811                             // [I2cDriver24] Enable CCS811 sensor (I2C address 0x5A) (+2k2 code)
//  #define USE_MPU6050                            // [I2cDriver25] Enable MPU6050 sensor (I2C address 0x68 AD0 low or 0x69 AD0 high) (+3K3 of code and 188 Bytes of RAM)
//    #define USE_MPU6050_DMP                      // Enable in MPU6050 to use the DMP on the chip, should create better results (+8k6 of code)
//  #define USE_DS3231                             // [I2cDriver26] Enable DS3231 external RTC in case no Wifi is avaliable. See docs in the source file (+1k2 code)
//    #define USE_RTC_ADDR  0x68                   // Default I2C address 0x68
//  #define USE_MGC3130                            // [I2cDriver27] Enable MGC3130 Electric Field Effect Sensor (I2C address 0x42) (+2k7 code, 0k3 mem)
//  #define USE_MAX44009                           // [I2cDriver28] Enable MAX44009 Ambient Light sensor (I2C addresses 0x4A and 0x4B) (+0k8 code)
//  #define USE_SCD30                              // [I2cDriver29] Enable Sensiron SCd30 CO2 sensor (I2C address 0x61) (+3k3 code)
//  #define USE_SPS30                              // [I2cDriver30] Enable Sensiron SPS30 particle sensor (I2C address 0x69) (+1.7 code)
//  #define USE_ADE7953                            // [I2cDriver7] Enable ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38) (+1k5)
//  #define USE_VL53L0X                            // [I2cDriver31] Enable VL53L0x time of flight sensor (I2C address 0x29) (+4k code)
//  #define USE_VL53L1X                            // [I2cDriver54] Enable support for VL53L1X sensor (I2C address 0x29) using Pololu VL53L1X library (+2k9 code)
//  #define USE_MLX90614                           // [I2cDriver32] Enable MLX90614 ir temp sensor (I2C address 0x5a) (+0.6k code)
//  #define USE_CHIRP                              // [I2cDriver33] Enable CHIRP soil moisture sensor (variable I2C address, default 0x20)
//  #define USE_PAJ7620                            // [I2cDriver34] Enable PAJ7620 gesture sensor (I2C address 0x73) (+2.5k code)
//  #define USE_PCF8574                            // [I2cDriver2] Enable PCF8574 I/O Expander (I2C addresses 0x20 - 0x26 and 0x39 - 0x3F) (+1k9 code)
//  #define USE_HIH6                               // [I2cDriver36] Enable Honeywell HIH Humidity and Temperature sensor (I2C address 0x27) (+0k6)
//  #define USE_DHT12                              // [I2cDriver41] Enable DHT12 humidity and temperature sensor (I2C address 0x5C) (+0k7 code)
//  #define USE_DS1624                             // [I2cDriver42] Enable DS1624, DS1621 temperature sensor (I2C addresses 0x48 - 0x4F) (+1k2 code)
//  #define USE_AHT1x                              // [I2cDriver43] Enable AHT10/15 humidity and temperature sensor (I2C address 0x38, 0x39) (+0k8 code)
//    #define USE_AHT2x                              // [I2cDriver43] Enable AHT20 instead of AHT1x humidity and temperature sensor (I2C address 0x38) (+0k8 code)
//  #define USE_WEMOS_MOTOR_V1                     // [I2cDriver44] Enable Wemos motor driver V1 (I2C addresses 0x2D - 0x30) (+0k7 code)
//    #define WEMOS_MOTOR_V1_ADDR  0x30            // Default I2C address 0x30
//    #define WEMOS_MOTOR_V1_FREQ  1000            // Default frequency
//  #define USE_HDC1080                            // [I2cDriver45] Enable HDC1080 temperature/humidity sensor (I2C address 0x40) (+1k5 code)
//  #define USE_IAQ                                // [I2cDriver46] Enable iAQ-core air quality sensor (I2C address 0x5a) (+0k6 code)
//  #define USE_AS3935                             // [I2cDriver48] Enable AS3935 Franklin Lightning Sensor (I2C address 0x03) (+5k4 code)
//  #define USE_VEML6075                           // [I2cDriver49] Enable VEML6075 UVA/UVB/UVINDEX Sensor (I2C address 0x10) (+2k1 code)
//  #define USE_VEML7700                           // [I2cDriver50] Enable VEML7700 Ambient Light sensor (I2C addresses 0x10) (+4k5 code)
//  #define USE_MCP9808                            // [I2cDriver51] Enable MCP9808 temperature sensor (I2C addresses 0x18 - 0x1F) (+0k9 code)
//  #define USE_HP303B                             // [I2cDriver52] Enable HP303B temperature and pressure sensor (I2C address 0x76 or 0x77) (+6k2 code)
//  #define USE_MLX90640                           // [I2cDriver53] Enable MLX90640 IR array temperature sensor (I2C address 0x33) (+20k code)
//  #define USE_EZOPH                              // [I2cDriver55] Enable support for EZO's pH sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOORP                             // [I2cDriver55] Enable support for EZO's ORP sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZORTD                             // [I2cDriver55] Enable support for EZO's RTD sensor (+0k2 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOHUM                             // [I2cDriver55] Enable support for EZO's HUM sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOEC                              // [I2cDriver55] Enable support for EZO's EC sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOCO2                             // [I2cDriver55] Enable support for EZO's CO2 sensor (+0k2 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOO2                              // [I2cDriver55] Enable support for EZO's O2 sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOPRS                             // [I2cDriver55] Enable support for EZO's PRS sensor (+0k7 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOFLO                             // [I2cDriver55] Enable support for EZO's FLO sensor (+0k4 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZODO                              // [I2cDriver55] Enable support for EZO's DO sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZORGB                             // [I2cDriver55] Enable support for EZO's RGB sensor (+0k5 code) - Shared EZO code required for any EZO device (+1k2 code)
//  #define USE_EZOPMP                             // [I2cDriver55] Enable support for EZO's PMP sensor (+0k3 code) - Shared EZO code required for any EZO device (+1k2 code)

//  #define USE_DISPLAY                            // Add I2C Display Support (+2k code)
//    #define USE_DISPLAY_MODES1TO5                // Enable display mode 1 to 5 in addition to mode 0
//    #define USE_DISPLAY_LCD                      // [DisplayModel 1] [I2cDriver3] Enable Lcd display (I2C addresses 0x27 and 0x3F) (+6k code)
//    #define USE_DISPLAY_SSD1306                  // [DisplayModel 2] [I2cDriver4] Enable SSD1306 Oled 128x64 display (I2C addresses 0x3C and 0x3D) (+16k code)
//    #define USE_DISPLAY_MATRIX                   // [DisplayModel 3] [I2cDriver5] Enable 8x8 Matrix display (I2C adresseses see below) (+11k code)
//      #define MTX_ADDRESS1     0x71              // [DisplayAddress1] I2C address of first 8x8 matrix module
//      #define MTX_ADDRESS2     0x74              // [DisplayAddress2] I2C address of second 8x8 matrix module
//      #define MTX_ADDRESS3     0x75              // [DisplayAddress3] I2C address of third 8x8 matrix module
//      #define MTX_ADDRESS4     0x72              // [DisplayAddress4] I2C address of fourth 8x8 matrix module
//      #define MTX_ADDRESS5     0x73              // [DisplayAddress5] I2C address of fifth 8x8 matrix module
//      #define MTX_ADDRESS6     0x76              // [DisplayAddress6] I2C address of sixth 8x8 matrix module
//      #define MTX_ADDRESS7     0x00              // [DisplayAddress7] I2C address of seventh 8x8 matrix module
//      #define MTX_ADDRESS8     0x00              // [DisplayAddress8] I2C address of eigth 8x8 matrix module
//    #define USE_DISPLAY_SEVENSEG                 // [DisplayModel 11] [I2cDriver47] Enable sevenseg display (I2C 0x70-0x77) (<+11k code)
//      #define USE_DISPLAY_SEVENSEG_COMMON_ANODE  // Enable support for common anode sevenseg displays
                                                 // Multiple sevenseg displays are logically arranged vertically with MTX_ADDRESS1 at y=0,
                                                 // MTX_ADDRESS2 at y=1, up to MTX_ADDRESS8 at y=7
                                                 // Command: DisplayText [yn]8888
                                                 // will display 8888 at sevenseg display at I2C address MTX_ADDRESS(n-1)
                                                 // Each segment may be address Command: DisplayText [xn]m
                                                 //  where n is 0..4 (4 digits and middle :) and m is decimal for bitmap of which segment to turn on.
                                                 // Reference: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-led-backpack.pdf
    // #define SEVENSEG_ADDRESS1     0x70      // No longer used.  Use MTX_ADDRESS1 - MTX_ADDRESS8 instead to specify I2C address of sevenseg displays
//    #define USE_DISPLAY_SH1106                   // [DisplayModel 7] [I2cDriver6] Enable SH1106 Oled 128x64 display (I2C addresses 0x3C and 0x3D)
#endif  // USE_I2C

// -- SPI sensors ---------------------------------
//#define USE_SPI                                  // Hardware SPI using GPIO12(MISO), GPIO13(MOSI) and GPIO14(CLK) in addition to two user selectable GPIOs(CS and DC)

#ifdef USE_SPI
//  #define USE_NRF24                              // Add SPI support for NRF24L01(+) (+2k6 code)
//    #define USE_MIBLE                            // BLE-bridge for some Mijia-BLE-sensors (+4k7 code)
//  #define USE_DISPLAY                            // Add SPI Display support for 320x240 and 480x320 TFT
//    #define USE_DISPLAY_ILI9341                  // [DisplayModel 4] Enable ILI9341 Tft 480x320 display (+19k code)
//    #define USE_DISPLAY_EPAPER_29                // [DisplayModel 5] Enable e-paper 2.9 inch display (+19k code)
//    #define USE_DISPLAY_EPAPER_42                // [DisplayModel 6] Enable e-paper 4.2 inch display
//    #define USE_DISPLAY_ILI9488                  // [DisplayModel 8] [I2cDriver38] (Touch)
//    #define USE_DISPLAY_SSD1351                  // [DisplayModel 9]
//    #define USE_DISPLAY_RA8876                   // [DisplayModel 10] [I2cDriver39] (Touch)
//  #define USE_RC522                              // Add support for MFRC522 13.56Mhz Rfid reader (+6k code)
//    #define USE_RC522_DATA_FUNCTION              // Add support for reading data block content (+0k4 code)
//    #define USE_RC522_TYPE_INFORMATION           // Add support for showing card type (+0k4 code)

#endif  // USE_SPI

// -- Serial sensors ------------------------------
//#define USE_MHZ19                                // Add support for MH-Z19 CO2 sensor (+2k code)
//#define USE_SENSEAIR                             // Add support for SenseAir K30, K70 and S8 CO2 sensor (+2k3 code)
//  #define CO2_LOW              800               // Below this CO2 value show green light (needs PWM or WS2812 RG(B) led and enable with SetOption18 1)
//  #define CO2_HIGH             1200              // Above this CO2 value show red light (needs PWM or WS2812 RG(B) led and enable with SetOption18 1)
//#define USE_PMS5003                              // Add support for PMS5003 and PMS7003 particle concentration sensor (+1k3 code)
  //#define PMS_MODEL_PMS3003                      // Enable support of PMS3003 instead of PMS5003/PMS7003 (needs the USE_PMS5003 above)
//#define USE_NOVA_SDS                             // Add support for SDS011 and SDS021 particle concentration sensor (+1k5 code)
//  #define STARTING_OFFSET      30                // Turn on NovaSDS XX-seconds before tele_period is reached
//#define USE_HPMA                                 // Add support for Honeywell HPMA115S0 particle concentration sensor (+1k4)
//#define USE_SR04                                 // Add support for HC-SR04 ultrasonic devices (+1k code)
//#define USE_DYP                                  // Add support for DYP ME-007 ultrasonic distance sensor, serial port version (+0k5 code)
#define USE_SERIAL_BRIDGE                        // Add support for software Serial Bridge (+0k8 code)
//#define USE_TCP_BRIDGE                           //  Add support for Serial to TCP bridge (+1.3k code)
//#define USE_MP3_PLAYER                           // Use of the DFPlayer Mini MP3 Player RB-DFR-562 commands: play, volume and stop
//  #define MP3_VOLUME           10                // Set the startup volume on init, the range can be 0..30(max)
//#define USE_AZ7798                               // Add support for AZ-Instrument 7798 CO2 datalogger (+1k6 code)
//#define USE_PN532_HSU                            // Add support for PN532 using HSU (Serial) interface (+1k8 code, 140 bytes mem)
//  #define USE_PN532_DATA_FUNCTION                // Add sensor40 command support for erase, setting data block content (+1k7 code, 388 bytes mem)
//  #define USE_PN532_DATA_RAW                     // Allow DATA block to be used by non-alpha-numberic data (+ 80 bytes code, 48 bytes ram)
//#define USE_RDM6300                              // Add support for RDM6300 125kHz RFID Reader (+0k8)
//#define USE_IBEACON                              // Add support for bluetooth LE passive scan of ibeacon devices (uses HM17 module)
//#define USE_GPS                                  // Add support for GPS and NTP Server for becoming Stratus 1 Time Source (+3k1 code, +132 bytes RAM)
//  #define USE_FLOG                               // Add support for GPS logging in OTA's Flash (Experimental) (+2k9 code, +8 bytes RAM)
//#define USE_HM10                                 // (ESP8266 only) Add support for HM-10 as a BLE-bridge (+9k3 code)
//#define USE_HRXL                                 // Add support for MaxBotix HRXL-MaxSonar ultrasonic range finders (+0k7)
//#define USE_TASMOTA_CLIENT                       // Add support for Arduino Uno/Pro Mini via serial interface including flashing (+2k6 code, 64 mem)
//  #define USE_TASMOTA_CLIENT_FLASH_SPEED 57600   // Usually 57600 for 3.3V variants and 115200 for 5V variants
//  #define USE_TASMOTA_CLIENT_SERIAL_SPEED 57600  // Depends on the sketch that is running on the Uno/Pro Mini
//#define USE_OPENTHERM                            // Add support for OpenTherm (+15k code)
//#define USE_MIEL_HVAC                            // Add support for Mitsubishi Electric HVAC serial interface (+5k code)
//#define USE_AS608                                // Add support for AS608 optical and R503 capacitive fingerprint sensor (+3k code)
//  #define USE_AS608_MESSAGES                     // Add verbose error messages (+0k4 code)

// -- Power monitoring sensors --------------------
//#define USE_ENERGY_MARGIN_DETECTION              // Add support for Energy Margin detection (+1k6 code)
//  #define USE_ENERGY_POWER_LIMIT                 // Add additional support for Energy Power Limit detection (+1k2 code)
//#define USE_PZEM004T                             // Add support for PZEM004T Energy monitor (+2k code)
//#define USE_PZEM_AC                              // Add support for PZEM014,016 Energy monitor (+1k1 code)
//#define USE_PZEM_DC                              // Add support for PZEM003,017 Energy monitor (+1k1 code)
//#define USE_MCP39F501                            // Add support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)
//#define USE_SDM120                               // Add support for Eastron SDM120-Modbus energy monitor (+1k1 code)
  #define SDM120_SPEED         2400              // SDM120-Modbus RS485 serial speed (default: 2400 baud)
//#define USE_SDM630                               // Add support for Eastron SDM630-Modbus energy monitor (+0k6 code)
  #define SDM630_SPEED         9600              // SDM630-Modbus RS485 serial speed (default: 9600 baud)
//  #define SDM630_IMPORT                          // Show import active energy in MQTT and Web (+0k3 code)
//#define USE_DDS2382                              // Add support for Hiking DDS2382 Modbus energy monitor (+0k6 code)
  #define DDS2382_SPEED        9600              // Hiking DDS2382 Modbus RS485 serial speed (default: 9600 baud)
//#define USE_DDSU666                              // Add support for Chint DDSU666 Modbus energy monitor (+0k6 code)
  #define DDSU666_SPEED        9600              // Chint DDSU666 Modbus RS485 serial speed (default: 9600 baud)
//#define USE_SOLAX_X1                             // Add support for Solax X1 series Modbus log info (+3k1 code)
  #define SOLAXX1_SPEED        9600              // Solax X1 Modbus RS485 serial speed (default: 9600 baud)
  #define SOLAXX1_PV2                            // Solax X1 using second PV
//#define USE_LE01MR                               // Add support for F&F LE-01MR Modbus energy monitor (+1k code)
  #define LE01MR_SPEED         9600              // LE-01MR modbus baudrate (default: 9600)
  #define LE01MR_ADDR          1                 // LE-01MR modbus address (default: 0x01)
//#define USE_BL0940                               // Add support for BL0940 Energy monitor as used in Blitzwolf SHP-10 (+1k6 code)
//#define USE_TELEINFO                             // Add support for Teleinfo via serial RX interface (+5k2 code, +168 RAM + SmartMeter LinkedList Values RAM)
//  #define USE_TELEINFO_STANDARD                  // Use standard mode (9600 bps) else it's historical mode (1200 bps)
//#define USE_IEM3000                              // Add support for Schneider Electric iEM3000-Modbus series energy monitor (+0k8 code)
  #define IEM3000_SPEED          19200           // iEM3000-Modbus RS485 serial speed (default: 19200 baud)
  #define IEM3000_ADDR           1               // iEM3000-Modbus modbus address (default: 0x01)
//#define USE_WE517                                // Add support for Orno WE517-Modbus energy monitor (+1k code)

// -- Low level interface devices -----------------
//#define USE_DHT                                  // Add support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)

//#define USE_MAX31855                             // Add support for MAX31855/MAX6675 K-Type thermocouple sensor using softSPI
//#define USE_MAX31865                             // Add support for MAX31865 RTD sensors using softSPI
  #define MAX31865_PTD_WIRES  2                  // PTDs come in several flavors. Pick yours
  #define MAX31865_PTD_RES    100                // Nominal PTD resistance at 0°C (100Ω for a PT100, 1000Ω for a PT1000, YMMV!)
  #define MAX31865_REF_RES    430                // Reference resistor (Usually 430Ω for a PT100, 4300Ω for a PT1000)
  #define MAX31865_PTD_BIAS   0                  // To calibrate your not-so-good PTD
//#define USE_LMT01                                // Add support for TI LMT01 temperature sensor, count pulses on single GPIO (+0k5 code)

// -- IR Remote features - all protocols from IRremoteESP8266 --------------------------
// IR Full Protocols mode is activated through platform.io only.
// Either use 'default_envs = tasmota-ircustom' and disable some features here to keep code not too big
// or use 'default_envs = tasmota-ir' for a pre-packaged IR-dedicated firmware
// When using 'tasmota-ircustom' or 'tasmota-ir', parameters below
// (USE_IR_REMOTE, USE_IR_RECEIVE, USE_IR_HVAC...) are IGNORED.
//
// Code impact of IR full protocols is +81k code, 3k mem
// You can reduce this size by disabling some protocols in "lib/IRremoteESP8266.x.x.x/src/IRremoteESP8266.h"

// -- IR Remote features - subset of IR protocols --------------------------
//#define USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k3 code, 0k3 mem, 48 iram)
//  #define USE_IR_SEND_NEC                        // Support IRsend NEC protocol
//  #define USE_IR_SEND_RC5                        // Support IRsend Philips RC5 protocol
//  #define USE_IR_SEND_RC6                        // Support IRsend Philips RC6 protocol

//  #define USE_IR_RECEIVE                         // Support for IR receiver (+7k2 code, 264 iram)
//    #define IR_RCV_BUFFER_SIZE      100          // Max number of packets allowed in capture buffer (default 100 (*2 bytes ram))
//    #define IR_RCV_TIMEOUT          15           // Number of milli-Seconds of no-more-data before we consider a message ended (default 15)
//    #define IR_RCV_MIN_UNKNOWN_SIZE 6            // Set the smallest sized "UNKNOWN" message packets we actually care about (default 6, max 255)

// -- Zigbee interface ----------------------------
//#define USE_ZIGBEE                                // Enable serial communication with Zigbee CC2530 flashed with ZNP (+49k code, +3k mem)
//  #define USE_ZIGBEE_ZNP                         // Enable ZNP protocol, needed for CC2530 based devices
//  #define USE_ZIGBEE_EZSP                        // Enable EZSP protocol, needed for EFR32 EmberZNet based devices, like Sonoff Zigbee bridge
                                                 // Note: USE_ZIGBEE_ZNP and USE_ZIGBEE_EZSP are mutually incompatible, you must select exactly one
//  #define USE_ZIGBEE_CHANNEL  11                 // Zigbee Channel (11-26)
//  #define USE_ZIGBEE_TXRADIO_DBM  20             // Tx Radio power in dBm (only for EZSP, EFR32 can go up to 20 dBm)

//  #define USE_ZIGBEE_COALESCE_ATTR_TIMER 350     // timer to coalesce attribute values (in ms)
//  #define USE_ZIGBEE_MODELID      "Tasmota Z2T"  // reported "ModelId"      (cluster 0000 / attribute 0005)
//  #define USE_ZIGBEE_MANUFACTURER "Tasmota"      // reported "Manufacturer" (cluster 0000 / attribute 0004)
//  #define USE_ZBBRIDGE_TLS                       // TLS support for zbbridge
//  #define USE_ZIGBEE_ZBBRIDGE_EEPROM 0x50        // I2C id for the ZBBridge EEPROM

// -- Other sensors/drivers -----------------------

//#define USE_TM1638                               // Add support for TM1638 switches copying Switch1 .. Switch8 (+1k code)
//#define USE_HX711                                // Add support for HX711 load cell (+1k5 code)
//  #define USE_HX711_GUI                          // Add optional web GUI to HX711 as scale (+1k8 code)

// Select none or only one of the below defines
//#define USE_TX20_WIND_SENSOR                     // Add support for La Crosse TX20 anemometer (+2k6/0k8 code)
//#define USE_TX23_WIND_SENSOR                     // Add support for La Crosse TX23 anemometer (+2k7/1k code)

//#define USE_WINDMETER                            // Add support for analog anemometer (+2k2 code)

//#define USE_RC_SWITCH                            // Add support for RF transceiver using library RcSwitch (+2k7 code, 460 iram)

//#define USE_RF_SENSOR                            // Add support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)
//  #define USE_THEO_V2                            // Add support for decoding Theo V2 sensors as documented on https://sidweb.nl using 434MHz RF sensor receiver (+1k4 code)
//  #define USE_ALECTO_V2                          // Add support for decoding Alecto V2 sensors like ACH2010, WS3000 and DKW2012 weather stations using 868MHz RF sensor receiver (+1k7 code)

//#define USE_HRE                                  // Add support for Badger HR-E Water Meter (+1k4 code)
//#define USE_A4988_STEPPER                        // Add support for A4988/DRV8825 stepper-motor-driver-circuit (+10k5 code)

// -- Thermostat control ----------------------------
//#define USE_THERMOSTAT                           // Add support for Thermostat
//  #define THERMOSTAT_CONTROLLER_OUTPUTS         1         // Number of outputs to be controlled independently
//  #define THERMOSTAT_SENSOR_NAME                "DS18B20" // Name of the local sensor to be used
//  #define THERMOSTAT_SENSOR_NUMBER              1         // Number of local sensors to be used
//  #define THERMOSTAT_RELAY_NUMBER               1         // Default output relay number for the first controller (+i for following ones)
//  #define THERMOSTAT_SWITCH_NUMBER              1         // Default input switch number for the first controller (+i for following ones)
//  #define THERMOSTAT_TIME_ALLOW_RAMPUP          300       // Default time after last target update to allow ramp-up controller phase in minutes
//  #define THERMOSTAT_TIME_RAMPUP_MAX            960       // Default time maximum ramp-up controller duration in minutes
//  #define THERMOSTAT_TIME_RAMPUP_CYCLE          30        // Default time ramp-up cycle in minutes
//  #define THERMOSTAT_TIME_SENS_LOST             30        // Maximum time w/o sensor update to set it as lost in minutes
//  #define THERMOSTAT_TEMP_SENS_NUMBER           1         // Default temperature sensor number
//  #define THERMOSTAT_TIME_MANUAL_TO_AUTO        60        // Default time without input switch active to change from manual to automatic in minutes
//  #define THERMOSTAT_TIME_RESET                 12000     // Default reset time of the PI controller in seconds
//  #define THERMOSTAT_TIME_PI_CYCLE              30        // Default cycle time for the thermostat controller in minutes
//  #define THERMOSTAT_TIME_MAX_ACTION            20        // Default maximum thermostat time per cycle in minutes
//  #define THERMOSTAT_TIME_MIN_ACTION            4         // Default minimum thermostat time per cycle in minutes
//  #define THERMOSTAT_TIME_MIN_TURNOFF_ACTION    3         // Default minimum turnoff time in minutes, below it the thermostat will be held on
//  #define THERMOSTAT_PROP_BAND                  4         // Default proportional band of the PI controller in degrees celsius
//  #define THERMOSTAT_TEMP_RESET_ANTI_WINDUP     8         // Default range where reset antiwindup is disabled, in tenths of degrees celsius
//  #define THERMOSTAT_TEMP_HYSTERESIS            1         // Default range hysteresis for temperature PI controller, in tenths of degrees celsius
//  #define THERMOSTAT_TEMP_FROST_PROTECT         40        // Default minimum temperature for frost protection, in tenths of degrees celsius
//  #define THERMOSTAT_TEMP_RAMPUP_DELTA_IN       4         // Default minimum delta temperature to target to get into rampup mode, in tenths of degrees celsius
//  #define THERMOSTAT_TEMP_RAMPUP_DELTA_OUT      2         // Default minimum delta temperature to target to get out of the rampup mode, in tenths of degrees celsius
//  #define THERMOSTAT_TEMP_PI_RAMPUP_ACC_E       200       // Default accumulated error when switching from ramp-up controller to PI in hundreths of degrees celsius
//  #define THERMOSTAT_TIME_OUTPUT_DELAY          180       // Default output delay between state change and real actuation event (f.i. valve open/closed)
//  #define THERMOSTAT_TEMP_INIT                  180       // Default init target temperature for the thermostat controller
//  #define THERMOSTAT_TIME_MAX_OUTPUT_INCONSIST  3         // Default maximum time where the input and the outpus shall differ (for diagnostic) in minutes
//  #define THERMOSTAT_TIME_MAX_AUTOTUNE          21600     // Maximum time for the PI autotune function to complete in seconds
//  #define THERMOSTAT_DUTYCYCLE_AUTOTUNE         35        // Default duty cycle (in % over PI cycle time) for the step response of the autotune PI function
//  #define THERMOSTAT_PEAKNUMBER_AUTOTUNE        8         // Default number of peak temperatures (max or min) to be used for the autotune PI function
//  #define THERMOSTAT_TEMP_BAND_NO_PEAK_DET      1         // Default temperature band in thenths of degrees celsius within no peak will be detected
//  #define THERMOSTAT_TIME_STD_DEV_PEAK_DET_OK   10        // Default standard deviation in minutes of the oscillation periods within the peak detection is successful

// -- Prometheus exporter ---------------------------
//#define USE_PROMETHEUS                           // Add support for https://prometheus.io/ metrics exporting over HTTP /metrics endpoint

// -- End of general directives -------------------

/*********************************************************************************************\
 * ESP32 only features
\*********************************************************************************************/

#ifdef ESP32

//#define USE_ETHERNET                             // Add support for ethernet (Currently fixed for Olimex ESP32-PoE)
  // Olimex ESP32-PoE
//  #define ETH_TYPE          0                    // [EthType] 0 = ETH_PHY_LAN8720, 1 = ETH_PHY_TLK110, 2 = ETH_PHY_IP101
//  #define ETH_ADDR          0                    // [EthAddress] 0 = PHY0 .. 31 = PHY31
//  #define ETH_CLKMODE       3                    // [EthClockMode] 0 = ETH_CLOCK_GPIO0_IN, 1 = ETH_CLOCK_GPIO0_OUT, 2 = ETH_CLOCK_GPIO16_OUT, 3 = ETH_CLOCK_GPIO17_OUT
  // wESP32-PoE
//  #define ETH_TYPE          0                    // [EthType] 0 = ETH_PHY_LAN8720, 1 = ETH_PHY_TLK110, 2 = ETH_PHY_IP101
//  #define ETH_ADDR          0                    // [EthAddress] 0 = PHY0 .. 31 = PHY31
//  #define ETH_CLKMODE       0                    // [EthClockMode] 0 = ETH_CLOCK_GPIO0_IN, 1 = ETH_CLOCK_GPIO0_OUT, 2 = ETH_CLOCK_GPIO16_OUT, 3 = ETH_CLOCK_GPIO17_OUT
  // Wireless-Tag WT32-ETH01
//  #define ETH_TYPE          0                    // [EthType] 0 = ETH_PHY_LAN8720, 1 = ETH_PHY_TLK110, 2 = ETH_PHY_IP101
//  #define ETH_ADDR          1                    // [EthAddress] 0 = PHY0 .. 31 = PHY31
//  #define ETH_CLKMODE       0                    // [EthClockMode] 0 = ETH_CLOCK_GPIO0_IN, 1 = ETH_CLOCK_GPIO0_OUT, 2 = ETH_CLOCK_GPIO16_OUT, 3 = ETH_CLOCK_GPIO17_OUT

//#define USE_ADC                                  // Add support for ADC on GPIO32 to GPIO39

//#define USE_SPI                                  // Add support for hardware SPI
//#define USE_MI_ESP32                             // Add support for ESP32 as a BLE-bridge (+9k2 mem, +292k flash)
//#define USE_WEBCAM                               // Add support for webcam

#endif  // ESP32

/*********************************************************************************************\
 * Debug features
\*********************************************************************************************/

//#define DEBUG_TASMOTA_CORE                       // Enable core debug messages
//#define DEBUG_TASMOTA_DRIVER                     // Enable driver debug messages
//#define DEBUG_TASMOTA_SENSOR                     // Enable sensor debug messages
//#define USE_DEBUG_DRIVER                         // Use xdrv_99_debug.ino providing commands CpuChk, CfgXor, CfgDump, CfgPeek and CfgPoke

/*********************************************************************************************\
 * Optional firmware configurations
 * Select none or just one for optional features and sensors as configured in tasmota_configurations.h
 * See RELEASENOTES.md for selected features
\*********************************************************************************************/

//#define FIRMWARE_LITE                            // Create tasmota-lite with no sensors
//#define FIRMWARE_SENSORS                         // Create tasmota-sensors with useful sensors enabled
//#define FIRMWARE_KNX_NO_EMULATION                // Create tasmota-knx with KNX but without Emulation
//#define FIRMWARE_DISPLAYS                        // Create tasmota-display with display drivers enabled
//#define FIRMWARE_IR                              // Create tasmota-ir with IR full protocols activated, and many sensors disabled
//#define FIRMWARE_IR_CUSTOM                       // Create tasmota customizable with special marker to add all IR protocols
//#define FIRMWARE_MINIMAL                         // Create tasmota-minimal as intermediate firmware for OTA-MAGIC

/*********************************************************************************************\
 * No user configurable items below
\*********************************************************************************************/

#ifdef USE_CONFIG_OVERRIDE
//  #include "user_config_override.h"         // Configuration overrides for my_user_config.h
#endif

#if defined(USE_DISCOVERY) && (defined(USE_MQTT_AWS_IOT) || defined(USE_MQTT_AWS_IOT_LIGHT))
  #error "Select either USE_DISCOVERY or USE_MQTT_AWS_IOT, mDNS takes too much code space and is not needed for AWS IoT"
#endif

#if defined(USE_RULES) && defined(USE_SCRIPT)
  #error "Select either USE_RULES or USE_SCRIPT. They can't both be used at the same time"
#endif

/*********************************************************************************************\
 * Post-process compile options for TLS
\*********************************************************************************************/

#if defined(USE_MQTT_TLS) || defined(USE_SENDMAIL) || defined(USE_TELEGRAM)
  #define USE_TLS                                  // flag indicates we need to include TLS code

  #if defined(USE_MQTT_AWS_IOT) || defined(USE_TELEGRAM)
    #define USE_MQTT_TLS_FORCE_EC_CIPHER           // AWS IoT and TELEGRAM require EC Cipher
  #endif
#endif

#endif  // _MY_USER_CONFIG_H_