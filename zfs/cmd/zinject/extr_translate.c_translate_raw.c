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
struct TYPE_3__ {scalar_t__ zi_start; scalar_t__ zi_end; int /*<<< orphan*/  zi_level; int /*<<< orphan*/  zi_object; int /*<<< orphan*/  zi_objset; } ;
typedef  TYPE_1__ zinject_record_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
translate_raw(const char *str, zinject_record_t *record)
{
	/*
	 * A raw bookmark of the form objset:object:level:blkid, where each
	 * number is a hexadecimal value.
	 */
	if (sscanf(str, "%llx:%llx:%x:%llx", (u_longlong_t *)&record->zi_objset,
	    (u_longlong_t *)&record->zi_object, &record->zi_level,
	    (u_longlong_t *)&record->zi_start) != 4) {
		(void) fprintf(stderr, "bad raw spec '%s': must be of the form "
		    "'objset:object:level:blkid'\n", str);
		return (-1);
	}

	record->zi_end = record->zi_start;

	return (0);
}