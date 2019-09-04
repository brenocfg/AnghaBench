#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct TYPE_38__ {TYPE_6__* pCursors; int /*<<< orphan*/  bEmulateVersion10; } ;
struct TYPE_37__ {int nFlags; } ;
struct TYPE_32__ {int nFlags; TYPE_10__* prev_para; TYPE_10__* next_para; TYPE_10__* pCell; } ;
struct TYPE_34__ {TYPE_4__* next_cell; } ;
struct TYPE_36__ {TYPE_3__ para; TYPE_8__ run; TYPE_5__ cell; } ;
struct TYPE_35__ {scalar_t__ nOffset; TYPE_10__* pPara; TYPE_10__* pRun; } ;
struct TYPE_30__ {scalar_t__ next_cell; } ;
struct TYPE_31__ {TYPE_1__ cell; } ;
struct TYPE_33__ {TYPE_2__ member; } ;
struct TYPE_29__ {scalar_t__ type; TYPE_7__ member; } ;
typedef  TYPE_9__ ME_TextEditor ;
typedef  TYPE_10__ ME_DisplayItem ;

/* Variables and functions */
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 int MERF_ENDPARA ; 
 int MERF_TAB ; 
 TYPE_10__* ME_AppendTableRow (TYPE_9__*,TYPE_10__*) ; 
 TYPE_10__* ME_FindItemBack (TYPE_10__*,scalar_t__) ; 
 TYPE_10__* ME_FindItemFwd (TYPE_10__*,scalar_t__) ; 
 void* ME_GetParagraph (TYPE_10__*) ; 
 TYPE_10__* ME_GetTableRowEnd (TYPE_10__*) ; 
 TYPE_10__* ME_GetTableRowStart (TYPE_10__*) ; 
 TYPE_10__* ME_IsInTable (TYPE_10__*) ; 
 int /*<<< orphan*/  ME_WrapMarkedParagraphs (TYPE_9__*) ; 
 int /*<<< orphan*/  assert (TYPE_10__*) ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diParagraphOrEnd ; 
 scalar_t__ diRun ; 
 scalar_t__ diRunOrParagraphOrEnd ; 

__attribute__((used)) static void ME_SelectOrInsertNextCell(ME_TextEditor *editor,
                                      ME_DisplayItem *run)
{
  ME_DisplayItem *para = ME_GetParagraph(run);
  int i;

  assert(run && run->type == diRun);
  assert(ME_IsInTable(run));
  if (!editor->bEmulateVersion10) { /* v4.1 */
    ME_DisplayItem *cell;
    /* Get the initial cell */
    if (para->member.para.nFlags & MEPF_ROWSTART) {
      cell = para->member.para.next_para->member.para.pCell;
    } else if (para->member.para.nFlags & MEPF_ROWEND) {
      cell = para->member.para.prev_para->member.para.pCell;
    } else {
      cell = para->member.para.pCell;
    }
    assert(cell);
    /* Get the next cell. */
    if (cell->member.cell.next_cell &&
        cell->member.cell.next_cell->member.cell.next_cell)
    {
      cell = cell->member.cell.next_cell;
    } else {
      para = ME_GetTableRowEnd(ME_FindItemFwd(cell, diParagraph));
      para = para->member.para.next_para;
      assert(para);
      if (para->member.para.nFlags & MEPF_ROWSTART) {
        cell = para->member.para.next_para->member.para.pCell;
      } else {
        /* Insert row */
        para = para->member.para.prev_para;
        para = ME_AppendTableRow(editor, ME_GetTableRowStart(para));
        /* Put cursor at the start of the new table row */
        para = para->member.para.next_para;
        editor->pCursors[0].pPara = para;
        editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
        editor->pCursors[0].nOffset = 0;
        editor->pCursors[1] = editor->pCursors[0];
        ME_WrapMarkedParagraphs(editor);
        return;
      }
    }
    /* Select cell */
    editor->pCursors[1].pRun = ME_FindItemFwd(cell, diRun);
    editor->pCursors[1].pPara = ME_GetParagraph(editor->pCursors[1].pRun);
    editor->pCursors[1].nOffset = 0;
    assert(editor->pCursors[0].pRun);
    cell = cell->member.cell.next_cell;
    editor->pCursors[0].pRun = ME_FindItemBack(cell, diRun);
    editor->pCursors[0].pPara = ME_GetParagraph(editor->pCursors[0].pRun);
    editor->pCursors[0].nOffset = 0;
    assert(editor->pCursors[1].pRun);
  } else { /* v1.0 - 3.0 */
    if (run->member.run.nFlags & MERF_ENDPARA &&
        ME_IsInTable(ME_FindItemFwd(run, diParagraphOrEnd)))
    {
      run = ME_FindItemFwd(run, diRun);
      assert(run);
    }
    for (i = 0; i < 2; i++)
    {
      while (!(run->member.run.nFlags & MERF_TAB))
      {
        run = ME_FindItemFwd(run, diRunOrParagraphOrEnd);
        if (run->type != diRun)
        {
          para = run;
          if (ME_IsInTable(para))
          {
            run = ME_FindItemFwd(para, diRun);
            assert(run);
            editor->pCursors[0].pPara = para;
            editor->pCursors[0].pRun = run;
            editor->pCursors[0].nOffset = 0;
            i = 1;
          } else {
            /* Insert table row */
            para = ME_AppendTableRow(editor, para->member.para.prev_para);
            /* Put cursor at the start of the new table row */
            editor->pCursors[0].pPara = para;
            editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
            editor->pCursors[0].nOffset = 0;
            editor->pCursors[1] = editor->pCursors[0];
            ME_WrapMarkedParagraphs(editor);
            return;
          }
        }
      }
      if (i == 0)
        run = ME_FindItemFwd(run, diRun);
      editor->pCursors[i].pRun = run;
      editor->pCursors[i].pPara = ME_GetParagraph(run);
      editor->pCursors[i].nOffset = 0;
    }
  }
}