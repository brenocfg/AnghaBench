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
struct chmcLzxcControlData {int size; int version; int resetInterval; int windowSize; int windowsPerReset; scalar_t__ unknown_18; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

void chmc_control_data_init(struct chmcLzxcControlData *control_data)
{
	control_data->size = 6;
	memcpy(control_data->signature, "LZXC", 4);
	control_data->version = 2;
	control_data->resetInterval = 2;
	control_data->windowSize = 2;
	control_data->windowsPerReset = 1;
	control_data->unknown_18 = 0;
}