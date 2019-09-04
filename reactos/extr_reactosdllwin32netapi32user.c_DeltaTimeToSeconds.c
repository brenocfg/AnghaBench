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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int QuadPart; scalar_t__ HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  TIMEQ_FOREVER ; 

__attribute__((used)) static
ULONG
DeltaTimeToSeconds(LARGE_INTEGER DeltaTime)
{
    LARGE_INTEGER Seconds;

    if (DeltaTime.QuadPart == 0)
        return 0;

    Seconds.QuadPart = -DeltaTime.QuadPart / 10000000;

    if (Seconds.HighPart != 0)
        return TIMEQ_FOREVER;

    return Seconds.LowPart;
}