#pragma once

#include "easyloggingpp/easylogging++.h"

#ifndef LOCATION
	#ifdef __linux__
		#define LOCATION " [" << __PRETTY_FUNCTION__ << "] "
	#elif _WIN32
		#define LOCATION " [" << __FUNCSIG__ << "] "
	#else
		#define LOCATION " [" << __FUNCTION__ << "] "
	#endif
#endif
