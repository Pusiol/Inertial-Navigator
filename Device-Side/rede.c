#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

char *r = 
  "HTTP/1.0 200 OK\n"
  "Server:AwesomeAndroidHackingServer\n"
  "Content-type: text/html\n\n"
  "<html><body><h1>Hello Android                                        kkk     </h1></body></html>\n";


#include <stdio.h>
#include <unistd.h>
#include <android/sensor.h>
#include <android/looper.h>

ASensorEventQueue* sensorEventQueue;

static int get_sensor_events(int fd, int events, void* data);

int main (int argc, char *argv[])
{
//========================================
  struct sockaddr_in   server, client;
  socklen_t            len = sizeof (struct sockaddr_in);
  int  s,s1;

  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  s = socket (PF_INET, SOCK_STREAM, 0);
  bind (s, (struct sockaddr *) &server, sizeof (server));
  listen (s, 10);
//========================================


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
  sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, 0, NULL, NULL);
  ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);

  while (1)
    {

      get_sensor_events (0, 0,NULL);
      sleep (1);
printf("==v==\n");

      //if(s1 = accept (s, (struct sockaddr *)&client, &len)){
      //write (s1, r, strlen(r));
      //close (s1);}

      
    }
}



static int fire = 1;
int c;
char *scrtl="                                      ";

static int get_sensor_events(int fd, int events, void* data) 
{
  static ASensorEvent event;
printf("==1==\n");
  //while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) 
    {printf("==2==\n");
      if(event.type == ASENSOR_TYPE_ACCELEROMETER) 
  {printf("==3==\n");
        sprintf(scrtl,"(%04d) %+6.5f %+6.5f %+6.5f %lld\n", 7, event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);//cnt, evebt,type,
        for(c=125;c<135;c++)*(r+c)=*(scrtl+c-125);
          printf("(%04d) %+6.5f %+6.5f %+6.5f %lld\n", 7, event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
  }
    }
  //should return 1 to continue receiving callbacks, or 0 to unregister
  return 1;
}