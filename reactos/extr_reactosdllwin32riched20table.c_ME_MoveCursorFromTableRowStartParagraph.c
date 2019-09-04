#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nFlags; TYPE_5__* next_para; } ;
struct TYPE_9__ {TYPE_1__ para; } ;
struct TYPE_12__ {TYPE_2__ member; } ;
struct TYPE_11__ {TYPE_3__* pCursors; } ;
struct TYPE_10__ {scalar_t__ nOffset; int /*<<< orphan*/  pRun; TYPE_5__* pPara; } ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  TYPE_5__ ME_DisplayItem ;

/* Variables and functions */
 int MEPF_ROWSTART ; 
 int /*<<< orphan*/  ME_FindItemFwd (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diRun ; 

void ME_MoveCursorFromTableRowStartParagraph(ME_TextEditor *editor)
{
  ME_DisplayItem *para = editor->pCursors[0].pPara;
  if (para == editor->pCursors[1].pPara &&
      para->member.para.nFlags & MEPF_ROWSTART) {
    /* The cursors should not be at the hidden start row paragraph without
     * a selection, so the cursor is moved into the first cell. */
    para = para->member.para.next_para;
    editor->pCursors[0].pPara = para;
    editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
    editor->pCursors[0].nOffset = 0;
    editor->pCursors[1] = editor->pCursors[0];
  }
}