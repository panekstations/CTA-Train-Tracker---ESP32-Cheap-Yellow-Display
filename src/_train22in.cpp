#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ArduinoJson.h>

// Declare the label object at a scope accessible by both setup() and loop() if necessary
lv_obj_t *label;

// UDPATE WITH YOUR WIFI DETAILS

const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxxx";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  smartdisplay_init(); // Initialize your smart display here

  // Rotate the display if necessary
  auto disp = lv_disp_get_default();
  lv_disp_set_rotation(disp, LV_DISP_ROT_90);

  // Create a label for displaying the fetched data
  lv_obj_t* label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "BLUE LINE TRAIN TRACKER");
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0,0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_22, 0);
}

// UDPATE WITH YOUR TRAIN TRACKER KEY AND PARAMETERS

void fetchDataAndDisplay() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://lapi.transitchicago.com/api/1.0/ttarrivals.aspx?key=XXXXXXXXXXXXXXXXXXXXXXXX&mapid=40590&outputType=JSON");
    int httpCode = http.GET(); // Make the GET request

    if (httpCode > 0) {
      String payload = http.getString(); // Get the request response payload
      Serial.println(payload); // Print the response to the Serial monitor

      // Parse JSON payload
      DynamicJsonDocument doc(1024 * 2); // Adjust size according to your JSON response size
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      const char* currentTimeStr = doc["ctatt"]["tmst"];
      struct tm currentTimeTm = {0};
      strptime(currentTimeStr, "%Y-%m-%dT%H:%M:%S", &currentTimeTm);
      time_t currentTime = mktime(&currentTimeTm);

      String displayText = "Damen Blue Line - South \n--------------------------------------\n";
      JsonArray arr = doc["ctatt"]["eta"].as<JsonArray>();
      for(JsonVariant v : arr) {
        const char* trDr = v["trDr"];
        // Check if destSt is '30171'
        if (strcmp(trDr, "5") == 0) {
          const char* isDly = v["isDly"];    //Not Delayed 0, Delayed 1
          const char* isApp = v["isApp"];    //Not Due 0, Due 1
          const char* destNm = v["destNm"];
          const char* rn = v["rn"];
          const char* arrTStr = v["arrT"];

          struct tm arrTTm = {0};
          strptime(arrTStr, "%Y-%m-%dT%H:%M:%S", &arrTTm);
          time_t arrTTime = mktime(&arrTTm);

          // Calculate the difference in minutes
          double minutesDiff = difftime(arrTTime, currentTime) / 60;

          String displayArr = "";
          if (strcmp(isDly, "1") == 0) {
              displayArr = String("Delay");
          } else if (strcmp(isApp, "1") == 0) {
              displayArr = String("Due");
          } else {
              displayArr = String(minutesDiff, 1) + " min";
          }

          // Format and append this entry to the display text
          displayText += String(destNm) + " (" + String(rn) + "):   " + displayArr + "\n";
        }
      }

      // Display the response on the LCD
      lv_obj_t* label = lv_label_create(lv_scr_act());
      lv_label_set_text(label, displayText.c_str());
      lv_obj_align(label,  LV_ALIGN_TOP_LEFT, 0,0);
      lv_obj_set_style_text_font(label, &lv_font_montserrat_22, 0);
    } else {
      lv_obj_t* label = lv_label_create(lv_scr_act());
      lv_label_set_text(label, "No Response Yet...");
      lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0,0);
      lv_obj_set_style_text_font(label, &lv_font_montserrat_22, 0);
      
    }

    http.end(); // Free the resources
  }
}


// UDPATE WITH YOUR TRAIN TRACKER KEY AND PARAMETERS

void fetchDataAndDisplay2() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://lapi.transitchicago.com/api/1.0/ttarrivals.aspx?key=XXXXXXXXXXXXXXXXXXXXXXXXXX&mapid=40590&outputType=JSON");
    int httpCode = http.GET(); // Make the GET request

    if (httpCode > 0) {
      String payload = http.getString(); // Get the request response payload
      Serial.println(payload); // Print the response to the Serial monitor

      // Parse JSON payload
      DynamicJsonDocument doc(1024 * 2); // Adjust size according to your JSON response size
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      const char* currentTimeStr = doc["ctatt"]["tmst"];
      struct tm currentTimeTm = {0};
      strptime(currentTimeStr, "%Y-%m-%dT%H:%M:%S", &currentTimeTm);
      time_t currentTime = mktime(&currentTimeTm);

      String displayText = "Damen Blue Line - North \n-----------------------------------\n";
      JsonArray arr = doc["ctatt"]["eta"].as<JsonArray>();
      for(JsonVariant v : arr) {
        const char* trDr = v["trDr"];
        // Check if destSt is '30077'
        if (strcmp(trDr, "1") == 0)  {
          const char* isDly = v["isDly"];    //Not Delayed 0, Delayed 1
          const char* isApp = v["isApp"];    //Not Due 0, Due 1
          const char* destNm = v["destNm"];
          const char* rn = v["rn"];
          const char* arrTStr = v["arrT"];

          struct tm arrTTm = {0};
          strptime(arrTStr, "%Y-%m-%dT%H:%M:%S", &arrTTm);
          time_t arrTTime = mktime(&arrTTm);

          // Calculate the difference in minutes
          double minutesDiff = difftime(arrTTime, currentTime) / 60;

          String displayArr = "";
          if (strcmp(isDly, "1") == 0) {
              displayArr = String("Delay");
          } else if (strcmp(isApp, "1") == 0) {
              displayArr = String("Due");
          } else {
              displayArr = String(minutesDiff, 1) + " min";
          }

          // Format and append this entry to the display text
          displayText += String(destNm) + " (" + String(rn) + "):     " + displayArr + "\n";
        }
      }

      // Display the response on the LCD
      lv_obj_t* label = lv_label_create(lv_scr_act());
      lv_label_set_text(label, displayText.c_str());
      lv_obj_align(label,  LV_ALIGN_TOP_LEFT, 0,0);
      lv_obj_set_style_text_font(label, &lv_font_montserrat_22, 0);
    } else {
      lv_obj_t* label = lv_label_create(lv_scr_act());
      lv_label_set_text(label, "No Response Yet...");
      lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0,0);
      lv_obj_set_style_text_font(label, &lv_font_montserrat_22, 0);
    }

    http.end(); // Free the resources
  }
}



// Example function to clear the screen and LED color
void clearScreen() {
  lv_obj_clean(lv_scr_act());
}

void loop() {
  clearScreen(); // Then recreate and align your label or other UI elements as necessary
  fetchDataAndDisplay(); // Fetch and display data from the URL
  lv_task_handler(); // Handle LVGL tasks
  // smartdisplay_led_set_rgb(0,0,1);  //optional set to blue
  delay(10000); // Wait for 10 seconds before the next fetch
  // smartdisplay_led_set_rgb(0,0,0);  //optional set to black

  // clearScreen(); // Then recreate and align your label or other UI elements as necessary
  // fetchDataAndDisplay2(); // Fetch and display data from the URL
  // lv_task_handler(); // Handle LVGL tasks
  // delay(10000); // Wait for 10 seconds before the next fetch


}




