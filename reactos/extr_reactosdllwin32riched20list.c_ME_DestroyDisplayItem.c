#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  entry; } ;
struct TYPE_8__ {int /*<<< orphan*/  style; TYPE_3__* clusters; TYPE_3__* glyphs; TYPE_6__* reobj; } ;
struct TYPE_7__ {TYPE_2__ run; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ member; } ;
typedef  TYPE_3__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ME_DeleteReObject (TYPE_6__*) ; 
 int /*<<< orphan*/  ME_GetDITypeName (scalar_t__) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ diRun ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void ME_DestroyDisplayItem(ME_DisplayItem *item)
{
  if (0)
    TRACE("type=%s\n", ME_GetDITypeName(item->type));
  if (item->type==diRun)
  {
    if (item->member.run.reobj)
    {
      list_remove(&item->member.run.reobj->entry);
      ME_DeleteReObject(item->member.run.reobj);
    }
    heap_free( item->member.run.glyphs );
    heap_free( item->member.run.clusters );
    ME_ReleaseStyle(item->member.run.style);
  }
  heap_free(item);
}