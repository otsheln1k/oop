#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <queue>

#include "map.hpp"
#include "unit.hpp"


namespace events {

    class EventLoop;
    class Event {
    public:
        virtual void execute(EventLoop *) =0;

        virtual ~Event() {}
    };

    struct Damage : public Event {
        int dmg;
        MapIter iter;

        Damage(int d, MapIter iter) :dmg{d}, iter{iter} {}

        virtual void
        execute(EventLoop *) override;

        BaseUnit *target() const { return iter->unit(); }
    };

    struct Death : public Event {
        MapIter iter;

        Death(MapIter iter) :iter{iter} {}

        virtual void
        execute(EventLoop *) override;
    };



    class EventLoop {
        std::queue<Event *> _events {};

    public:
        void push(Event *e) { _events.push(e); }
        Event *front() const { return _events.front(); }
        bool empty() const { return _events.empty(); }

        void process();

        virtual void handle(Damage *) {}
        virtual void handle(Death *) {}
    };

}

#endif
