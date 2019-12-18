#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int msftime_t ;
struct TYPE_6__ {int quot; int rem; } ;
typedef  TYPE_1__ lldiv_t ;
struct TYPE_8__ {int QuadPart; } ;
struct TYPE_7__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_4__ freq ; 
 TYPE_1__ lldiv (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static msftime_t GetQPC(void)
{
    LARGE_INTEGER counter;

    if (!QueryPerformanceCounter(&counter))
        abort();

    lldiv_t d = lldiv(counter.QuadPart, freq.QuadPart);
    return (d.quot * 10000000) + ((d.rem * 10000000) / freq.QuadPart);
}