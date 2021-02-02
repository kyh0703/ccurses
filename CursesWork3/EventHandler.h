#pragma once
#include <algorithm>
#include <list>
#include <string>
using namespace std;

enum EventType
{
    KEYBORAD_EVENT,
    MOUSE_EVENT,
};

struct KeyEvent {
    EventType type;
    int code;
};

struct MouseEvent
{
    EventType type;
    int y, x;
};

class Listener
{
public:
    virtual ~Listener();
    virtual void OnNotify() = 0;
};

class EventDispatcher
{
public:
    virtual ~EventDispatcher() = 0;
    virtual void AddListener(Listener *pObs);
    virtual void RemoveListner(Listener *pObs);
    virtual void Dispatch();

protected:
    list<Listener *> _listeners;
};