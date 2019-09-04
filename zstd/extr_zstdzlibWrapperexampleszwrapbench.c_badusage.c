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
 int g_displayLevel ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static int badusage(const char* programName)
{
    DISPLAYLEVEL(1, "Incorrect parameters\n");
    if (g_displayLevel >= 1) usage(programName);
    return 1;
}