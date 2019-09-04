#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  pRun; int /*<<< orphan*/ * pPara; scalar_t__ nOffset; } ;
struct TYPE_8__ {TYPE_2__* pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  int /*<<< orphan*/  ME_DisplayItem ;
typedef  TYPE_2__ ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  ME_FindItemFwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ME_GetInsertStyle (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ME_SplitParagraph (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ME_SplitRunSimple (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  diRun ; 

__attribute__((used)) static ME_DisplayItem* ME_InsertEndParaFromCursor(ME_TextEditor *editor,
                                                  int nCursor,
                                                  const WCHAR *eol_str, int eol_len,
                                                  int paraFlags)
{
  ME_Style *pStyle = ME_GetInsertStyle(editor, nCursor);
  ME_DisplayItem *tp;
  ME_Cursor* cursor = &editor->pCursors[nCursor];
  if (cursor->nOffset)
    ME_SplitRunSimple(editor, cursor);

  tp = ME_SplitParagraph(editor, cursor->pRun, pStyle, eol_str, eol_len, paraFlags);
  ME_ReleaseStyle(pStyle);
  cursor->pPara = tp;
  cursor->pRun = ME_FindItemFwd(tp, diRun);
  return tp;
}