

#define number_of_mux 1
#define numOfMuxPins number_of_mux * 8
#define enPin 2
#define S0 3
#define S1 4
#define S2 5
#define S3 6

const int comPin  = 7;
String incomingByte;   // for incoming serial data

int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(enPin, OUTPUT);
  
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  digitalWrite(enPin, LOW);

}

void loop() {
  Serial.print("\ntype what channel to read\n");
  while (Serial.available() == 0)   {
  }
    incomingByte = Serial.readString();
    int in=incomingByte.toInt();
    Serial.print("you said --\n");
    Serial.print(in,BIN);
    Serial.print("\n");
//    Serial.print(bitRead(in,3));
//    Serial.print(bitRead(in,2));
//    Serial.print(bitRead(in,1));
//    Serial.print(bitRead(in,0));

    digitalWrite(S0, bitRead(in,3));
    digitalWrite(S1, bitRead(in,2));
    digitalWrite(S2, bitRead(in,1));
    digitalWrite(S3, bitRead(in,0));

    
      Vo = analogRead(comPin);
      Serial.print(Vo);
      
      R2 = R1 * (1023.0 / (float)Vo - 1.0);
      logR2 = log(R2);
      T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
      T = T - 273.15;
      Serial.print("Temperature1: "); 
      Serial.print(T);
      Serial.println(" C");
}
