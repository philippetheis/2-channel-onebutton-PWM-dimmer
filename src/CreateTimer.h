#include <Arduino.h>

// CreateTimer.cpp
// CreateTimer.h"
//
// Rev 
//  1.00   October 2,  2015 Functional code
//  1.01   October 4,  2015 Renamed variables and functions. Added: After() Remaining() Elapsed()
//  1.02   October 10, 2015 Added the Repeat option to the Start function
//  1.03   Cctober 10, 2015 Made some name changes
//
//=============================================================================
//                    F U N C T I O N    P R O T O T Y P E S
//=============================================================================
/*
CreateTimer::Start(unsigned long Interval);                      Starts your timer, requires an Interval 
CreateTimer::StartRepeat(unsigned long Interval, long Repeats);  Starts your timer, 
                                                                 requires an Interval, requires a "Repeat" value  
CreateTimer::Restart(void);                                      The timer Interval is restarted
CreateTimer::Enable(void);                                       Allow timer action
CreateTimer::Disable(void);                                      Disable timer action
CreateTimer::SetInterval(unsigned long, Interval);               Change timer Interval
CreateTimer::IsEnabled(void);                                    bool returns the timer enable status
CreateTimer::Remaining(void);	                                 unsigned long returns the ms left in this timer
CreateTimer::Repeat(void);                                       bool true when interval is reached, may repeat timing
                                                                      if you used StartRepeat() to start the timer
CreateTimer::Once(void);                                         bool true  when  interval is reached, false there after
CreateTimer::While(void);                                        bool true  until interval is reached, false there after
CreateTimer::After(void);                                        bool false until interval is reached, true there after  
*/

//                      C l a s s   C r e a t e T i m  e r  
 
class CreateTimer
{
public:
  //CreateTimer();
  //void begin();
  void Start(unsigned long Interval);  
  void StartRepeat(unsigned long Interval, long Repeats);  //1.02
  void Restart(void);
  void Enable(void);
  void Disable(void);
  void SetInterval(unsigned long Interval);
  unsigned long Remaining(void);	         //1.01
  bool IsEnabled(void);
  bool Repeat(void);
  bool Once(void);
  bool While(void);
  bool After(void);					         //1.01
  
private:
  unsigned long Elapsed();		            //1.01  No access to the user

  long _Repeats;                            //1.02
  bool enabled;
  unsigned long _Interval;
  unsigned long lastMillis; 
  unsigned long _temp;			           //temporary variable 1.01

};  // END of CreateTimer class  
// In C++ you must have a ; at the end of a class definition


