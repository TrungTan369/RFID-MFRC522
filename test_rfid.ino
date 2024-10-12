/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program to test your firmware.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * This example test the firmware of your MFRC522 reader module, only known version can be checked. If the test passed
 * it do not mean that your module is faultless! Some modules have bad or broken antennas or the PICC is broken.
 * 
 * @author Rotzbua
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int UID[4], i;
int the1[4] = {213, 251, 142, 18}; // the sinh vien
int the2[4] = {227, 182, 182, 15}; // the xanh
int the3[4] = {27, 153, 140, 2} ; // the trang
void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 module

}

void loop(){
    if(! mfrc522.PICC_IsNewCardPresent()){
        return;
    }
    if(! mfrc522.PICC_ReadCardSerial()){
        return;
    }
    Serial.print("UID: ");
    for(byte i = 0; i < mfrc522.uid.size; i++){
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
        UID[i] = mfrc522.uid.uidByte[i];
        Serial.print(UID[i]);
    }
    Serial.println("    ");

    if(UID[i] ==  the1[i]){
        Serial.println("THE SINH VIEN");
    }
    
    else if(UID[i] == the2[i]){
        Serial.println("THE XANH");
    }
    else if(UID[i] == the3[i]){
        Serial.println("THE TRANG");
    }
    else {
        Serial.println("SAI THE");
    }

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}
