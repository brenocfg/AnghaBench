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
typedef  int /*<<< orphan*/  zpool_handle_t ;

/* Variables and functions */
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
is_pool_cb(zpool_handle_t *zhp, void *data)
{
	char *name = data;
	if (strcmp(name, zpool_get_name(zhp)) == 0)
		return (1);

	return (0);
}