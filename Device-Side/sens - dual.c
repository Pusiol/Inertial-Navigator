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

static int get_sensor_events(int fd, int events, void* data)
{//printf("==1==\n");
  static ASensorEvent event;

  while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0)
    {//printf("==2==\n");
      if(event.type == ASENSOR_TYPE_MAGNETIC_FIELD)
	{//printf("==3==\n");
	      //printf("(%04d) %+6.5f %+6.5f %+6.5f %lld\n", 7, event.magnetic.x, event.magnetic.y, event.magnetic.z, event.timestamp);//cnt, evebt,type,
//	      printf("%+6.5f,%+6.5f,%+6.5f\n",event.magnetic.x, event.magnetic.y, event.magnetic.z);//cnt, evebt,type,
	      ctt++;if(ctt>10){ctt=0;printf("%+6.5f %+6.5f,%+6.5f,%+6.5f   %+6.5f\n",180/3.14159265*atan2f(event.magnetic.y,event.magnetic.x),event.magnetic.x, event.magnetic.y, event.magnetic.z,sqrt(event.magnetic.x*event.magnetic.x+ event.magnetic.y*event.magnetic.y+ event.magnetic.z*event.magnetic.z));}//cnt, evebt,type,

	}
    if(event.type == ASENSOR_TYPE_ACCELEROMETER)
        {//printf("==3==\n");
	      //printf("(%04d) %+6.5f %+6.5f %+6.5f %lld\n", 7, event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);//cnt, evebt,type,
        }
    }
  //should return 1 to continue receiving callbacks, or 0 to unregister
  return 1;
}
