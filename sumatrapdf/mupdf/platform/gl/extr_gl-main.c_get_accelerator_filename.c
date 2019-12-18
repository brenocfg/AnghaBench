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
 int PATH_MAX ; 
 int /*<<< orphan*/  convert_to_accel_path (char*,char*,size_t) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  realpath (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_accelerator_filename(char outname[], size_t len)
{
	char absname[PATH_MAX];
	if (!realpath(filename, absname))
		return 0;
	if (!convert_to_accel_path(outname, absname, len))
		return 0;
	return 1;
}