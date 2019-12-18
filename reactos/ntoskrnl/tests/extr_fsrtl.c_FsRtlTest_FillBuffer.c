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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int ULONG ;
struct TYPE_3__ {scalar_t__ QuadPart; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__* PULONGLONG ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */

void FsRtlTest_FillBuffer(LARGE_INTEGER Start, ULONG Length, PVOID Buffer) {
    ULONG i = 0;
    PULONGLONG Index = (PULONGLONG) Buffer;

    for (i=0; i<Length/sizeof(ULONGLONG); i++) {
        Index[i] = Start.QuadPart + i;
    }

    return;
 }