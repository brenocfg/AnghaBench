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
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ getprop_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static int
zfs_add_option(zfs_handle_t *zhp, char *options, int len,
    zfs_prop_t prop, char *on, char *off)
{
	char *source;
	uint64_t value;

	/* Skip adding duplicate default options */
	if ((strstr(options, on) != NULL) || (strstr(options, off) != NULL))
		return (0);

	/*
	 * zfs_prop_get_int() is not used to ensure our mount options
	 * are not influenced by the current /proc/self/mounts contents.
	 */
	value = getprop_uint64(zhp, prop, &source);

	(void) strlcat(options, ",", len);
	(void) strlcat(options, value ? on : off, len);

	return (0);
}