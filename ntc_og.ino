//int ThermistorPin = 0;
//int Vo;
//float R1 = 10000;
//float logR2, R2, T, Tc, Tf;
//float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
//
//void setup() {
//Serial.begin(9600);
//}
//
//void loop() {
//
//  Vo = analogRead(ThermistorPin);
//  R2 = R1 * (1023.0 / (float)Vo - 1.0);
//  logR2 = log(R2);
//  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
//  Tc = T - 273.15;
//  Tf = (Tc * 9.0)/ 5.0 + 32.0; 
//
//  Serial.print("Temperature: "); 
//  Serial.print(Tf);
//  Serial.print(" F; ");
//  Serial.print(Tc);
//  Serial.println(" C");   
//
//  delay(500);
//}



// 74HC4067 multiplexer demonstration (16 to 1)

// control pins output table in array form
// see truth table on page 2 of TI 74HC4067 data sheet
// connect 74HC4067 S0~S3 to Arduino D7~D4 respectively
// connect 74HC4067 pin 1 to Arduino A0
byte controlPins[] = {B00000000, 
                  B10000000,
                  B01000000,
                  B11000000,
                  B00100000,
                  B10100000,
                  B01100000,
                  B11100000,
                  B00010000,
                  B10010000,
                  B01010000,
                  B11010000,
                  B00110000,
                  B10110000,
                  B01110000,
                  B11110000 }; 

// holds incoming values from 74HC4067                  
byte muxValues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};

void setup()
{
  Serial.begin(9600);
  DDRD = B11111111; // set PORTD (digital 7~0) to outputs
}

void setPin(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPins[outputPin];
}

void displayData()
// dumps captured data from array to serial monitor
{
  Serial.println();
  Serial.println("Values from multiplexer:");
  Serial.println("========================");
  for (int i = 0; i < 16; i++)
  {
    Serial.print("input I"); 
    Serial.print(i); 
    Serial.print(" = "); 
    Serial.println(muxValues[i]);
  }
  Serial.println("========================");  
}

void loop()
{
  for (int i = 0; i < 16; i++)
  {
    setPin(i); // choose an input pin on the 74HC4067
    muxValues[i]=analogRead(0); // read the vlaue on that pin and store in array
  }

  // display captured data
  displayData();
  delay(2000); 
}
