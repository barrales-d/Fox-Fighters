#include "event_timer.h"

namespace bts
{
    // --------------------------------------------------------
    Timer::Timer(float interval) :
        interval(interval), elapseTime(0.0f), active(true) {
    }

    void Timer::Update(float dt) {
        if (!active) return;
        elapseTime += dt;
    }

    bool Timer::IsReady() {
        if (elapseTime >= interval) {
            this->Reset();
            return true;
        }
        return false;
    }
    // --------------------------------------------------------

    // --------------------------------------------------------
    EventTimer::EventTimer(float interval, ITimerListener* listener)
        : timer(interval), listener(listener) {
    }

    void EventTimer::Update(float dt) {
        if (timer.IsReady() && listener) {
            listener->OnTimerFinished();
        }
        timer.Update(dt);
    }

    void EventTimer::Start() { timer.Start(); }
    void EventTimer::Stop() { timer.Stop(); }
    // --------------------------------------------------------
}