#pragma once

#define RS_DONT_LOG // Prevent annoying log spam
#include "../RocketSim/src/RocketSim.h"

// Define our own log
#define RG_LOG(s) { std::cout << s << std::endl; }

#define RG_NO_COPY(className) \
className(const className&) = delete;  \
className& operator= (const className&) = delete