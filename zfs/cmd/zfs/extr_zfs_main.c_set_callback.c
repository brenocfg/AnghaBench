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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
#define  EZFS_MOUNTFAILED 129 
#define  EZFS_SHARENFSFAILED 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int libzfs_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ zfs_prop_set_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_callback(zfs_handle_t *zhp, void *data)
{
	nvlist_t *props = data;

	if (zfs_prop_set_list(zhp, props) != 0) {
		switch (libzfs_errno(g_zfs)) {
		case EZFS_MOUNTFAILED:
			(void) fprintf(stderr, gettext("property may be set "
			    "but unable to remount filesystem\n"));
			break;
		case EZFS_SHARENFSFAILED:
			(void) fprintf(stderr, gettext("property may be set "
			    "but unable to reshare filesystem\n"));
			break;
		}
		return (1);
	}
	return (0);
}