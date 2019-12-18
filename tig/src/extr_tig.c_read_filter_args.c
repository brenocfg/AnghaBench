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
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int ERROR_OUT_OF_MEMORY ; 
 int SUCCESS ; 
 scalar_t__ argv_append (char const***,char*) ; 

__attribute__((used)) static enum status_code
read_filter_args(char *name, size_t namelen, char *value, size_t valuelen, void *data)
{
	const char ***filter_args = data;

	return argv_append(filter_args, name) ? SUCCESS : ERROR_OUT_OF_MEMORY;
}