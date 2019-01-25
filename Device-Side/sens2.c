#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <android/sensor.h>
#include <android/looper.h>

ASensorEventQueue* sensorEventQueue;

static int get_sensor_events(int fd, int events, void* data);

int main (int argc, char *argv[])
{
  ASensorEvent event;
  ASensorManager* sensorManager;
  const ASensor* accSensor;
  const ASensor* mSensor;
  ALooper* looper = ALooper_forThread();

  if(looper == NULL)
    {
      looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    }

  sensorManager = ASensorManager_getInstance();
  accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
  mSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_MAGNETIC_FIELD);
  sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, 0,NULL, NULL);
  ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);
  ASensorEventQueue_enableSensor(sensorEventQueue, mSensor);

  while (1)
    {
      get_sensor_events (0, 0,NULL);
      //sleep (1);
    }
}



static int fire = 1,ctt=0;
float accmod;
float evx,evy;

static int get_sensor_events(int fd, int events, void* data)
{//printf("==1==\n");
  static ASensorEvent event;

  while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0)
    {
      if(event.type == ASENSOR_TYPE_MAGNETIC_FIELD)
	  {
        ctt++;
        evx+=event.acceleration.x;
        evy+=event.acceleration.y;
	    if(ctt>10){
                ctt=0,evx/=10,evy/=10;
                printf("%+6.5f %+6.5f,%+6.5f,%+6.5f   %+6.5f\n",180/3.14159265*atan2f(evy,evx),evx, evy, event.magnetic.z,sqrt(event.magnetic.x*event.magnetic.x+ event.magnetic.y*event.magnetic.y+ event.magnetic.z*event.magnetic.z));
                }
	  }
    if(event.type == ASENSOR_TYPE_ACCELEROMETER)
        {
/*          accmod=sqrt(event.acceleration.x*event.acceleration.x+event.acceleration.y*event.acceleration.y+event.acceleration.z*event.acceleration.z);
	      ctt++;
	      evx+=event.acceleration.x;
	      evy+=event.acceleration.y;
	      if(ctt>10){
                ctt=0,evx/=10,evy/=10;
                printf("%+6.5f %+6.5f %+6.5f %+6.5f\n", event.acceleration.x, event.acceleration.y, event.acceleration.z, accmod);
          }
	      if(accmod>11){printf("passo\n");}///sllep(400mili);send();
*/        }
    }

  return 1;
}
