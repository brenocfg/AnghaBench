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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VDEV_TYPE_MIRROR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/ * make_vdev_raidz (char*,char*,char*,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static nvlist_t *
make_vdev_mirror(char *path, char *aux, char *pool, size_t size,
    uint64_t ashift, int r, int m)
{
	nvlist_t *mirror, **child;
	int c;

	if (m < 1)
		return (make_vdev_raidz(path, aux, pool, size, ashift, r));

	child = umem_alloc(m * sizeof (nvlist_t *), UMEM_NOFAIL);

	for (c = 0; c < m; c++)
		child[c] = make_vdev_raidz(path, aux, pool, size, ashift, r);

	VERIFY(nvlist_alloc(&mirror, NV_UNIQUE_NAME, 0) == 0);
	VERIFY(nvlist_add_string(mirror, ZPOOL_CONFIG_TYPE,
	    VDEV_TYPE_MIRROR) == 0);
	VERIFY(nvlist_add_nvlist_array(mirror, ZPOOL_CONFIG_CHILDREN,
	    child, m) == 0);

	for (c = 0; c < m; c++)
		nvlist_free(child[c]);

	umem_free(child, m * sizeof (nvlist_t *));

	return (mirror);
}