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
struct TYPE_7__ {int root_entries; scalar_t__ root_start; scalar_t__ root_cluster; } ;
typedef  TYPE_1__ DOS_FS ;
typedef  int /*<<< orphan*/  DOS_FILE ;
typedef  int /*<<< orphan*/  DIR_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  add_file (TYPE_1__*,int /*<<< orphan*/ ***,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_dir (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ check_files (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fp_root ; 
 int /*<<< orphan*/  lfn_check_orphaned () ; 
 int /*<<< orphan*/  new_dir () ; 
 int /*<<< orphan*/ * root ; 
 int subdirs (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int scan_root(DOS_FS * fs)
{
    DOS_FILE **chain;
    int i;

    root = NULL;
    chain = &root;
    new_dir();
    if (fs->root_cluster) {
	add_file(fs, &chain, NULL, 0, &fp_root);
    } else {
	for (i = 0; i < fs->root_entries; i++)
	    add_file(fs, &chain, NULL, fs->root_start + i * sizeof(DIR_ENT),
		     &fp_root);
    }
    lfn_check_orphaned();
    (void)check_dir(fs, &root, 0);
    if (check_files(fs, root))
	return 1;
    return subdirs(fs, NULL, &fp_root);
}