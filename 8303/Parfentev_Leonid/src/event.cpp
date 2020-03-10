#include "map.hpp"
#include "unit.hpp"
#include "event.hpp"


namespace events {

    void
    EventLoop::process()
    {
        while (!_events.empty()) {
            Event *ev = _events.front();
            _events.pop();
            ev->execute(this);
            delete ev;
        }
    }

    void
    Damage::execute(EventLoop *el)
    {
        el->handle(this);

        BaseUnit *unit = iter->unit();
        unit->takeDamage(dmg);
        if (!unit->alive())
            el->push(new Death {iter});
    }

    void
    Death::execute(EventLoop *el)
    {
        el->handle(this);
        delete iter.map()->removeFrom(iter.point());
    }

}
