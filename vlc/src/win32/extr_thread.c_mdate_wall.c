#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {int /*<<< orphan*/  QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_6__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
typedef  TYPE_2__ FILETIME ;

/* Variables and functions */
 int CLOCK_FREQ ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_2__*) ; 
 int /*<<< orphan*/  GetSystemTimePreciseAsFileTime (TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MSFTIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 

__attribute__((used)) static vlc_tick_t mdate_wall (void)
{
    FILETIME ts;
    ULARGE_INTEGER s;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) && (!VLC_WINSTORE_APP || _WIN32_WINNT >= 0x0A00)
    GetSystemTimePreciseAsFileTime (&ts);
#else
    GetSystemTimeAsFileTime (&ts);
#endif
    s.LowPart = ts.dwLowDateTime;
    s.HighPart = ts.dwHighDateTime;
    /* hundreds of nanoseconds */
    static_assert ((10000000 % CLOCK_FREQ) == 0, "Broken frequencies ratio");
    return VLC_TICK_FROM_MSFTIME(s.QuadPart);
}