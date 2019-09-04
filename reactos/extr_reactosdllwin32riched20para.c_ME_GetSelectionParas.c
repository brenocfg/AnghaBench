#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  nOffset; TYPE_3__* pRun; TYPE_7__* pPara; } ;
struct TYPE_15__ {scalar_t__ nCharOfs; TYPE_7__* prev_para; } ;
struct TYPE_16__ {TYPE_4__ para; } ;
struct TYPE_18__ {TYPE_5__ member; } ;
struct TYPE_17__ {TYPE_8__* pCursors; } ;
struct TYPE_12__ {int /*<<< orphan*/  nCharOfs; } ;
struct TYPE_13__ {TYPE_1__ run; } ;
struct TYPE_14__ {TYPE_2__ member; } ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  TYPE_7__ ME_DisplayItem ;
typedef  TYPE_8__ ME_Cursor ;

/* Variables and functions */

void
ME_GetSelectionParas(ME_TextEditor *editor, ME_DisplayItem **para, ME_DisplayItem **para_end)
{
  ME_Cursor *pEndCursor = &editor->pCursors[1];

  *para = editor->pCursors[0].pPara;
  *para_end = editor->pCursors[1].pPara;
  if (*para == *para_end)
    return;

  if ((*para_end)->member.para.nCharOfs < (*para)->member.para.nCharOfs) {
    ME_DisplayItem *tmp = *para;

    *para = *para_end;
    *para_end = tmp;
    pEndCursor = &editor->pCursors[0];
  }

  /* The paragraph at the end of a non-empty selection isn't included
   * if the selection ends at the start of the paragraph. */
  if (!pEndCursor->pRun->member.run.nCharOfs && !pEndCursor->nOffset)
    *para_end = (*para_end)->member.para.prev_para;
}