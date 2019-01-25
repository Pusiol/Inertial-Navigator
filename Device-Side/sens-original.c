#include <stdio.h>
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
   
  ALooper* looper = ALooper_forThread();
  
  if(looper == NULL)
    {
      looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    }
  
  sensorManager = ASensorManager_getInstance();
  accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
  sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, 0, 
						     NULL, NULL);
  ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);

  while (1)
    {
      get_sensor_events (0, 0,NULL);
      sleep (1);
    }
}



static int fire = 1;

static int get_sensor_events(int fd, int events, void* data) 
{//printf("==1==\n");
  static ASensorEvent event;

  while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) 
    {//printf("==2==\n");
      if(event.type == ASENSOR_TYPE_ACCELEROMETER) 
	{//printf("==3==\n");
	      printf("(%04d) %+6.5f %+6.5f %+6.5f %lld\n", 7, event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);//cnt, evebt,type,
	}
    }
  //should return 1 to continue receiving callbacks, or 0 to unregister
  return 1;
}