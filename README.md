# CTA Train Tracker for the Sunton aka Cheap Yellow Display (CYD) boards. esp32-2432S024N, esp32-2432S022N

For [PlatformIO](https://platformio.org/)

Example of [ESP32-2432S022N on AliExpress](https://www.aliexpress.us/item/3256806097839998.html?spm=a2g0o.order_list.order_list_main.20.21ef1802zxQefl&gatewayAdapt=glo2usa)
Example of [ESP32-2432S024N on AliExpress](https://www.aliexpress.us/item/3256805678792605.html?spm=a2g0o.order_list.order_list_main.25.21ef1802zxQefl&gatewayAdapt=glo2usa)

The files are currently configured for the x22N board. You can use another Sunton ESP32 board, but you will need to update the following files: 

**\platformio.ini file** - will need to update the board to have the correct model number
**\src\_train22in.cpp file** - I've appended '.backup' to each .cpp file not in use to avoid compiling issues. There should only be one. 


[![Platform IO CI](https://github.com/rzeldent/esp32-smartdisplay-demo/actions/workflows/main.yml/badge.svg)](https://github.com/rzeldent/esp32-smartdisplay-demo/actions/workflows/main.yml)

This application was based on the Github Repo [esp32-smartdisplay](https://github.com/rzeldent/esp32-smartdisplay) library that is intended to be used in [PlatformIO](https://platformio.org/).
See [https://github.com/rzeldent/esp32-smartdisplay](https://github.com/rzeldent/esp32-smartdisplay/) for more information about the driver library.


![Example](assets/CTA.JPG)


  
