#pragma once

#include <string>

namespace Cosmetics {
    class IEvent {
    public:
        virtual ~IEvent() {}

        virtual const std::string& getName() const = 0;
    };

    template <typename ..._args>
    class Event : public IEvent {
    public:
        using _callback = std::function<void(_args...)>;

        explicit Event(const std::string& name, const _callback& cb) : _name(name), _cbFunc(cb) {}
        ~Event() {}

        virtual const std::string& getName() const override { return this->_name; }
        void trigger(_args... a) { this->_cbFunc(a...); }

    protected:
        std::string _name;
        _callback const _cbFunc;
    };
}