#include "EventHandler.h"

void Event::AddHandler(const EventType &handler)
{
    _handlers.push_back(unique_ptr<EventType>(new EventType{handler}));
}

void Event::RemoveHandler(const EventType &handler)
{
    vector<unique_ptr<EventType>>::iterator it;
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

Event &Event::operator+=(const EventType &handler)
{
    AddHandler(handler);
    return *this;
}

Event &Event::operator-=(const EventType &handler)
{
    RemoveHandler(handler);
    return *this;
}

void Event::NotifyHandlers()
{
    vector<unique_ptr<EventType>>::iterator it;
    for (it = _handlers.begin(); it != _handlers.end(); ++it)
    {
        // if (*it)
        //     (*(*it))();
    }
}

void Event::NotifyHandlers()
{
    vector<unique_ptr<EventType>>::iterator it;
    for (it = _handlers.begin(); it != _handlers.end(); ++it)
    {
        EventType = it;
        if (*it != nullptr)
            (*(*it))();
    }
}


출처: https://vallista.tistory.com/entry/C-c에-있는-eventdelegate-system-구현 [VallistA]
출처: https://vallista.tistory.com/entry/C-c에-있는-eventdelegate-system-구현 [VallistA]

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