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
typedef  size_t cmsUInt32Number ;
struct TYPE_3__ {size_t nEntries; int* Table16; } ;
typedef  TYPE_1__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
cmsBool IsDegenerated(const cmsToneCurve* g)
{
    cmsUInt32Number i, Zeros = 0, Poles = 0;
    cmsUInt32Number nEntries = g ->nEntries;

    for (i=0; i < nEntries; i++) {

        if (g ->Table16[i] == 0x0000) Zeros++;
        if (g ->Table16[i] == 0xffff) Poles++;
    }

    if (Zeros == 1 && Poles == 1) return FALSE;  // For linear tables
    if (Zeros > (nEntries / 20)) return TRUE;  // Degenerated, many zeros
    if (Poles > (nEntries / 20)) return TRUE;  // Degenerated, many poles

    return FALSE;
}