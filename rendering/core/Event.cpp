#include "core/Event.h"

void EventPool::start_all() {
    for (auto event: events_) {
        event->start();
    }
}

void EventPool::update_all() {
    for (auto event: events_) {
        event->update();
    }
}

