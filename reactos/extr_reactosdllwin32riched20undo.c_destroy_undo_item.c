#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  eol_str; } ;
struct TYPE_4__ {int /*<<< orphan*/  style; struct undo_item* str; } ;
struct TYPE_6__ {TYPE_2__ split_para; TYPE_1__ insert_run; } ;
struct undo_item {int type; TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ME_DestroyString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (struct undo_item*) ; 
#define  undo_insert_run 129 
#define  undo_split_para 128 

__attribute__((used)) static void destroy_undo_item( struct undo_item *undo )
{
    switch( undo->type )
    {
    case undo_insert_run:
        heap_free( undo->u.insert_run.str );
        ME_ReleaseStyle( undo->u.insert_run.style );
        break;
    case undo_split_para:
        ME_DestroyString( undo->u.split_para.eol_str );
        break;
    default:
        break;
    }

    heap_free( undo );
}