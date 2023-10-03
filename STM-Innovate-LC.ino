
// Nastavte pin, který bude použit pro měření napětí.
#define MEASURE_PIN A0




void setup() {
// Nastavte rychlost převodu ADC na 100 Hz.
  analogReadResolution(12);
 // Nastavte pin pro LED na výstup.
  pinMode(LED_BUILTIN, OUTPUT);

  // Nastavte pin pro měření na vstup.
  pinMode(MEASURE_PIN, INPUT);

  while(!Serial);
  Serial.begin(19200);
  delay(200);
}


void loop() {
   // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 4027) to a voltage (0 - 5V):
  // 5V na převodníku = 4005
  float voltage = sensorValue * (5.0 / 4005.0);
  float lambda = 0.68 + (voltage * 0.68 /5);
  float inno_lambda = (lambda * 1000) - 500;
  uint16_t LAMBDA = (inno_lambda); 
  
  uint16_t header = 0xB282;
  uint16_t afr_header = 0x4200;
  uint16_t AFR = 147;
  uint16_t hnumber = AFR;
  hnumber  <<= 1;
  hnumber = hnumber & 0xFF00;
  uint16_t lnumber = AFR & 0x007F;
  uint16_t ISP2_AFR = hnumber + lnumber + afr_header;
  
  hnumber = LAMBDA;
  hnumber  <<= 1;
  hnumber = hnumber & 0xFF00;
  lnumber = LAMBDA & 0x007F;
  uint16_t ISP2_LAMBDA = hnumber + lnumber;

  
  Serial.write((header >> 8) & 0xFF);
  Serial.write(header & 0xFF);
  delay(5);
  Serial.write((ISP2_AFR >> 8) & 0xFF);
  Serial.write(ISP2_AFR & 0xFF);
  delay(5);
  Serial.write((ISP2_LAMBDA >> 8) & 0xFF);
  Serial.write(ISP2_LAMBDA & 0xFF);
  delay(5);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(50);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(50);                      // wait for a second
} 