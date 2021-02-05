#pragma once
#include <algorithm>
#include <list>
#include <string>
#include <memory>
#include <functional>
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

class EventHandler
{
public:
    using Func = function<void()>;

private:
    Func _func;

public:
    int id;
    static int counter;

    EventHandler();
    EventHandler(const Func &func);
    void operator()();
    void operator=(const Func &func);
    bool operator==(const EventHandler &del);
    bool operator!=(nullptr_t);
};

class Event
{
public:
    void AddHandler(const EventHandler &handler);
    void RemoveHandler(const EventHandler &handler);
    void operator()();
    Event &operator+=(const EventHandler &handler);
    Event &operator-=(const EventHandler &handler);

private:
    void NotifyHandlers();
    vector<unique_ptr<EventHandler>> _handlers;
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