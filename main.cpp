#include <Arduino.h>
#define SensorESP 32 //Sensor

int DatoSensor;
String BanderaTiva;

double adcFiltradoEMA = 30; // S(0) = Y(0)
double alpha = 0.12;        // 0.05; // Factor de suavizado (0-1)

void filtroEMA(void);
void MedirSensor (void);

void MedirSensor (void){
filtroEMA();
adcFiltradoEMA = analogRead(SensorESP)/150.0*16.0;
DatoSensor = adcFiltradoEMA;
}

void setup() {

Serial.begin(115200);
Serial2.begin(115200);
  
}

void loop() {

if (Serial2.available()) {
		BanderaTiva = Serial2.readString();
        //Serial.println(BanderaTiva);
		//Serial.println("Valor de BanderaTiva: " + BanderaTiva);
		if (BanderaTiva == "on") {
		Serial.println("Medición requerida");
        MedirSensor();
        Serial2.print(DatoSensor);
		Serial.println("Medición enviada: ");
		Serial.println(DatoSensor);
		delay(200);
		}
	}
}

//funciones ADC
void filtroEMA(void){
float lectura = analogRead(SensorESP)/150.0*16.0;
adcFiltradoEMA = (alpha * lectura) + ((1.0 - alpha) * adcFiltradoEMA);
}
