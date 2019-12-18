#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {void* dwHighDateTime; void* dwLowDateTime; } ;
typedef  TYPE_1__* LPFILETIME ;
typedef  int LONGLONG ;
typedef  void* DWORD ;

/* Variables and functions */
 int Int32x32To64 (int /*<<< orphan*/ ,int) ; 

void UnixTimeToFileTime(time_t t, LPFILETIME pft)
{
    /* Windows specific.  From MS Q167296 */
    /* 'time_t' represents seconds since midnight January 1, 1970 UTC (coordinated universal time). */
    /* 64-bit FILETIME structure represents the number of 100-nanosecond intervals since January 1, 1601 UTC (coordinate universal time). */
    LONGLONG ll; /* LONGLONG is a 64-bit value. */
    ll = Int32x32To64(t, 10000000) + 116444736000000000;
    pft->dwLowDateTime = (DWORD)ll;
    /* pft->dwLowDateTime = (DWORD)(0x00000000ffffffff & ll); */
    pft->dwHighDateTime = (DWORD)(ll >> 32);
}