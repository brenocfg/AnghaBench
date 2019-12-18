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
 void* fz_atoi (char const*) ; 
 char* strchr (char const*,char) ; 
 void* x_resolution ; 
 void* y_resolution ; 

__attribute__((used)) static void
read_resolution(const char *arg)
{
	char *sep = strchr(arg, ',');

	if (sep == NULL)
		sep = strchr(arg, 'x');
	if (sep == NULL)
		sep = strchr(arg, ':');
	if (sep == NULL)
		sep = strchr(arg, ';');

	x_resolution = fz_atoi(arg);
	if (sep && sep[1])
		y_resolution = fz_atoi(arg);
	else
		y_resolution = x_resolution;
}