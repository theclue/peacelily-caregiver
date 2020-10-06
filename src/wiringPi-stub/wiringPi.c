/*
 * wiringPi.c:
 *  Arduino like Wiring library for the Raspberry Pi.
 *  This is a stub for Linux.
 ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include "wiringPi.h"

const char *piModelNames    [16] = { "Stubbed wiringPi" };
const char *piRevisionNames [16] = { "n/a" };
const char *piMakerNames    [16] = { "cdelord.fr" };
const int   piMemorySize    [ 8] = { 0 };

struct wiringPiNodeStruct *wiringPiNodes = NULL;

// Internal

int wiringPiFailure (int fatal, const char *message, ...)
{
    va_list ap;
    va_start(ap, message);
    vprintf(message, ap);
    va_end(ap);
    exit(fatal);
}

// Core wiringPi functions

struct wiringPiNodeStruct *wiringPiFindNode (int pin) ;
struct wiringPiNodeStruct *wiringPiNewNode  (int pinBase, int numPins) ;

int  wiringPiSetup       (void) { return 0; }
int  wiringPiSetupSys    (void) { return 0; }
int  wiringPiSetupGpio   (void) { return 0; }
int  wiringPiSetupPhys   (void) { return 0; }

void pinModeAlt          (int pin, int mode) ;
void pinMode             (int pin, int mode) { }
void pullUpDnControl     (int pin, int pud) ;
int  digitalRead         (int pin)
{
    static int pinDec[1024] = {0};
    static int pinVal[1024] = {0};
    if (pinDec[pin] > 0)
    {
        pinDec[pin]--;
    }
    else
    {
        switch (pin)
        {
            case 2:
                pinVal[pin] = random()%2 ? HIGH : LOW;
                pinDec[pin] = 500;
                break;
            default:
                wiringPiFailure(1, "The pin %d is not simulated.", pin);
                break;
        }
    }
    return !!pinVal[pin];
}
void digitalWrite        (int pin, int value)
{
    //printf("digitalWrite(pin = %d, value = %d)\n", pin, value);
}
void pwmWrite            (int pin, int value) ;
int  analogRead          (int pin) ;
void analogWrite         (int pin, int value) ;

// PiFace specifics
//  (Deprecated)

int  wiringPiSetupPiFace (void) { return 0; }
int  wiringPiSetupPiFaceForGpioProg (void) { return 0; }    // Don't use this - for gpio program only

// On-Board Raspberry Pi hardware specific stuff

         int  piBoardRev          (void) { return 0; }
         void piBoardId           (int *model, int *rev, int *mem, int *maker, int *overVolted)
         {
             *model = 0;
             *rev = 0;
             *mem = 0;
             *maker = 0;
             *overVolted = 0;
         }
         int  wpiPinToGpio        (int wpiPin) ;
         int  physPinToGpio       (int physPin) ;
         void setPadDrive         (int group, int value) ;
         int  getAlt              (int pin) ;
         void pwmToneWrite        (int pin, int freq) { }
         void digitalWriteByte    (int value) ;
unsigned int  digitalReadByte     (void) ;
         void pwmSetMode          (int mode) { };
         void pwmSetRange         (unsigned int range) ;
         void pwmSetClock         (int divisor) ;
         void gpioClockSet        (int pin, int freq) ;

// Interrupts
//  (Also Pi hardware specific)

int  waitForInterrupt    (int pin, int mS) ;
int  wiringPiISR         (int pin, int mode, void (*function)(void)) ;

// Threads

int  piThreadCreate      (void *(*fn)(void *)) ;
void piLock              (int key) ;
void piUnlock            (int key) ;

// Schedulling priority

int piHiPri (const int pri) ;

// Extras from arduino land

void         delay             (unsigned int howLong) ;

void delayMicrosecondsHard (unsigned int howLong)
{
  struct timeval tNow, tLong, tEnd ;

  gettimeofday (&tNow, NULL) ;
  tLong.tv_sec  = howLong / 1000000 ;
  tLong.tv_usec = howLong % 1000000 ;
  timeradd (&tNow, &tLong, &tEnd) ;

  while (timercmp (&tNow, &tEnd, <))
    gettimeofday (&tNow, NULL) ;
}

void delayMicroseconds (unsigned int howLong)
{
  struct timespec sleeper ;
  unsigned int uSecs = howLong % 1000000 ;
  unsigned int wSecs = howLong / 1000000 ;

  /**/ if (howLong ==   0)
    return ;
  else if (howLong  < 100)
    delayMicrosecondsHard (howLong) ;
  else
  {
    sleeper.tv_sec  = wSecs ;
    sleeper.tv_nsec = (long)(uSecs * 1000L) ;
    nanosleep (&sleeper, NULL) ;
  }
}

unsigned int millis            (void) ;
unsigned int micros            (void) ;