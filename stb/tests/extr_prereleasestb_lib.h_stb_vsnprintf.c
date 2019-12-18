#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int _vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int stb_vsnprintf(char *s, size_t n, const char *fmt, va_list v)
{
   int res;
   #ifdef _WIN32
   // Could use "_vsnprintf_s(s, n, _TRUNCATE, fmt, v)" ?
   res = _vsnprintf(s,n,fmt,v);
   #else
   res = vsnprintf(s,n,fmt,v);
   #endif
   if (n) s[n-1] = 0;
   // Unix returns length output would require, Windows returns negative when truncated.
   return (res >= (int) n || res < 0) ? -1 : res;
}