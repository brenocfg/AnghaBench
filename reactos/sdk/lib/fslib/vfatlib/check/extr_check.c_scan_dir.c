#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_19__ {struct TYPE_19__* first; int /*<<< orphan*/  offset; } ;
struct TYPE_18__ {int cluster_size; } ;
typedef  int /*<<< orphan*/  FDSC ;
typedef  TYPE_1__ DOS_FS ;
typedef  TYPE_2__ DOS_FILE ;
typedef  int /*<<< orphan*/  DIR_ENT ;

/* Variables and functions */
 int FSTART (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_file (TYPE_1__*,TYPE_2__***,TYPE_2__*,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ check_dir (TYPE_1__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 scalar_t__ check_files (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ cluster_start (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lfn_check_orphaned () ; 
 int /*<<< orphan*/  new_dir () ; 
 int next_cluster (TYPE_1__*,int) ; 
 int subdirs (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int scan_dir(DOS_FS * fs, DOS_FILE * this, FDSC ** cp)
{
    DOS_FILE **chain;
    int i;
    uint32_t clu_num;

    chain = &this->first;
    i = 0;
    clu_num = FSTART(this, fs);
    new_dir();
    while (clu_num > 0 && clu_num != -1) {
	add_file(fs, &chain, this,
		 cluster_start(fs, clu_num) + (i % fs->cluster_size), cp);
	i += sizeof(DIR_ENT);
	if (!(i % fs->cluster_size))
	    if ((clu_num = next_cluster(fs, clu_num)) == 0 || clu_num == -1)
		break;
    }
    lfn_check_orphaned();
    if (check_dir(fs, &this->first, this->offset))
	return 0;
    if (check_files(fs, this->first))
	return 1;
    return subdirs(fs, this, cp);
}