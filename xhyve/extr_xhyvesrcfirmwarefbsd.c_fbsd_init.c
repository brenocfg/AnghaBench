#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* userboot; char* bootvolume; char* kernelenv; char* cons; } ;

/* Variables and functions */
 TYPE_1__ config ; 

void
fbsd_init(char *userboot_path, char *bootvolume_path, char *kernelenv,
	char *cons)
{
	config.userboot = userboot_path;
	config.bootvolume = bootvolume_path;
	config.kernelenv = kernelenv;
	config.cons = cons;
}