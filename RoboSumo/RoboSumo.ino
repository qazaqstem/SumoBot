/* Author: Yermekov Rustem (qazaqstem)
 * rustem.erm@gmail.com
 * date: 13/04/2024
 * last update: 16/05/2024
 * robo sumo 10x10 500g 
 * 4 motor n20 motor 800RPM
 * 1 ir distance sensor 
 * 1 JSUMO ir starting module
 */
 
//left motors pin: 3 5
//right motor pin: 6 9
//IR sensor SHARP 0A51SK pin: A0
//Jsumo Starting module pin: 14

#define Jstart 14

#define Lmotor1 3
#define Lmotor2 5
#define Rmotor1 6
#define Rmotor2 9

int Fdist = 15; //Fight distance

boolean STRT = false;

const int sensorPin[] = {A0};
float distance[1]; //variable sharp ir distance
const int AVERAGE_OF =50;
const float MCU_VOLTAGE = 5.0;

void setup() {
  Serial.begin(9600);
  pinMode(Jstart, INPUT);
  pinMode(Lmotor1, OUTPUT);
  pinMode(Lmotor2, OUTPUT);
  pinMode(Rmotor1, OUTPUT);
  pinMode(Rmotor2, OUTPUT);
}

void loop() {
  readDistance(0);//Distance from ir sharp

  STRT = digitalRead(Jstart);//Read staus from starting module

//----If starting module in start mode, robot start fight----
  if (STRT == false){
    Motorstop();
  }else{
    if(distance[0] < Fdist){ //distance when robot start go forward
      forward();
    } else{
        left();
    }
  }
//----------------------------
  
  Serial.print("d1 =");
  Serial.print(distance[0]);
  Serial.println("cm");
  delay(50);
}

void forward(){
  Serial.println("Sumo forward");
  digitalWrite(Lmotor1, HIGH);
  digitalWrite(Lmotor2, LOW);
  digitalWrite(Rmotor1, LOW);
  digitalWrite(Rmotor2, HIGH);   
}

void bacward(){
  Serial.println("Sumo backward");
  digitalWrite(Lmotor1, LOW);
  digitalWrite(Lmotor2, HIGH);
  digitalWrite(Rmotor1, HIGH);
  digitalWrite(Rmotor2, LOW); 
}

void left(){
  Serial.println("Sumo left");
  digitalWrite(Lmotor1, LOW);
  digitalWrite(Lmotor2, HIGH);
  digitalWrite(Rmotor1, LOW);
  digitalWrite(Rmotor2, HIGH); 
}

void right(){
  Serial.println("Sumo right");
  digitalWrite(Lmotor1, HIGH);
  digitalWrite(Lmotor2, LOW);
  digitalWrite(Rmotor1, HIGH);
  digitalWrite(Rmotor2, LOW);   
}

void Motorstop(){
  Serial.println("Sumo stop");
  digitalWrite(Lmotor1, LOW);
  digitalWrite(Lmotor2, LOW);
  digitalWrite(Rmotor1, LOW);
  digitalWrite(Rmotor2, LOW);   
}

void readDistance(int sensor){
      float voltage_temp_average=0;     
      for(int i=0; i < AVERAGE_OF; i++)
    {
      int sensorValue = analogRead(sensorPin[sensor] );
      delay(1);      
      voltage_temp_average +=sensorValue * (MCU_VOLTAGE / 1023.0);
    }
     voltage_temp_average /= AVERAGE_OF;
  distance[sensor] = 33.9 + -69.5*(voltage_temp_average) + 62.3*pow(voltage_temp_average,2) + -25.4*pow(voltage_temp_average,3) + 3.83*pow(voltage_temp_average,4);
}
