#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pathtype; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_2__ path; int /*<<< orphan*/  custom_paths; int /*<<< orphan*/ * methods; } ;
struct TYPE_11__ {TYPE_1__ cpath; int /*<<< orphan*/  hypertable_relid; int /*<<< orphan*/  hypertable_rti; int /*<<< orphan*/ * mtpath; } ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ModifyTablePath ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_3__ ChunkDispatchPath ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomPath ; 
 int /*<<< orphan*/  T_CustomScan ; 
 int /*<<< orphan*/  chunk_dispatch_path_methods ; 
 int /*<<< orphan*/  list_make1 (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ palloc0 (int) ; 

Path *
ts_chunk_dispatch_path_create(ModifyTablePath *mtpath, Path *subpath, Index hypertable_rti,
							  Oid hypertable_relid)
{
	ChunkDispatchPath *path = (ChunkDispatchPath *) palloc0(sizeof(ChunkDispatchPath));

	memcpy(&path->cpath.path, subpath, sizeof(Path));
	path->cpath.path.type = T_CustomPath;
	path->cpath.path.pathtype = T_CustomScan;
	path->cpath.methods = &chunk_dispatch_path_methods;
	path->cpath.custom_paths = list_make1(subpath);
	path->mtpath = mtpath;
	path->hypertable_rti = hypertable_rti;
	path->hypertable_relid = hypertable_relid;

	return &path->cpath.path;
}