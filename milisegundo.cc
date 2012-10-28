#include <unistd.h>
#include <sys/time.h>
long long cronousec(int startstop)
{
  static long long pre_time;
  struct timeval tv;

  if (startstop)
    {
      gettimeofday(&tv, NULL);      
      pre_time=tv.tv_sec*1000000+tv.tv_usec;
    }
  else
    {      
      gettimeofday(&tv, NULL);      
      return tv.tv_sec*1000000+tv.tv_usec - pre_time;
    }
    return 0;
}