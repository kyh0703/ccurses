#include "EventHandler.h"

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