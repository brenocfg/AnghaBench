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
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,unsigned int) ; 
 int /*<<< orphan*/  longCommandWArg (char const**,char*) ; 
 unsigned int readU32FromChar (char const**) ; 

__attribute__((used)) static unsigned parseLegacyParameters(const char* stringPtr, unsigned* selectivity)
{
    if (!longCommandWArg(&stringPtr, "s=") && !longCommandWArg(&stringPtr, "selectivity=")) { return 0; }
    *selectivity = readU32FromChar(&stringPtr);
    if (stringPtr[0] != 0) return 0;
    DISPLAYLEVEL(4, "legacy: selectivity=%u\n", *selectivity);
    return 1;
}