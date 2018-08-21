#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "nlohmann/json.hpp"

using namespace nlohmann;

class Object;

class Mediator {
public:
	virtual void sendMessage(json message, Object *obj) {}
	virtual void setRenter(Object *renter) {}
	virtual void setLandlord(Object *landlord) {}
};

#endif // MEDIATOR_H
