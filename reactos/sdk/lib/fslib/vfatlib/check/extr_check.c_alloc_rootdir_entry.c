#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  d2 ;
struct TYPE_20__ {scalar_t__ attr; scalar_t__ name; } ;
struct TYPE_19__ {int root_cluster; int cluster_size; int data_clusters; int root_entries; int root_start; int /*<<< orphan*/  fat; } ;
struct TYPE_18__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;
typedef  TYPE_3__ DIR_ENT ;

/* Variables and functions */
 scalar_t__ IS_FREE (scalar_t__) ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 scalar_t__ VFAT_LN_ATTR ; 
 TYPE_3__* alloc (int) ; 
 int cluster_start (TYPE_2__*,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  fs_read (int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  fs_write (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  get_fat (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  get_owner (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_files ; 
 int next_cluster (TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_fat (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  set_owner (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

off_t alloc_rootdir_entry(DOS_FS * fs, DIR_ENT * de, const char *pattern, int gen_name)
{
    static int curr_num = 0;
    off_t offset;

    if (fs->root_cluster) {
	DIR_ENT d2;
	int i = 0, got = 0;
	uint32_t clu_num, prev = 0;
	off_t offset2;

	clu_num = fs->root_cluster;
	offset = cluster_start(fs, clu_num);
	while (clu_num > 0 && clu_num != -1) {
	    fs_read(offset, sizeof(DIR_ENT), &d2);
	    if (IS_FREE(d2.name) && d2.attr != VFAT_LN_ATTR) {
		got = 1;
		break;
	    }
	    i += sizeof(DIR_ENT);
	    offset += sizeof(DIR_ENT);
	    if ((i % fs->cluster_size) == 0) {
		prev = clu_num;
		if ((clu_num = next_cluster(fs, clu_num)) == 0 || clu_num == -1)
		    break;
		offset = cluster_start(fs, clu_num);
	    }
	}
	if (!got) {
	    /* no free slot, need to extend root dir: alloc next free cluster
	     * after previous one */
	    if (!prev)
		die("Root directory has no cluster allocated!");
	    for (clu_num = prev + 1; clu_num != prev; clu_num++) {
		FAT_ENTRY entry;

		if (clu_num >= fs->data_clusters + 2)
		    clu_num = 2;
		get_fat(&entry, fs->fat, clu_num, fs);
		if (!entry.value)
		    break;
	    }
	    if (clu_num == prev)
		die("Root directory full and no free cluster");
	    set_fat(fs, prev, clu_num);
	    set_fat(fs, clu_num, -1);
	    set_owner(fs, clu_num, get_owner(fs, fs->root_cluster));
	    /* clear new cluster */
	    memset(&d2, 0, sizeof(d2));
	    offset = cluster_start(fs, clu_num);
	    for (i = 0; i < fs->cluster_size; i += sizeof(DIR_ENT))
		fs_write(offset + i, sizeof(d2), &d2);
	}
	memset(de, 0, sizeof(DIR_ENT));
	if (gen_name) {
	    while (1) {
		char expanded[12];
		sprintf(expanded, pattern, curr_num);
		memcpy(de->name, expanded, MSDOS_NAME);
		clu_num = fs->root_cluster;
		i = 0;
		offset2 = cluster_start(fs, clu_num);
		while (clu_num > 0 && clu_num != -1) {
		    fs_read(offset2, sizeof(DIR_ENT), &d2);
		    if (offset2 != offset &&
			!strncmp((const char *)d2.name, (const char *)de->name,
				 MSDOS_NAME))
			break;
		    i += sizeof(DIR_ENT);
		    offset2 += sizeof(DIR_ENT);
		    if ((i % fs->cluster_size) == 0) {
			if ((clu_num = next_cluster(fs, clu_num)) == 0 ||
			    clu_num == -1)
			    break;
			offset2 = cluster_start(fs, clu_num);
		    }
		}
		if (clu_num == 0 || clu_num == -1)
		    break;
		if (++curr_num >= 10000)
		    die("Unable to create unique name");
	    }
	} else {
	    memcpy(de->name, pattern, MSDOS_NAME);
	}
    } else {
	DIR_ENT *root;
	int next_free = 0, scan;

	root = alloc(fs->root_entries * sizeof(DIR_ENT));
	fs_read(fs->root_start, fs->root_entries * sizeof(DIR_ENT), root);

	while (next_free < fs->root_entries)
	    if (IS_FREE(root[next_free].name) &&
		root[next_free].attr != VFAT_LN_ATTR)
		break;
	    else
		next_free++;
	if (next_free == fs->root_entries)
	    die("Root directory is full.");
	offset = fs->root_start + next_free * sizeof(DIR_ENT);
	memset(de, 0, sizeof(DIR_ENT));
	if (gen_name) {
	    while (1) {
		char expanded[12];
		sprintf(expanded, pattern, curr_num);
		memcpy(de->name, expanded, MSDOS_NAME);
		for (scan = 0; scan < fs->root_entries; scan++)
		    if (scan != next_free &&
			!strncmp((const char *)root[scan].name,
				 (const char *)de->name, MSDOS_NAME))
			break;
		if (scan == fs->root_entries)
		    break;
		if (++curr_num >= 10000)
		    die("Unable to create unique name");
	    }
	} else {
	    memcpy(de->name, pattern, MSDOS_NAME);
	}
	free(root);
    }
    ++n_files;
    return offset;
}