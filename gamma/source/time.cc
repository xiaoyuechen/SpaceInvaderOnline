// time.cc

#include "gamma.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace gamma {
   // static
   time time::now() {
      static LARGE_INTEGER start = {};
      static int64 factor = 0;
      if (!factor)
      {
         LARGE_INTEGER f = {};
         QueryPerformanceFrequency(&f);
         factor = f.QuadPart / 1000;
         QueryPerformanceCounter(&start);
      }

      LARGE_INTEGER now = {};
      QueryPerformanceCounter(&now);

      return time((now.QuadPart - start.QuadPart) / factor);
   }

   time::time()
      : tick_(0)
   {
   }

   time::time(int64 tick)
      : tick_(tick)
   {
   }

   time time::operator+(const time &rhs) {
      return time(tick_ + rhs.tick_);
   }

   time time::operator-(const time &rhs) {
      return time(tick_ - rhs.tick_);
   }

   bool time::operator<(const time &rhs) {
      return tick_ < rhs.tick_;
   }

   float time::as_seconds() const {
      return tick_ * 0.001f;
   }

   float time::as_milliseconds() const {
      return tick_ * 1.0f;
   }
} // !uu
