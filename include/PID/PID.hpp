#ifndef __PID
#define __PID

namespace PID {
    class PID_System {
        public:
        float error = 0;
        float kp = 0;
        float ki = 0;
        float kd = 0;
        float maxCumulativeError = 0;
        float minSettleError = 0, defaultMinSettleError = 0;
        float minSettleTime = 0, defaultMinSettleTime = 0;
        float timeout = 0, defaultTimeout = 0;
        float cumulativeError = 0;
        float prevError = 0;
        float output = 0;
        float timeSpentSettled = 0;
        float timeSpentRunning = 0;

        float loopTime = 10;

        bool holdIntegralAtEnd = false;

        PID_System(float error, float kp, float ki, float kd, float maxCumulativeError, float minSettleError, float minSettleTime, float timeout, float loopTime = 10, bool holdIntegralAtEnd = false);

        PID_System(float error, float kp, float ki, float kd, float maxCumulativeError, float loopTime = 10, bool holdIntegralAtEnd = false);

        // System Functions
        float compute(float error);
        bool isSettled();
        void resetSystem();

        // Util Functions
        void setkConstants(float kp, float ki, float kd, float maxCumulativeError);
        void setStopConditionConstants(float minSettleError, float minSettleTime, float timeout);
        // void 
    };
}

#endif //__PID