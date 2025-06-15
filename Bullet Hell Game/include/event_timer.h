#pragma once
#ifndef __EVENT_TIMER_H__
#define __EVENT_TIMER_H__

namespace bts
{
    // --------------------------------------------------------
    class Timer {
    public:
        Timer(float interval);

        void Update(float dt);
        bool IsReady();

        void Reset() { elapseTime = 0.0f; }
        void Stop() { active = false; }
        void Start() { active = true; }
        bool IsActive() { return active; }

        void SetInterval(float new_interval) { interval = new_interval; this->Reset(); }
        float GetInterval() const { return interval; }

    private:
        float interval;
        float elapseTime;
        bool active;
    };
    // --------------------------------------------------------

    // --------------------------------------------------------
    class ITimerListener {
    public:
        virtual void OnTimerFinished() = 0;
    };

    class EventTimer {
    public:
        EventTimer(float interval, ITimerListener* listener);
        void Update(float dt);

        void Stop();
        void Start();

        void SetInterval(float new_interval) { timer.SetInterval(new_interval); }
        float GetInterval() const { return timer.GetInterval(); }

    private:
        Timer timer;
        ITimerListener* listener;
    };
    // --------------------------------------------------------
}


#endif // !__EVENT_TIMER_H__
