#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pos; int len; } ;
struct TYPE_4__ {TYPE_1__ delete_run; } ;
struct undo_item {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct undo_item* add_undo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  undo_delete_run ; 

BOOL add_undo_delete_run( ME_TextEditor *editor, int pos, int len )
{
    struct undo_item *undo = add_undo( editor, undo_delete_run );
    if (!undo) return FALSE;

    undo->u.delete_run.pos = pos;
    undo->u.delete_run.len = len;

    return TRUE;
}