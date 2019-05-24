#pragma once

#include <math.h>
#include <vector>
#include <memory>

#if defined(_WIN32)
	#include <windows.h>
#endif

class System {
public:
	static long nanoTime()
	{
#if defined(WIN32)
		SYSTEMTIME time;
		GetSystemTime(&time);
		return static_cast<long>(((time.wSecond * 1000) + time.wMilliseconds) * pow(10, 6));
#else
		timespec ts;
   		// clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
   		clock_gettime(CLOCK_REALTIME, &ts);
		return ts.tv_sec *  pow(10, 9) + ts.tv_nsec;
#endif
	}

	static void arraycopy(std::vector<char> src, int srcPos, std::vector<char> dest, int destPos, int length)
	{
		for (int i = 0; i < length; i++) {
			dest[destPos + i] = src[srcPos + i];
		}
	}

    static long currentTimeMillis()
	{
        return nanoTime() * pow(10, 6);
    }
};
