#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  lfn_offset; scalar_t__ lfn; } ;
struct TYPE_10__ {scalar_t__ data_clusters; } ;
typedef  TYPE_1__ DOS_FS ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DELETED_FLAG ; 
 scalar_t__ FSTART (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MODIFY (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfn_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_files ; 
 int /*<<< orphan*/ * name ; 
 scalar_t__ next_cluster (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  set_owner (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_file(DOS_FS * fs, DOS_FILE * file)
{
    uint32_t cluster;

    MODIFY(file, name[0], DELETED_FLAG);
    if (file->lfn)
	lfn_remove(file->lfn_offset, file->offset);
    for (cluster = FSTART(file, fs); cluster > 0 && cluster <
	 fs->data_clusters + 2; cluster = next_cluster(fs, cluster))
	set_owner(fs, cluster, NULL);
    --n_files;
}