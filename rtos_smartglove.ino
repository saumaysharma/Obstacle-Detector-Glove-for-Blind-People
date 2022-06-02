#include <Arduino_FreeRTOS.h>
#define trigPin 13
#define echoPin 12
#define led 11

void Task_control(void *param);
void Task_print(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

void setup()
{
  
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  xTaskCreate(Task_control,"Task1",100,NULL,1,&Task_Handle1);
  xTaskCreate(Task_print,"Task2",100,NULL,1,&Task_Handle2);
}
void loop(){
  
}

void Task_control(void *param)
{
  (void) param;
  while(1){
    long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 25)
  {
  digitalWrite(led,HIGH);
  }
 
  else
  {
  digitalWrite(led,LOW);
  vTaskDelay(100/portTICK_PERIOD_MS);
  } 
  }
}

void Task_print(void *param)
{
  (void) param;
  while(1){
    long duration, distance;
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
     vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
