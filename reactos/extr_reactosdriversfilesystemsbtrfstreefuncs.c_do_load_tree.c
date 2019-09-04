#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* tree; int /*<<< orphan*/  generation; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ tree_holder ;
typedef  int /*<<< orphan*/  tree_data ;
struct TYPE_12__ {int /*<<< orphan*/ * paritem; struct TYPE_12__* parent; } ;
typedef  TYPE_3__ tree ;
struct TYPE_13__ {TYPE_1__* nonpaged; } ;
typedef  TYPE_4__ root ;
typedef  int /*<<< orphan*/  device_extension ;
struct TYPE_10__ {int /*<<< orphan*/  load_tree_lock; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  load_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS do_load_tree(device_extension* Vcb, tree_holder* th, root* r, tree* t, tree_data* td, BOOL* loaded, PIRP Irp) {
    BOOL ret;

    ExAcquireResourceExclusiveLite(&r->nonpaged->load_tree_lock, TRUE);

    if (!th->tree) {
        NTSTATUS Status;
        tree* nt;

        Status = load_tree(Vcb, th->address, r, &nt, th->generation, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("load_tree returned %08x\n", Status);
            ExReleaseResourceLite(&r->nonpaged->load_tree_lock);
            return Status;
        }

        nt->parent = t;

#ifdef DEBUG_PARANOID
        if (t && t->header.level <= nt->header.level) int3;
#endif

        nt->paritem = td;

        th->tree = nt;

        ret = TRUE;
    } else
        ret = FALSE;

    ExReleaseResourceLite(&r->nonpaged->load_tree_lock);

    *loaded = ret;

    return STATUS_SUCCESS;
}