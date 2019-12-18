#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int strcspn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* zfs_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zpool_add_handle (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * zpool_find_handle (TYPE_1__*,char*,int) ; 

__attribute__((used)) static zpool_handle_t *
zpool_handle(zfs_handle_t *zhp)
{
	char *pool_name;
	int len;
	zpool_handle_t *zph;

	len = strcspn(zhp->zfs_name, "/@#") + 1;
	pool_name = zfs_alloc(zhp->zfs_hdl, len);
	(void) strlcpy(pool_name, zhp->zfs_name, len);

	zph = zpool_find_handle(zhp, pool_name, len);
	if (zph == NULL)
		zph = zpool_add_handle(zhp, pool_name);

	free(pool_name);
	return (zph);
}