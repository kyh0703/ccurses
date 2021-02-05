#include "EventHandler.h"
int EventHandler::counter = 0;

EventHandler::EventHandler()
{
    id = 0;
}

EventHandler::EventHandler(const Func &func)
{
    _func = func;
    id = ++EventHandler::counter;
}

void EventHandler::operator()()
{
    _func();
}

void EventHandler::operator=(const Func &func)
{
    _func = func;
    id = ++EventHandler::counter;

    // if (_func == nullptr)
    // {
    //     _func = func;
    //     id = ++EventHandler::counter;
    // }
}

bool EventHandler::operator==(const EventHandler &del)
{
    return id == del.id;
}

bool EventHandler::operator!=(nullptr_t)
{
    return _func != nullptr;
}

void Event::AddHandler(const EventHandler &handler)
{
    _handlers.push_back(unique_ptr<EventHandler>(new EventHandler{handler}));
}

void Event::RemoveHandler(const EventHandler &handler)
{
    vector<unique_ptr<EventHandler>>::iterator it;
    for (it = _handlers.begin(); it != _handlers.end(); ++it)
    {
        if (*(*it) == handler)
        {
            _handlers.erase(it);
            break;
        }
    }
}

void Event::operator()()
{
    NotifyHandlers();
}

Event &Event::operator+=(const EventHandler &handler)
{
    AddHandler(handler);
    return *this;
}

Event &Event::operator-=(const EventHandler &handler)
{
    RemoveHandler(handler);
    return *this;
}

void Event::NotifyHandlers()
{
    vector<unique_ptr<EventHandler>>::iterator it;
    for (it = _handlers.begin(); it != _handlers.end(); ++it)
    {
        if (*it != nullptr)
            (*(*it))();
    }
}

void EventDispatcher::AddListener(Listener *pObs)
{
    _listeners.push_front(pObs);
}

void EventDispatcher::RemoveListner(Listener *pObs)
{
    list<Listener *>::iterator it;
    it = find(_listeners.begin(), _listeners.end(), pObs);
    if (it != _listeners.end())
        _listeners.erase(it);
}

void EventDispatcher::Dispatch()
{
    list<Listener *>::iterator it;
    for (it = _listeners.begin(); it != _listeners.end(); ++it)
        (*it)->OnNotify();
}