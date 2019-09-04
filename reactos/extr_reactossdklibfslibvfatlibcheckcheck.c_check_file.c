#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_24__ {int attr; int /*<<< orphan*/  size; scalar_t__ name; } ;
struct TYPE_27__ {TYPE_1__ dir_ent; int /*<<< orphan*/  offset; struct TYPE_27__* parent; } ;
struct TYPE_26__ {int root_cluster; int data_clusters; int cluster_size; int /*<<< orphan*/  fat; } ;
struct TYPE_25__ {scalar_t__ value; } ;
typedef  TYPE_2__ FAT_ENTRY ;
typedef  TYPE_3__ DOS_FS ;
typedef  TYPE_4__ DOS_FILE ;

/* Variables and functions */
 int ATTR_DIR ; 
 int /*<<< orphan*/  DELETED_FLAG ; 
 int FSTART (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  MODIFY (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODIFY_START (TYPE_4__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  MSDOS_DOT ; 
 int /*<<< orphan*/  MSDOS_DOTDOT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 scalar_t__ bad_cluster (TYPE_3__*,int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  get_fat (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 char get_key (char*,char*) ; 
 TYPE_4__* get_owner (TYPE_3__*,int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 scalar_t__ interactive ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * name ; 
 int next_cluster (TYPE_3__*,int) ; 
 char* path_name (TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_fat (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  set_owner (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  size ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_file (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static int check_file(DOS_FS * fs, DOS_FILE * file)
{
    DOS_FILE *owner;
    int restart;
    uint32_t expect, curr, this, clusters, prev, walk, clusters2;

    if (file->dir_ent.attr & ATTR_DIR) {
	if (le32toh(file->dir_ent.size)) {
#ifndef __REACTOS__
	    printf("%s\n  Directory has non-zero size. Fixing it.\n",
		   path_name(file));
#else
	    printf("%s\n  Directory has non-zero size.%s\n",
		   path_name(file), (rw) ? " Fixing it." : "");
	    if (rw)
#endif
	    MODIFY(file, size, htole32(0));
	}
	if (file->parent
	    && !strncmp((const char *)file->dir_ent.name, MSDOS_DOT,
			MSDOS_NAME)) {
	    expect = FSTART(file->parent, fs);
	    if (FSTART(file, fs) != expect) {
		printf("%s\n  Start (%lu) does not point to parent (%lu)\n",
		       path_name(file), (unsigned long)FSTART(file, fs), (long)expect);
#ifdef __REACTOS__
		if (rw)
#endif
		MODIFY_START(file, expect, fs);
	    }
	    return 0;
	}
	if (file->parent
	    && !strncmp((const char *)file->dir_ent.name, MSDOS_DOTDOT,
			MSDOS_NAME)) {
	    expect =
		file->parent->parent ? FSTART(file->parent->parent, fs) : 0;
	    if (fs->root_cluster && expect == fs->root_cluster)
		expect = 0;
	    if (FSTART(file, fs) != expect) {
		printf("%s\n  Start (%lu) does not point to .. (%lu)\n",
		       path_name(file), (unsigned long)FSTART(file, fs), (unsigned long)expect);
#ifdef __REACTOS__
		if (rw)
#endif
		MODIFY_START(file, expect, fs);
	    }
	    return 0;
	}
	if (FSTART(file, fs) == 0) {
#ifndef __REACTOS__
	    printf("%s\n Start does point to root directory. Deleting dir. \n",
		   path_name(file));
#else
	    printf("%s\n Start does point to root directory.%s\n",
		   path_name(file), (rw) ? " Deleting dir. " : "");
	    if (rw)
#endif
	    MODIFY(file, name[0], DELETED_FLAG);
	    return 0;
	}
    }
    if (FSTART(file, fs) == 1) {
	printf("%s\n  Bad start cluster 1. Truncating file.\n",
	       path_name(file));
	if (!file->offset)
	    die("Bad FAT32 root directory! (bad start cluster 1)\n");
#ifdef __REACTOS__
	if (rw)
#endif
	MODIFY_START(file, 0, fs);
    }
    if (FSTART(file, fs) >= fs->data_clusters + 2) {
	printf
#ifndef __REACTOS__
	    ("%s\n  Start cluster beyond limit (%lu > %lu). Truncating file.\n",
	     path_name(file), (unsigned long)FSTART(file, fs),
	     (unsigned long)(fs->data_clusters + 1));
#else
	    ("%s\n  Start cluster beyond limit (%lu > %lu).%s\n",
	     path_name(file), (unsigned long)FSTART(file, fs),
	     (unsigned long)(fs->data_clusters + 1),
	     (rw) ? " Truncating file." : "");
#endif
	if (!file->offset)
	    die("Bad FAT32 root directory! (start cluster beyond limit: %lu > %lu)\n",
		(unsigned long)FSTART(file, fs),
		(unsigned long)(fs->data_clusters + 1));
#ifdef __REACTOS__
	if (rw)
#endif
	MODIFY_START(file, 0, fs);
    }
    clusters = prev = 0;
    for (curr = FSTART(file, fs) ? FSTART(file, fs) :
	 -1; curr != -1; curr = next_cluster(fs, curr)) {
	FAT_ENTRY curEntry;
	get_fat(&curEntry, fs->fat, curr, fs);

	if (!curEntry.value || bad_cluster(fs, curr)) {
#ifndef __REACTOS__
	    printf("%s\n  Contains a %s cluster (%lu). Assuming EOF.\n",
		   path_name(file), curEntry.value ? "bad" : "free", (unsigned long)curr);
#else
	    printf("%s\n  Contains a %s cluster (%lu).%s\n",
		   path_name(file), curEntry.value ? "bad" : "free", (unsigned long)curr,
		   (rw) ? " Assuming EOF." : "");
#endif
	    if (prev)
#ifdef __REACTOS__
	    {
	    if (rw)
#endif
		set_fat(fs, prev, -1);
#ifdef __REACTOS__
	    }
#endif
	    else if (!file->offset)
		die("FAT32 root dir starts with a bad cluster!");
	    else
#ifdef __REACTOS__
		if (rw)
#endif
		MODIFY_START(file, 0, fs);
	    break;
	}
	if (!(file->dir_ent.attr & ATTR_DIR) && le32toh(file->dir_ent.size) <=
	    (uint64_t)clusters * fs->cluster_size) {
#ifdef __REACTOS__
	    if (rw) {
#endif
	    printf
		("%s\n  File size is %u bytes, cluster chain length is > %llu "
		 "bytes.\n  Truncating file to %u bytes.\n", path_name(file),
		 le32toh(file->dir_ent.size),
		 (unsigned long long)clusters * fs->cluster_size,
		 le32toh(file->dir_ent.size));
	    truncate_file(fs, file, clusters);
#ifdef __REACTOS__
	    } else {
	    printf
		("%s\n  File size is %u bytes, cluster chain length is > %llu "
		 "bytes.\n", path_name(file),
		 le32toh(file->dir_ent.size),
		 (unsigned long long)clusters * fs->cluster_size);
	    }
#endif
	    break;
	}
	if ((owner = get_owner(fs, curr))) {
	    int do_trunc = 0;
	    printf("%s  and\n", path_name(owner));
	    printf("%s\n  share clusters.\n", path_name(file));
	    clusters2 = 0;
	    for (walk = FSTART(owner, fs); walk > 0 && walk != -1; walk =
		 next_cluster(fs, walk))
		if (walk == curr)
		    break;
		else
		    clusters2++;
	    restart = file->dir_ent.attr & ATTR_DIR;
#ifndef __REACTOS__
	    if (!owner->offset) {
#else
	    if (!owner->offset && rw) {
#endif
		printf("  Truncating second to %llu bytes because first "
		       "is FAT32 root dir.\n",
		       (unsigned long long)clusters * fs->cluster_size);
		do_trunc = 2;
#ifndef __REACTOS__
	    } else if (!file->offset) {
#else
	    } else if (!file->offset && rw) {
#endif
		printf("  Truncating first to %llu bytes because second "
		       "is FAT32 root dir.\n",
		       (unsigned long long)clusters2 * fs->cluster_size);
		do_trunc = 1;
	    } else if (interactive)
		printf("1) Truncate first to %llu bytes%s\n"
		       "2) Truncate second to %llu bytes\n",
		       (unsigned long long)clusters2 * fs->cluster_size,
		       restart ? " and restart" : "",
		       (unsigned long long)clusters * fs->cluster_size);
	    else
#ifdef __REACTOS__
	    if (rw)
#endif
		printf("  Truncating second to %llu bytes.\n",
		       (unsigned long long)clusters * fs->cluster_size);
#ifndef __REACTOS__
	    if (do_trunc != 2
		&& (do_trunc == 1
#else
	    if ((do_trunc != 2 && rw)
		&& ((do_trunc == 1 && rw)
#endif
		    || (interactive && get_key("12", "?") == '1'))) {
		prev = 0;
		clusters = 0;
		for (this = FSTART(owner, fs); this > 0 && this != -1; this =
		     next_cluster(fs, this)) {
		    if (this == curr) {
			if (prev)
			    set_fat(fs, prev, -1);
			else
			    MODIFY_START(owner, 0, fs);
			MODIFY(owner, size,
			       htole32((uint64_t)clusters *
				       fs->cluster_size));
			if (restart)
			    return 1;
			while (this > 0 && this != -1) {
			    set_owner(fs, this, NULL);
			    this = next_cluster(fs, this);
			}
			this = curr;
			break;
		    }
		    clusters++;
		    prev = this;
		}
		if (this != curr)
		    die("Internal error: didn't find cluster %d in chain"
			" starting at %d", curr, FSTART(owner, fs));
	    } else {
		if (prev)
		    set_fat(fs, prev, -1);
		else
		    MODIFY_START(file, 0, fs);
		break;
	    }
	}
	set_owner(fs, curr, file);
	clusters++;
	prev = curr;
    }
    if (!(file->dir_ent.attr & ATTR_DIR) && le32toh(file->dir_ent.size) >
#ifndef __REACTOS__
	(uint64_t)clusters * fs->cluster_size) {
#else
	(uint64_t)clusters * fs->cluster_size && rw) {
#endif
	printf
	    ("%s\n  File size is %u bytes, cluster chain length is %llu bytes."
	     "\n  Truncating file to %llu bytes.\n", path_name(file),
	     le32toh(file->dir_ent.size),
	     (unsigned long long)clusters * fs->cluster_size,
	     (unsigned long long)clusters * fs->cluster_size);
	MODIFY(file, size,
	       htole32((uint64_t)clusters * fs->cluster_size));
    }
    return 0;
}