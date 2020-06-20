#ifndef _H_MAP_HPP
#define _H_MAP_HPP

#include "rectmap.hpp"

// Map interface doesn’t know about cells -- instead, it only cares
// about certain kinds of Placeables


class Map;

class Unit;
class Base;

class MapIter {
    RectMapIter _it;

    friend class Map;

    MapIter(RectMapIter r)
        :_it{r} {}

public:
    static MapIter makeNull()
    {
        return MapIter{RectMapIter::makeNull()};
    }

    bool operator==(const MapIter &o) const { return _it == o._it; }
    bool operator!=(const MapIter &o) const { return _it != o._it; }

    int x() const { return _it.x(); }
    int y() const { return _it.y(); }
    Vec2 point() const { return _it.point(); }

    bool null() const { return _it.null(); }
    bool valid() const { return _it.valid(); }

    void shift(Vec2 dxy) { _it.moveTo(point().shifted(dxy)); }
    MapIter shifted(Vec2 dxy) const
    {
        return MapIter{_it.otherAt(point().shifted(dxy))};
    }

    void moveTo(Vec2 xy) { _it.moveTo(xy); }
    MapIter otherAt(Vec2 xy) const
    {
        return MapIter{_it.otherAt(xy)};
    }

    void advance(int d) { _it.advance(d); }
    MapIter advanced(int d) const
    {
        return MapIter{_it.advanced(d)};
    }

    Unit *unit() const;
    bool occupied() { return unit() != nullptr; }
    // other placeable types in the future
};

class Map {
    RectMap _rm;
    int _units_count = 0;
    int _units_max = -1;

public:
    Map(int w, int h)
        :_rm{w, h} {}

    int width() const { return _rm.width(); }
    int height() const { return _rm.height(); }
    MapIter iterAt(Vec2 pt) { return MapIter{_rm.iterAt(pt)}; }
    MapIter iterAt(int x, int y) { return iterAt({x, y}); }

    MapIter begin() { return iterAt(0, 0); }
    MapIter end() { return iterAt(0, height()); }

    MapIter addUnit(Unit *u, Vec2 pt);
    Unit *removeUnitAt(Vec2 at);
    Unit *removeUnitAt(MapIter iter)
    {
        return removeUnitAt(iter.point());
    }

    int maxUnitsCount() const { return _units_max; }
    bool setMaxUnitsCount(int x)
    {
        if (_units_count > x)
            return false;
        _units_max = x;
        return true;
    }
    int unitsCount() const { return _units_count; }
};

#endif