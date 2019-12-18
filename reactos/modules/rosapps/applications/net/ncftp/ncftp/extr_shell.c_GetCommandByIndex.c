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
typedef  int /*<<< orphan*/ * CommandPtr ;

/* Variables and functions */
 int /*<<< orphan*/ * gCommands ; 
 scalar_t__ gNumCommands ; 
 int /*<<< orphan*/ * kNoCommand ; 

CommandPtr
GetCommandByIndex(const int i)
{
	if ((i < 0) || (i >= (int) gNumCommands))
		return (kNoCommand);
	return (&gCommands[i]);
}