#ifndef _GameTime_H
#define _GameTime_H

//#include "../Frostbite_classes.h"

namespace fb
{

	class GameTime
	{
	public:
		DWORD m_ticks;						// 0x00
		DWORD m_tickFrequency;				// 0x04
		DWORD m_tickIndexInFrame;			// 0x08
		DWORD m_lastTickIndexInFrame;		// 0x0C
		DWORD m_tickCountInFrame;			// 0x10
		FLOAT m_deltaTime;					// 0x14
		FLOAT m_passedDeltaTimeInFrame;		// 0x18
		DOUBLE m_time;						// 0x1C
		INT m_useVariableDeltaTime;			// 0x24
	}; // 0x28

  class GameTimeSettings
  {
  public:
    PAD(0xC);
    float m_vsyncSubtractTime;      // 0xC
    float m_joinJobsTimeLimit;      // 0x10
    float m_yieldTimeLimit;         // 0x14
    float m_yieldTime;              // 0x18
    float m_maxInactiveVariableFps; // 0x1C
    float m_maxSimFps;              // 0x20
    float m_maxVariableFps;         // 0x24
    int m_clampTicks;               // 0x28
    float m_forceDeltaTime;         // 0x2C
    int m_forceDeltaTickCount;      // 0x30
    float m_timeScale;              // 0x34
    BYTE m_useWaitableTimer;    // 0x38

  public:
    static GameTimeSettings* Singleton()
    {
      return *(GameTimeSettings**)(0x022E39D0);
    }
  };

};

#endif