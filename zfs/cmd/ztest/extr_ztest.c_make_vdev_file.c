#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {char* zo_pool; int /*<<< orphan*/  zo_dir; } ;
struct TYPE_3__ {scalar_t__ zs_vdev_aux; int /*<<< orphan*/  zs_vdev_next_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 char* VDEV_TYPE_FILE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ASHIFT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fatal (int,char*,char*) ; 
 scalar_t__ ftruncate (int,size_t) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 char* umem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int /*<<< orphan*/ ) ; 
 char* ztest_aux_template ; 
 char* ztest_dev_template ; 
 scalar_t__ ztest_get_ashift () ; 
 TYPE_2__ ztest_opts ; 
 TYPE_1__* ztest_shared ; 

__attribute__((used)) static nvlist_t *
make_vdev_file(char *path, char *aux, char *pool, size_t size, uint64_t ashift)
{
	char *pathbuf;
	uint64_t vdev;
	nvlist_t *file;

	pathbuf = umem_alloc(MAXPATHLEN, UMEM_NOFAIL);

	if (ashift == 0)
		ashift = ztest_get_ashift();

	if (path == NULL) {
		path = pathbuf;

		if (aux != NULL) {
			vdev = ztest_shared->zs_vdev_aux;
			(void) snprintf(path, MAXPATHLEN,
			    ztest_aux_template, ztest_opts.zo_dir,
			    pool == NULL ? ztest_opts.zo_pool : pool,
			    aux, vdev);
		} else {
			vdev = ztest_shared->zs_vdev_next_leaf++;
			(void) snprintf(path, MAXPATHLEN,
			    ztest_dev_template, ztest_opts.zo_dir,
			    pool == NULL ? ztest_opts.zo_pool : pool, vdev);
		}
	}

	if (size != 0) {
		int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			fatal(1, "can't open %s", path);
		if (ftruncate(fd, size) != 0)
			fatal(1, "can't ftruncate %s", path);
		(void) close(fd);
	}

	VERIFY(nvlist_alloc(&file, NV_UNIQUE_NAME, 0) == 0);
	VERIFY(nvlist_add_string(file, ZPOOL_CONFIG_TYPE, VDEV_TYPE_FILE) == 0);
	VERIFY(nvlist_add_string(file, ZPOOL_CONFIG_PATH, path) == 0);
	VERIFY(nvlist_add_uint64(file, ZPOOL_CONFIG_ASHIFT, ashift) == 0);
	umem_free(pathbuf, MAXPATHLEN);

	return (file);
}