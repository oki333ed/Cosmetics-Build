#pragma once

#include <map>
#include <string>
#include <vector>

#include "Event.hpp"

namespace Cosmetics {
    class EventDispatcher {
    public:
        EventDispatcher() {}
        ~EventDispatcher() {
            for (auto el : _eventList) {
                for (auto e : el.second)
                    delete e;
            }
        }

        static EventDispatcher* get() {
            static EventDispatcher instance;
            return &instance;
        }

        void registerListener(IEvent* event) {
            if ( event )
            _eventList[event->getName()].push_back( event );
        }

        template <typename ..._args>
        void dispatch(const std::string& eventName, _args... a) {
            auto it_eventList = _eventList.find( eventName );
            if ( it_eventList == _eventList.end() )
                return;
            for ( auto ie : it_eventList->second )
            {
            if ( Event<_args...> * event = dynamic_cast<Event<_args...>*>( ie ) )
                event->trigger( a... );
            }
        }

    protected:
        std::map<std::string, std::vector<IEvent*>> _eventList;
    };
}