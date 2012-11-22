#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
long long cronomsec(int startstop)
{
  static long long pre_time;
  struct timeval tv;

  if (startstop)
    {
      gettimeofday(&tv, NULL);      
      pre_time=tv.tv_sec*1000+tv.tv_usec/1000;
    }
  else
    {      
      gettimeofday(&tv, NULL);      
      return tv.tv_sec*1000+tv.tv_usec/1000 - pre_time;
    }
    return 0;
}

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