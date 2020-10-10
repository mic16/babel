/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/
#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <chrono>

template <typename T>
class Clock
{
public:
    Clock() {}
    ~Clock() {}

    T getElapsedTime() const
    {
        if (this->running)
        {
            std::chrono::duration<T> point = this->elapsedTime + (std::chrono::high_resolution_clock::now() - this->_startTime);
            return point.count();
        }
        else
        {
            return this->elapsedTime.count();
        }
    }

    void reset()
    {
        this->_startTime = std::chrono::high_resolution_clock::now();
        this->elapsedTime = std::chrono::duration<T>::zero();
    }

    void start()
    {
        if (!this->running)
        {
            this->elapsedTime = this->elapsedTime.zero();
            this->running = true;
            this->_startTime = std::chrono::high_resolution_clock::now();
        }
    }

    void stop()
    {
        if (this->running)
        {
            this->running = false;
            this->elapsedTime += std::chrono::high_resolution_clock::now() - this->_startTime;
        }
    }

private:
    bool running = false;
    std::chrono::high_resolution_clock::time_point _startTime;
    std::chrono::duration<T> elapsedTime;
};

#endif /* !CLOCK_HPP_ */