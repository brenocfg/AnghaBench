#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct zfs_stat {int zs_mode; scalar_t__ zs_links; scalar_t__ zs_gen; scalar_t__* zs_ctime; } ;
typedef  int mode_t ;
struct TYPE_7__ {scalar_t__ shares; scalar_t__ zerr; int /*<<< orphan*/  tosnap; int /*<<< orphan*/  fromsnap; } ;
typedef  TYPE_1__ differ_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTSUP ; 
 int MAXPATHLEN ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  ZDIFF_ADDED ; 
 int /*<<< orphan*/  ZDIFF_MODIFIED ; 
 int /*<<< orphan*/  ZDIFF_REMOVED ; 
 int get_stats_for_obj (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,char*,int,struct zfs_stat*) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char*,struct zfs_stat*) ; 
 int /*<<< orphan*/  print_link_change (int /*<<< orphan*/ *,TYPE_1__*,int,char*,struct zfs_stat*) ; 
 int /*<<< orphan*/  print_rename (int /*<<< orphan*/ *,TYPE_1__*,char*,char*,struct zfs_stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
write_inuse_diffs_one(FILE *fp, differ_info_t *di, uint64_t dobj)
{
	struct zfs_stat fsb, tsb;
	mode_t fmode, tmode;
	char fobjname[MAXPATHLEN], tobjname[MAXPATHLEN];
	int fobjerr, tobjerr;
	int change;

	if (dobj == di->shares)
		return (0);

	/*
	 * Check the from and to snapshots for info on the object. If
	 * we get ENOENT, then the object just didn't exist in that
	 * snapshot.  If we get ENOTSUP, then we tried to get
	 * info on a non-ZPL object, which we don't care about anyway.
	 */
	fobjerr = get_stats_for_obj(di, di->fromsnap, dobj, fobjname,
	    MAXPATHLEN, &fsb);
	if (fobjerr && di->zerr != ENOENT && di->zerr != ENOTSUP)
		return (-1);

	tobjerr = get_stats_for_obj(di, di->tosnap, dobj, tobjname,
	    MAXPATHLEN, &tsb);
	if (tobjerr && di->zerr != ENOENT && di->zerr != ENOTSUP)
		return (-1);

	/*
	 * Unallocated object sharing the same meta dnode block
	 */
	if (fobjerr && tobjerr) {
		ASSERT(di->zerr == ENOENT || di->zerr == ENOTSUP);
		di->zerr = 0;
		return (0);
	}

	di->zerr = 0; /* negate get_stats_for_obj() from side that failed */
	fmode = fsb.zs_mode & S_IFMT;
	tmode = tsb.zs_mode & S_IFMT;
	if (fmode == S_IFDIR || tmode == S_IFDIR || fsb.zs_links == 0 ||
	    tsb.zs_links == 0)
		change = 0;
	else
		change = tsb.zs_links - fsb.zs_links;

	if (fobjerr) {
		if (change) {
			print_link_change(fp, di, change, tobjname, &tsb);
			return (0);
		}
		print_file(fp, di, ZDIFF_ADDED, tobjname, &tsb);
		return (0);
	} else if (tobjerr) {
		if (change) {
			print_link_change(fp, di, change, fobjname, &fsb);
			return (0);
		}
		print_file(fp, di, ZDIFF_REMOVED, fobjname, &fsb);
		return (0);
	}

	if (fmode != tmode && fsb.zs_gen == tsb.zs_gen)
		tsb.zs_gen++;	/* Force a generational difference */

	/* Simple modification or no change */
	if (fsb.zs_gen == tsb.zs_gen) {
		/* No apparent changes.  Could we assert !this?  */
		if (fsb.zs_ctime[0] == tsb.zs_ctime[0] &&
		    fsb.zs_ctime[1] == tsb.zs_ctime[1])
			return (0);
		if (change) {
			print_link_change(fp, di, change,
			    change > 0 ? fobjname : tobjname, &tsb);
		} else if (strcmp(fobjname, tobjname) == 0) {
			print_file(fp, di, ZDIFF_MODIFIED, fobjname, &tsb);
		} else {
			print_rename(fp, di, fobjname, tobjname, &tsb);
		}
		return (0);
	} else {
		/* file re-created or object re-used */
		print_file(fp, di, ZDIFF_REMOVED, fobjname, &fsb);
		print_file(fp, di, ZDIFF_ADDED, tobjname, &tsb);
		return (0);
	}
}