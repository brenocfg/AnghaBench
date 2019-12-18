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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*) ; 
 scalar_t__ longCommandWArg (char const**,char*) ; 
 scalar_t__ readU32FromChar (char const**) ; 

__attribute__((used)) static unsigned parseAdaptParameters(const char* stringPtr, int* adaptMinPtr, int* adaptMaxPtr)
{
    for ( ; ;) {
        if (longCommandWArg(&stringPtr, "min=")) { *adaptMinPtr = (int)readU32FromChar(&stringPtr); if (stringPtr[0]==',') { stringPtr++; continue; } else break; }
        if (longCommandWArg(&stringPtr, "max=")) { *adaptMaxPtr = (int)readU32FromChar(&stringPtr); if (stringPtr[0]==',') { stringPtr++; continue; } else break; }
        DISPLAYLEVEL(4, "invalid compression parameter \n");
        return 0;
    }
    if (stringPtr[0] != 0) return 0; /* check the end of string */
    if (*adaptMinPtr > *adaptMaxPtr) {
        DISPLAYLEVEL(4, "incoherent adaptation limits \n");
        return 0;
    }
    return 1;
}