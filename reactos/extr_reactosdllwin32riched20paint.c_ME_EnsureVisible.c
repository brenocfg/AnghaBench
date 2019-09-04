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
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_38__ {int nPos; } ;
struct TYPE_37__ {int cx; int cy; } ;
struct TYPE_34__ {int y; } ;
struct TYPE_35__ {int nHeight; TYPE_5__ pt; } ;
struct TYPE_32__ {int y; } ;
struct TYPE_33__ {TYPE_3__ pt; } ;
struct TYPE_36__ {TYPE_6__ row; TYPE_4__ para; } ;
struct TYPE_31__ {int x; } ;
struct TYPE_26__ {TYPE_2__ pt; } ;
struct TYPE_29__ {TYPE_12__ run; } ;
struct TYPE_30__ {TYPE_1__ member; } ;
struct TYPE_28__ {int /*<<< orphan*/  nOffset; TYPE_13__* pPara; TYPE_21__* pRun; } ;
struct TYPE_27__ {TYPE_7__ member; } ;
struct TYPE_24__ {int nPos; } ;
struct TYPE_25__ {int styleFlags; TYPE_10__ vert_si; TYPE_9__ horz_si; TYPE_8__ sizeWindow; } ;
typedef  TYPE_11__ ME_TextEditor ;
typedef  TYPE_12__ ME_Run ;
typedef  TYPE_13__ ME_DisplayItem ;
typedef  TYPE_14__ ME_Cursor ;

/* Variables and functions */
 int ES_AUTOHSCROLL ; 
 int ES_AUTOVSCROLL ; 
 TYPE_13__* ME_FindItemBack (TYPE_21__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_HScrollAbs (TYPE_11__*,int) ; 
 int ME_PointFromChar (TYPE_11__*,TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_ScrollAbs (TYPE_11__*,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (TYPE_13__*) ; 
 int /*<<< orphan*/  diStartRow ; 

void ME_EnsureVisible(ME_TextEditor *editor, ME_Cursor *pCursor)
{
  ME_Run *pRun = &pCursor->pRun->member.run;
  ME_DisplayItem *pRow = ME_FindItemBack(pCursor->pRun, diStartRow);
  ME_DisplayItem *pPara = pCursor->pPara;
  int x, y, yheight;

  assert(pRow);
  assert(pPara);

  if (editor->styleFlags & ES_AUTOHSCROLL)
  {
    x = pRun->pt.x + ME_PointFromChar(editor, pRun, pCursor->nOffset, TRUE);
    if (x > editor->horz_si.nPos + editor->sizeWindow.cx)
      x = x + 1 - editor->sizeWindow.cx;
    else if (x > editor->horz_si.nPos)
      x = editor->horz_si.nPos;

    if (~editor->styleFlags & ES_AUTOVSCROLL)
    {
      ME_HScrollAbs(editor, x);
      return;
    }
  } else {
    if (~editor->styleFlags & ES_AUTOVSCROLL)
      return;
    x = editor->horz_si.nPos;
  }

  y = pPara->member.para.pt.y + pRow->member.row.pt.y;
  yheight = pRow->member.row.nHeight;

  if (y < editor->vert_si.nPos)
    ME_ScrollAbs(editor, x, y);
  else if (y + yheight > editor->vert_si.nPos + editor->sizeWindow.cy)
    ME_ScrollAbs(editor, x, y + yheight - editor->sizeWindow.cy);
  else if (x != editor->horz_si.nPos)
    ME_ScrollAbs(editor, x, editor->vert_si.nPos);
}