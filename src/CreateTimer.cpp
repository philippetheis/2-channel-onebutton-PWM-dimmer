//*****************************************************************************

#include "CreateTimer.h"

//
//*****************************************************************************
//                    C l a s s   C r e a t e T i m e r  
//*****************************************************************************
//Constructor
/*
CreateTimer::CreateTimer()
{
} // END of CreateTimer()
*/

//********************************************************** 
//Initialization
/*
void CreateTimer::begin()
{
} // END of begin()
*/

// ********************************************************** 
// Initialize the timer. This starts the timing for this timer.
void CreateTimer::Start(unsigned long Interval)
{
  _Interval = Interval;
  _Repeats = -1;               //1.02
  lastMillis = millis();  
  enabled = true;
} // END of Start()

//********************************************************** 
// Initialize the timer. This starts the timing for this timer. "Repeats" is the number of repeating intervals.  
void CreateTimer::StartRepeat(unsigned long Interval,long Repeats)   //1.02
{
  _Interval = Interval;
  _Repeats = Repeats;            
  lastMillis = millis();  
  enabled = true;
} // END of StartRepeat()

//********************************************************** 
// Enable the timer
void CreateTimer::Enable(void)
{
  enabled = true;  
} // END of Enable()

//********************************************************** 
// Disable the timer
void CreateTimer::Disable(void)
{
  enabled = false;  
} // END of Disable()

//********************************************************** 
// Return true if the timer is enabled false if disabled
bool CreateTimer::IsEnabled(void)
{
  return enabled;
} // END of IsEnabled()

//********************************************************** 
// Restart the timing sequence
void CreateTimer::Restart(void)
{
  lastMillis = millis();  
} // END of Restart()

//********************************************************** 
//
unsigned long CreateTimer::Elapsed(void)	//1.01
{
  return millis() - lastMillis;
} // END of Elapsed()

//********************************************************** 
// Return the time left in the timer: >=0 time left <= interval
unsigned long CreateTimer::Remaining(void)	//1.01
{
  _temp = _Interval - Elapsed();
  if(_Interval >= _temp)
  {
    return _temp;
  }
  else
  {
    return 0;  //under flow, return zero
  }
} // END of Remaining()

//********************************************************** 
// Change the timer interval 
void CreateTimer::SetInterval(unsigned long Interval)
{
  _Interval = Interval;  
} // END of SetInterval()

//********************************************************** 
// Return false in the interval, return true at the end of the interval, then restart the timer
bool CreateTimer::Repeat(void)
{ 
  if(enabled && Elapsed() >= _Interval)
  {
    //_Repeats being negative indicates this is a continuous timer.
    if(_Repeats < 0)  //1.02
    {
      lastMillis = lastMillis + _Interval;
      return true;
    }
    //_Repeats being positive, indicates this is a timer that "Repeats" a given number of times.   1.02
	//2,147,483,647 is the maximum number the timer can repeat
    else if(_Repeats-- != 0)
    {
      lastMillis = lastMillis + _Interval;
      return true;
    }
    else
    {
      //We have now completed _Repeats number of Intervals 
      enabled = false;
      return false;	  
    }
  }

  return false;
} // END of Repeat()

//********************************************************** 
// Return false in the interval, return true "at" the end of the interval, then false there after
bool CreateTimer::Once(void)
{
  if(enabled && Elapsed() >= _Interval)
  {
    enabled = false;
    return true;
  }  

  return false;
} // END of Once()

//**********************************************************
// Return true while in the interval and false after the interval has expired 
bool CreateTimer::While(void)
{
  if(enabled && Elapsed() <= _Interval)
  {
    return true;
  }  

  enabled = false;
  return false;
} // END of While()

//**********************************************************
// Return false in the interval and true after the interval has expired 
bool CreateTimer::After(void)	//1.01
{
  if(enabled && Elapsed() <= _Interval)
  {
    return false;
  }  

  enabled = false;
  return true;
} // END of After()


// END of CreateTimer class definition
