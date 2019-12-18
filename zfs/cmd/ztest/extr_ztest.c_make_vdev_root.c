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
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 char const* VDEV_TYPE_ROOT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ALLOCATION_BIAS ; 
 char* ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/ * make_vdev_mirror (char*,char*,char*,size_t,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ ** umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static nvlist_t *
make_vdev_root(char *path, char *aux, char *pool, size_t size, uint64_t ashift,
    const char *class, int r, int m, int t)
{
	nvlist_t *root, **child;
	int c;
	boolean_t log;

	ASSERT(t > 0);

	log = (class != NULL && strcmp(class, "log") == 0);

	child = umem_alloc(t * sizeof (nvlist_t *), UMEM_NOFAIL);

	for (c = 0; c < t; c++) {
		child[c] = make_vdev_mirror(path, aux, pool, size, ashift,
		    r, m);
		VERIFY(nvlist_add_uint64(child[c], ZPOOL_CONFIG_IS_LOG,
		    log) == 0);

		if (class != NULL && class[0] != '\0') {
			ASSERT(m > 1 || log);   /* expecting a mirror */
			VERIFY(nvlist_add_string(child[c],
			    ZPOOL_CONFIG_ALLOCATION_BIAS, class) == 0);
		}
	}

	VERIFY(nvlist_alloc(&root, NV_UNIQUE_NAME, 0) == 0);
	VERIFY(nvlist_add_string(root, ZPOOL_CONFIG_TYPE, VDEV_TYPE_ROOT) == 0);
	VERIFY(nvlist_add_nvlist_array(root, aux ? aux : ZPOOL_CONFIG_CHILDREN,
	    child, t) == 0);

	for (c = 0; c < t; c++)
		nvlist_free(child[c]);

	umem_free(child, t * sizeof (nvlist_t *));

	return (root);
}