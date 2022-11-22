#include <PID_v1.h>
#include <basicMPU6050.h> 
#define x_paso 2    // Define el Pin de STEP para Motor de eje X
#define x_dire 5    // Define el Pin de DIR  para Motor de eje X
#define x_habi 8    // Define el Pin de ENABLE  para Motor de eje X
#define y_paso 3
#define y_dire 6
#define y_habi 8
#define z_paso 4
#define z_dire 7
#define z_habi 8
bool flag=false;

int posicionesPromedio=4;
int contadorPromedio=0;
int retardo = 3000;   // Menor numero el giro es mas rapido
int tiempo = 100;   // durante cuanto timpo da el giro el motor (vueltas)

double y1Y;
double y2Y;
double integralY=0;
double Setpoint=90, Input, Output;
double Kp=20, Ki=0, Kd=0;
double promedio=0;
double degresY;
double umbral=0.01;
unsigned long timer=0;
basicMPU6050<> imu;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  
  imu.setup();
  //Encendemos el PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-200,200);
  // Initial calibration of gyro
  imu.setBias();
  Serial.begin(38400);
  pinMode(y_paso, OUTPUT); pinMode(y_dire, OUTPUT); pinMode(y_habi, OUTPUT);
  pinMode(z_paso, OUTPUT); pinMode(z_dire, OUTPUT); pinMode(z_habi, OUTPUT); 
 
}    

void loop() {
  imu.updateBias();
  promedio+=imu.gy();
  contadorPromedio++;
//  if(contadorPromedio==posicionesPromedio){
//    contadorPromedio=0;
//    promedio=promedio/posicionesPromedio;
//  }

  if(millis()-timer>100){
    if(flag==true){
        y1Y=promedio/contadorPromedio;
        contadorPromedio=0;
        promedio=0; 
        flag=false;
    }else{
        if(millis()-timer>200){
          timer=millis();
          flag=true;
          
          y2Y=promedio/contadorPromedio;
          if(abs(y1Y)>umbral){
          double areaY=0.1*((y2Y+y1Y)/2);
          integralY+=areaY;
          }
          degresY=(integralY*360)/(2*PI);
          degresY+=90;
          Input=degresY;
          myPID.Compute();
          mostrarDatosPID();
          estimarDesplazamiento();
        }
    }
  }

  
  //
  //mostrarDatosMPU();
}
void adelante(int pasos,int velocidad){
  digitalWrite(y_habi, LOW);  // Habilita el Driver
  digitalWrite(y_dire, LOW);   // direccion de giro 1
  digitalWrite(z_habi, LOW);  // Habilita el Driver
  digitalWrite(z_dire, LOW);   // direccion de giro 1
  for(int i=0;i<pasos;i++){  // da  pasos por un tiempo  
    digitalWrite(y_paso, HIGH); 
    digitalWrite(z_paso, HIGH);     
    delayMicroseconds(velocidad);          
    digitalWrite(y_paso, LOW);
    digitalWrite(z_paso, LOW);        
    delayMicroseconds(velocidad); 
  }
  digitalWrite(z_habi, HIGH);
  digitalWrite(y_habi, HIGH);
}
void atras(int pasos,int velocidad){

  
  digitalWrite(y_habi, LOW);  // Habilita el Driver
  digitalWrite(y_dire, HIGH);   // direccion de giro 1
  digitalWrite(z_habi, LOW);  // Habilita el Driver
  digitalWrite(z_dire, HIGH);   // direccion de giro 1
  for(int i=0;i<pasos;i++){  // da  pasos por un tiempo  
    digitalWrite(y_paso, HIGH); 
    digitalWrite(z_paso, HIGH);     
    delayMicroseconds(velocidad);          
    digitalWrite(y_paso, LOW);
    digitalWrite(z_paso, LOW);        
    delayMicroseconds(velocidad); 
  }
  digitalWrite(z_habi, HIGH);
  digitalWrite(y_habi, HIGH);
}
void estimarDesplazamiento(){
    //Se requiere 200 pasos para dar una vuelta completa al motor
    if(Output>0){
       
        adelante(int(Output),1300);
        
    }
    if(Output<0){
      
      atras(int(abs(Output)),1300);  
    }
    
}
void mostrarDatosPID(){
  
  Serial.print("DegresY:"); Serial.print(degresY); Serial.print(", ");
  Serial.print("Setpoint:"); Serial.print(Setpoint); Serial.print(", ");
  Serial.print("Input:"); Serial.print(Input); Serial.print(", ");
  Serial.print("Output:"); Serial.print(Output); Serial.print(", ");
 Serial.println();
  
}
void mostrarDatosMPU(){
    //-- Scaled and calibrated output:
  Serial.print("Ax:"); Serial.print(imu.ax()); Serial.print(", ");
  Serial.print("Ay:"); Serial.print(imu.ay()); Serial.print(", ");
  Serial.print("Az:"); Serial.print(imu.az()); Serial.print(", ");

  Serial.print("Gx:"); Serial.print(imu.gx()); Serial.print(", ");
  Serial.print("Gy:"); Serial.print(imu.gy()); Serial.print(", ");
  Serial.print("Gz:"); Serial.print(imu.gz()); Serial.print(", ");
  
  
  Serial.println();
}
