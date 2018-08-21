
#include "Object.h"
#include "Mediator.h"

const std::string Object::tostring() const {
#if defined(__GNUC__)
	return abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr);
#else
	return typeid(*this).name();
#endif
}

void Object::setMediator(Mediator *_mediator) {
	mediator = _mediator;
}

void Object::send(json message) {
	mediator->sendMessage(message, this);
}

void Object::onMessage(json message) {
	
}