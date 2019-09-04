#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct re_object {int /*<<< orphan*/  entry; } ;
typedef  char WCHAR ;
struct TYPE_12__ {struct re_object* reobj; } ;
struct TYPE_13__ {TYPE_1__ run; } ;
struct TYPE_15__ {TYPE_2__ member; } ;
struct TYPE_14__ {int /*<<< orphan*/  reobj_list; } ;
typedef  int /*<<< orphan*/  REOBJECT ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  MERF_GRAPHICS ; 
 int /*<<< orphan*/  ME_DeleteSelection (TYPE_3__*) ; 
 int /*<<< orphan*/ * ME_GetInsertStyle (TYPE_3__*,int) ; 
 TYPE_4__* ME_InternalInsertTextFromCursor (TYPE_3__*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ME_IsSelection (TYPE_3__*) ; 
 scalar_t__ ME_PrevRun (int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 struct re_object* create_re_object (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_add_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ME_InsertOLEFromCursor(ME_TextEditor *editor, const REOBJECT* reo, int nCursor)
{
  ME_Style              *pStyle = ME_GetInsertStyle(editor, nCursor);
  ME_DisplayItem        *di;
  WCHAR                 space = ' ';
  ME_DisplayItem        *di_prev = NULL;
  struct re_object      *reobj_prev = NULL;
  
  /* FIXME no no no */
  if (ME_IsSelection(editor))
    ME_DeleteSelection(editor);

  di = ME_InternalInsertTextFromCursor(editor, nCursor, &space, 1, pStyle,
                                       MERF_GRAPHICS);
  di->member.run.reobj = create_re_object(reo);

  di_prev = di;
  while (ME_PrevRun(NULL, &di_prev, TRUE))
  {
    if (di_prev->member.run.reobj)
    {
      reobj_prev = di_prev->member.run.reobj;
      break;
    }
  }
  if (reobj_prev)
    list_add_after(&reobj_prev->entry, &di->member.run.reobj->entry);
  else
    list_add_head(&editor->reobj_list, &di->member.run.reobj->entry);

  ME_ReleaseStyle(pStyle);
}