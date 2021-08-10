// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_EVENT_H
#define RENDERING_CORE_EVENT_H

#include <list>

class ILoopEvent {
   public:
    void start();
    void update();
};

class EventPool {
   public:
    static EventPool &instance() {
        static EventPool inst;
        return inst;
    }

    EventPool(const EventPool &) = delete;
    EventPool &operator=(const EventPool &) = delete;
    void add_event(ILoopEvent &event) { events_.push_back(&event); }
    void start_all();
    void update_all();

   private:
    EventPool() = default;
    ~EventPool() = default;

    std::list<ILoopEvent *> events_;
};

#endif  // RENDERING_CORE_EVENT_H