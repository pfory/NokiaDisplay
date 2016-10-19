/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
 Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_BOJLER                   2
OneWire oneWireBojler(ONE_WIRE_BUS_BOJLER);
DallasTemperature sensorsBojler(&oneWireBojler);

int teplotaBojler = 0;

void setup()   {
  Serial.begin(9600);
  Serial.println("Koupelna v 0.1");
  sensorsBojler.begin();
  sensorsBojler.setResolution(12);
  sensorsBojler.setWaitForConversion(false);
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(60);

  display.clearDisplay();   // clears the screen and buffer
  display.display();
}


void loop() {
  //mereni
  sensorsBojler.requestTemperatures();
  delay(750);
  if (sensorsBojler.getCheckForConversion()==true) {
    teplotaBojler = sensorsBojler.getTempCByIndex(0) * 10;
    Serial.print("Teplota bojler ");
    Serial.println(teplotaBojler);
  } 
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(8,2);
  display.print("Bojler");
  display.setTextSize(2);
  display.setCursor(38,11);
  display.print("C");
  display.setTextSize(1);
  display.setCursor(31,11);
  display.print((char)247);
  
  display.setTextSize(1);
  display.setCursor(0,30);
  display.print("0");
  display.setCursor(17,30);
  display.print("25");
  display.setCursor(38,30);
  display.print("50");
  display.setCursor(59,30);
  display.print("75");

  display.drawRect(0, display.height()-10, display.width(), 10, BLACK);

  //long cislo = cisloom(0,1000);
  //cislo++;
  display.setTextSize(2);
  display.setCursor(4,11);
  if (teplotaBojler<100) {
    display.print(" ");
  }
  display.print(teplotaBojler/10);
  display.setCursor(25,17);
  display.setTextSize(1);
  display.print(".");
  display.print(teplotaBojler%10);
  
  byte delka = 84.0/100.0 * (float)teplotaBojler/10;
  display.fillRect(0, display.height()-9, delka, 8, BLACK);

  display.drawRect(52, 0, display.width()-52, 28, BLACK);
  display.drawRect(0, 0, 53, 28, BLACK);
  display.setTextSize(1);
  display.setCursor(56,4);
  display.print(100);
  display.print("%");
  display.setCursor(58,16);
  display.print(28);
  display.print((char)247);
  display.print("C");

  
  if (delka>21) {
    display.drawRect(22, display.height()-9, 1, 8, WHITE);
  } else {
    display.drawRect(21, display.height()-9, 1, 8, BLACK);
  }
  if (delka>42) {
    display.drawRect(43, display.height()-9, 1, 8, WHITE);
  } else {
    display.drawRect(42, display.height()-9, 1, 8, BLACK);
  }
  if (delka>63) {
    display.drawRect(64, display.height()-9, 1, 8, WHITE);
  } else {
    display.drawRect(63, display.height()-9, 1, 8, BLACK);
  }
  
  display.display();
  delay(10000);
/*   if (cislo>1000) {
    cislo=0;
  } */
}


