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
typedef  int /*<<< orphan*/  libpc_handle_t ;

/* Variables and functions */
 char* strdup (char const*) ; 
 int /*<<< orphan*/  zutil_no_memory (int /*<<< orphan*/ *) ; 

char *
zutil_strdup(libpc_handle_t *hdl, const char *str)
{
	char *ret;

	if ((ret = strdup(str)) == NULL)
		(void) zutil_no_memory(hdl);

	return (ret);
}