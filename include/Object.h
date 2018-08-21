//
// Created by Jie on 2018/8/4.
//

#ifndef UNTITLED_OBJECT_H
#define UNTITLED_OBJECT_H


#include <sol2/sol.hpp>

#ifdef DEBUG
#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#endif

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "nlohmann/json.hpp"


#if defined(__GNUC__)
#include <cxxabi.h>
#endif

#include <map>
#include <vector>
#include <memory>
#include <typeindex>

using namespace nlohmann;

class Mediator;

class Object {
public:
	int id;

	virtual const std::string tostring() const;

	virtual void setMediator(Mediator *_mediator);
	virtual void send(json message);
	virtual void onMessage(json message);

protected:
	Mediator * mediator;
	std::shared_ptr<spdlog::logger> console;
};

#endif //UNTITLED_OBJECT_H
