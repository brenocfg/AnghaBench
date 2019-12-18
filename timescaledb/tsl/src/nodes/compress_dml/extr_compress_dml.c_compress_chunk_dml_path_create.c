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
struct TYPE_10__ {int /*<<< orphan*/  pathtarget; int /*<<< orphan*/  parent; int /*<<< orphan*/  pathtype; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_2__ path; int /*<<< orphan*/  custom_paths; int /*<<< orphan*/ * methods; } ;
struct TYPE_11__ {TYPE_1__ cpath; int /*<<< orphan*/  chunk_relid; } ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ CompressChunkDmlPath ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomPath ; 
 int /*<<< orphan*/  T_CustomScan ; 
 int /*<<< orphan*/  compress_chunk_dml_path_methods ; 
 int /*<<< orphan*/  list_make1 (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static Path *
compress_chunk_dml_path_create(Path *subpath, Oid chunk_relid)
{
	CompressChunkDmlPath *path = (CompressChunkDmlPath *) palloc0(sizeof(CompressChunkDmlPath));

	memcpy(&path->cpath.path, subpath, sizeof(Path));
	path->cpath.path.type = T_CustomPath;
	path->cpath.path.pathtype = T_CustomScan;
	path->cpath.path.parent = subpath->parent;
	path->cpath.path.pathtarget = subpath->pathtarget;
	// path->cpath.path.param_info = subpath->param_info;
	path->cpath.methods = &compress_chunk_dml_path_methods;
	path->cpath.custom_paths = list_make1(subpath);
	path->chunk_relid = chunk_relid;

	return &path->cpath.path;
}