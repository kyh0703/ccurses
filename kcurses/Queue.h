#pragma once
#include <errno.h>
#include <pthread.h>
#include <queue>
#include <sys/time.h>
#include <time.h>

template <typename T>
class Queue
{
public:
    Queue()
    {
        pthread_mutex_init(&_mutex, NULL);
        pthread_cond_init(&_cond, NULL);
    }

    ~Queue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

    void push(T &item)
    {
        pthread_mutex_lock(&_mutex);
        _queue.push((T)item);
        pthread_cond_signal(&_cond);
        pthread_mutex_unlock(&_mutex);
    }

    void pop(T &item)
    {
        pthread_mutex_lock(&_mutex);
        while (_queue.empty())
            pthread_cond_wait(&_cond, &_mutex);

        item = _queue.front();
        _queue.pop();
        pthread_mutex_unlock(&_mutex);
    }

    int GetSize(void)
    {
        pthread_mutex_lock(&_mutex);
        int size = _queue.size();
        pthread_mutex_unlock(&_mutex);
        return size;
    }

private:
    std::queue<T> _queue;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};
