
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

int retardo = 3000;   // Menor numero el giro es mas rapido
int tiempo = 100;   // durante cuanto timpo da el giro el motor (vueltas)
basicMPU6050<> imu;



void setup() {
  imu.setup();

  // Initial calibration of gyro
  imu.setBias();
  Serial.begin(38400);
    
pinMode(y_paso, OUTPUT); pinMode(y_dire, OUTPUT); pinMode(y_habi, OUTPUT);
pinMode(z_paso, OUTPUT); pinMode(z_dire, OUTPUT); pinMode(z_habi, OUTPUT); 
}    

void loop() {
  imu.updateBias();
  giro(y_paso,y_dire,y_habi);
  giro(z_paso,z_dire,z_habi);
  mostrarDatosMPU();
}

void giro(int paso_,int dire_,int habi_) {
   digitalWrite(habi_, LOW);  // Habilita el Driver
   digitalWrite(dire_, LOW);   // direccion de giro 1
   for(int i=0;i<tiempo;i++){  // da  pasos por un tiempo  
    digitalWrite(paso_, HIGH);      
    delayMicroseconds(retardo);          
    digitalWrite(paso_, LOW);       
    delayMicroseconds(retardo); 
   }
  digitalWrite(dire_, HIGH);   // direccion de giro 2
  for(int i=0;i<tiempo;i++){   // da  pasos por un tiempo  
    digitalWrite(paso_, HIGH);      
    delayMicroseconds(retardo);          
    digitalWrite(paso_, LOW);       
    delayMicroseconds(retardo);  
  }
  digitalWrite(habi_, HIGH);   // quita la habilitacion del Driver

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
