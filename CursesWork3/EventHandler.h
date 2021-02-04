#pragma once
#include <algorithm>
#include <list>
#include <string>
#include <memory>
using namespace std;

enum EventType
{
    KEYBORAD_EVENT,
    MOUSE_CLICKED,
    MOUSE_LEAVE,
    MOUSE_PRESS,
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

class Event
{
public:
    void AddHandler(const EventType &handler);
    void RemoveHandler(const EventType &handler);
    void operator()(void);
    Event &operator+=(const EventType &handler);
    Event &operator-= (const EventType &handler);

private:
    void NotifyHandlers();
    vector<unique_ptr<EventType>> _handlers;
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