#include <stdio.h>
#include <unistd.h>
#include <android/sensor.h>
#include <android/looper.h>

#include <sys/socket.h>
#include <netinet/in.h>


ASensorEventQueue* sensorEventQueue;

static int get_sensor_events(int fd, int events, void* data);

float mx,my,mz;

int main (int argc, char *argv[])
{
  char r[60];
  //========================================
  struct sockaddr_in   server, client;
  socklen_t            len = sizeof (struct sockaddr_in);
  int  s,s1;

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(8886);

  s = socket (PF_INET, SOCK_STREAM, 0);
  bind (s, (struct sockaddr *) &server, sizeof (server));
  listen (s, 10);
//========================================

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
  sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, 0, NULL, NULL);
  ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);
  ASensorEventQueue_enableSensor(sensorEventQueue, mSensor);


  printf("=1=\n");
  s1 = accept (s, (struct sockaddr *)&client, &len);
printf("=2=\n");
  while (1)
    {
      if(get_sensor_events (0, 0,NULL)){
            sprintf(r,"%.0f %.0f %.0f\n", 10000*mx,10000*my,10000*mz);
            printf("=4=\n");write (s1, r, strlen(r));
            usleep(300000);
            }
      //close (s1);
    }
}



static int c;
//static char *scrtl="(0007) -0.81403 +0.16281 +9.18416 1543707852504314000                                                                  ";


static int fire = 1;

static int get_sensor_events(int fd, int events, void* data)
{char scrtl[65];scrtl[62]=0;
  static ASensorEvent event;

  while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0)
    {
      if(event.type == ASENSOR_TYPE_ACCELEROMETER)
	{
	    if((event.acceleration.x*event.acceleration.x+event.acceleration.y*event.acceleration.y+event.acceleration.z*event.acceleration.z)>121)return 1;
        //sprintf(scrtl,"X=%+6.5f Y=%+6.5f Z=%+6.5f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
	}
	if(event.type == ASENSOR_TYPE_MAGNETIC_FIELD)mx=event.magnetic.x,my=event.magnetic.y,mz=event.magnetic.z;
    }
  return 0;
}
