#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_95__   TYPE_9__ ;
typedef  struct TYPE_94__   TYPE_8__ ;
typedef  struct TYPE_93__   TYPE_7__ ;
typedef  struct TYPE_92__   TYPE_6__ ;
typedef  struct TYPE_91__   TYPE_5__ ;
typedef  struct TYPE_90__   TYPE_4__ ;
typedef  struct TYPE_89__   TYPE_46__ ;
typedef  struct TYPE_88__   TYPE_44__ ;
typedef  struct TYPE_87__   TYPE_40__ ;
typedef  struct TYPE_86__   TYPE_3__ ;
typedef  struct TYPE_85__   TYPE_39__ ;
typedef  struct TYPE_84__   TYPE_38__ ;
typedef  struct TYPE_83__   TYPE_37__ ;
typedef  struct TYPE_82__   TYPE_36__ ;
typedef  struct TYPE_81__   TYPE_35__ ;
typedef  struct TYPE_80__   TYPE_34__ ;
typedef  struct TYPE_79__   TYPE_33__ ;
typedef  struct TYPE_78__   TYPE_32__ ;
typedef  struct TYPE_77__   TYPE_31__ ;
typedef  struct TYPE_76__   TYPE_30__ ;
typedef  struct TYPE_75__   TYPE_2__ ;
typedef  struct TYPE_74__   TYPE_29__ ;
typedef  struct TYPE_73__   TYPE_28__ ;
typedef  struct TYPE_72__   TYPE_27__ ;
typedef  struct TYPE_71__   TYPE_26__ ;
typedef  struct TYPE_70__   TYPE_25__ ;
typedef  struct TYPE_69__   TYPE_24__ ;
typedef  struct TYPE_68__   TYPE_23__ ;
typedef  struct TYPE_67__   TYPE_22__ ;
typedef  struct TYPE_66__   TYPE_21__ ;
typedef  struct TYPE_65__   TYPE_20__ ;
typedef  struct TYPE_64__   TYPE_1__ ;
typedef  struct TYPE_63__   TYPE_19__ ;
typedef  struct TYPE_62__   TYPE_18__ ;
typedef  struct TYPE_61__   TYPE_17__ ;
typedef  struct TYPE_60__   TYPE_16__ ;
typedef  struct TYPE_59__   TYPE_15__ ;
typedef  struct TYPE_58__   TYPE_14__ ;
typedef  struct TYPE_57__   TYPE_13__ ;
typedef  struct TYPE_56__   TYPE_12__ ;
typedef  struct TYPE_55__   TYPE_11__ ;
typedef  struct TYPE_54__   TYPE_10__ ;

/* Type definitions */
struct TYPE_95__ {scalar_t__ width; int /*<<< orphan*/  colorRef; } ;
struct TYPE_94__ {scalar_t__ width; void* colorRef; } ;
struct TYPE_93__ {int /*<<< orphan*/ * hbrBackground; int /*<<< orphan*/  bEmulateVersion10; } ;
struct TYPE_92__ {int y; int x; } ;
struct TYPE_63__ {scalar_t__ width; void* colorRef; } ;
struct TYPE_59__ {scalar_t__ width; int /*<<< orphan*/  colorRef; } ;
struct TYPE_65__ {TYPE_19__ right; TYPE_15__ bottom; TYPE_9__ top; TYPE_8__ left; } ;
struct TYPE_85__ {int nHeight; int yTextOffset; int nWidth; TYPE_20__ border; TYPE_18__* next_cell; TYPE_6__ pt; } ;
struct TYPE_64__ {TYPE_39__ cell; } ;
struct TYPE_91__ {TYPE_1__ member; } ;
struct TYPE_75__ {TYPE_5__* pCell; } ;
struct TYPE_86__ {TYPE_2__ para; } ;
struct TYPE_90__ {TYPE_3__ member; } ;
struct TYPE_72__ {int nHeight; } ;
struct TYPE_68__ {int x; } ;
struct TYPE_69__ {TYPE_23__ pt; } ;
struct TYPE_73__ {TYPE_27__ row; TYPE_24__ run; } ;
struct TYPE_89__ {TYPE_28__ member; } ;
struct TYPE_54__ {TYPE_37__* next_para; } ;
struct TYPE_55__ {TYPE_10__ para; } ;
struct TYPE_88__ {TYPE_11__ member; } ;
struct TYPE_87__ {scalar_t__ lbHatch; void* lbColor; void* lbStyle; } ;
struct TYPE_70__ {int y; int x; } ;
struct TYPE_84__ {int /*<<< orphan*/  hDC; TYPE_25__ pt; TYPE_7__* editor; } ;
struct TYPE_56__ {int x; } ;
struct TYPE_57__ {TYPE_12__ pt; int /*<<< orphan*/  next_cell; } ;
struct TYPE_78__ {int dwMask; int wEffects; int dxOffset; int dxStartIndent; scalar_t__ dySpaceBefore; int cTabCount; int* rgxTabs; } ;
struct TYPE_71__ {int y; } ;
struct TYPE_66__ {int /*<<< orphan*/  colorRef; } ;
struct TYPE_67__ {TYPE_21__ top; } ;
struct TYPE_82__ {int nHeight; int nFlags; int nRows; TYPE_32__ fmt; TYPE_31__* next_para; TYPE_26__ pt; TYPE_22__ border; TYPE_5__* pCell; TYPE_4__* prev_para; } ;
struct TYPE_58__ {TYPE_13__ cell; TYPE_36__ para; } ;
struct TYPE_83__ {TYPE_14__ member; } ;
struct TYPE_81__ {int dwMask; scalar_t__ wEffects; } ;
struct TYPE_80__ {int x; int y; } ;
struct TYPE_79__ {int left; int right; int top; int bottom; } ;
struct TYPE_74__ {TYPE_35__ fmt; TYPE_5__* pCell; } ;
struct TYPE_76__ {TYPE_29__ para; } ;
struct TYPE_77__ {TYPE_30__ member; } ;
struct TYPE_60__ {int /*<<< orphan*/  next_cell; } ;
struct TYPE_61__ {TYPE_16__ cell; } ;
struct TYPE_62__ {TYPE_17__ member; } ;
typedef  TYPE_33__ RECT ;
typedef  TYPE_34__ POINT ;
typedef  TYPE_35__ PARAFORMAT2 ;
typedef  TYPE_36__ ME_Paragraph ;
typedef  TYPE_37__ ME_DisplayItem ;
typedef  TYPE_38__ ME_Context ;
typedef  TYPE_39__ ME_Cell ;
typedef  TYPE_40__ LOGBRUSH ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/ * HBRUSH ;
typedef  void* COLORREF ;
typedef  int BOOL ;

/* Variables and functions */
 void* BS_SOLID ; 
 int /*<<< orphan*/ * CreatePen (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExtCreatePen (int,int,TYPE_40__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_33__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTGRAY_BRUSH ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 TYPE_37__* ME_FindItemBack (TYPE_44__*,int /*<<< orphan*/ ) ; 
 TYPE_46__* ME_FindItemFwd (TYPE_37__*,int /*<<< orphan*/ ) ; 
 TYPE_44__* ME_GetTableRowEnd (TYPE_37__*) ; 
 int ME_twips2pointsX (TYPE_38__*,int) ; 
 int ME_twips2pointsY (TYPE_38__*,scalar_t__) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,TYPE_34__*) ; 
 int PFE_TABLE ; 
 int PFM_SPACEBEFORE ; 
 int PFM_TABLE ; 
 int PS_ENDCAP_FLAT ; 
 int PS_GEOMETRIC ; 
 int PS_JOIN_MITER ; 
 int PS_SOLID ; 
 void* RGB (int,int,int) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diCell ; 
 int /*<<< orphan*/  diRun ; 
 int /*<<< orphan*/  diStartRow ; 
 int max (int,int) ; 

__attribute__((used)) static void ME_DrawTableBorders(ME_Context *c, ME_DisplayItem *paragraph)
{
  ME_Paragraph *para = &paragraph->member.para;
  if (!c->editor->bEmulateVersion10) /* v4.1 */
  {
    if (para->pCell)
    {
      RECT rc;
      ME_Cell *cell = &para->pCell->member.cell;
      ME_DisplayItem *paraAfterRow;
      HPEN pen, oldPen;
      LOGBRUSH logBrush;
      HBRUSH brush;
      COLORREF color;
      POINT oldPt;
      int width;
      BOOL atTop = (para->pCell != para->prev_para->member.para.pCell);
      BOOL atBottom = (para->pCell != para->next_para->member.para.pCell);
      int top = c->pt.y + (atTop ? cell->pt.y : para->pt.y);
      int bottom = (atBottom ?
                    c->pt.y + cell->pt.y + cell->nHeight :
                    top + para->nHeight + (atTop ? cell->yTextOffset : 0));
      rc.left = c->pt.x + cell->pt.x;
      rc.right = rc.left + cell->nWidth;
      if (atTop) {
        /* Erase gap before text if not all borders are the same height. */
        width = max(ME_twips2pointsY(c, cell->border.top.width), 1);
        rc.top = top + width;
        width = cell->yTextOffset - width;
        rc.bottom = rc.top + width;
        if (width) {
          FillRect(c->hDC, &rc, c->editor->hbrBackground);
        }
      }
      /* Draw cell borders.
       * The order borders are draw in is left, top, bottom, right in order
       * to be consistent with native richedit.  This is noticeable from the
       * overlap of borders of different colours. */
      if (!(para->nFlags & MEPF_ROWEND)) {
        rc.top = top;
        rc.bottom = bottom;
        if (cell->border.left.width > 0)
        {
          color = cell->border.left.colorRef;
          width = max(ME_twips2pointsX(c, cell->border.left.width), 1);
        } else {
          color = RGB(192,192,192);
          width = 1;
        }
        logBrush.lbStyle = BS_SOLID;
        logBrush.lbColor = color;
        logBrush.lbHatch = 0;
        pen = ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT|PS_JOIN_MITER,
                           width, &logBrush, 0, NULL);
        oldPen = SelectObject(c->hDC, pen);
        MoveToEx(c->hDC, rc.left, rc.top, &oldPt);
        LineTo(c->hDC, rc.left, rc.bottom);
        SelectObject(c->hDC, oldPen);
        DeleteObject(pen);
        MoveToEx(c->hDC, oldPt.x, oldPt.y, NULL);
      }

      if (atTop) {
        if (cell->border.top.width > 0)
        {
          brush = CreateSolidBrush(cell->border.top.colorRef);
          width = max(ME_twips2pointsY(c, cell->border.top.width), 1);
        } else {
          brush = GetStockObject(LTGRAY_BRUSH);
          width = 1;
        }
        rc.top = top;
        rc.bottom = rc.top + width;
        FillRect(c->hDC, &rc, brush);
        if (cell->border.top.width > 0)
          DeleteObject(brush);
      }

      /* Draw the bottom border if at the last paragraph in the cell, and when
       * in the last row of the table. */
      if (atBottom) {
        int oldLeft = rc.left;
        width = max(ME_twips2pointsY(c, cell->border.bottom.width), 1);
        paraAfterRow = ME_GetTableRowEnd(paragraph)->member.para.next_para;
        if (paraAfterRow->member.para.nFlags & MEPF_ROWSTART) {
          ME_DisplayItem *nextEndCell;
          nextEndCell = ME_FindItemBack(ME_GetTableRowEnd(paraAfterRow), diCell);
          assert(nextEndCell && !nextEndCell->member.cell.next_cell);
          rc.left = c->pt.x + nextEndCell->member.cell.pt.x;
          /* FIXME: Native draws FROM the bottom of the table rather than
           * TO the bottom of the table in this case, but just doing so here
           * will cause the next row to erase the border. */
          /*
          rc.top = bottom;
          rc.bottom = rc.top + width;
           */
        }
        if (rc.left < rc.right) {
          if (cell->border.bottom.width > 0) {
            brush = CreateSolidBrush(cell->border.bottom.colorRef);
          } else {
            brush = GetStockObject(LTGRAY_BRUSH);
          }
          rc.bottom = bottom;
          rc.top = rc.bottom - width;
          FillRect(c->hDC, &rc, brush);
          if (cell->border.bottom.width > 0)
            DeleteObject(brush);
        }
        rc.left = oldLeft;
      }

      /* Right border only drawn if at the end of the table row. */
      if (!cell->next_cell->member.cell.next_cell &&
          !(para->nFlags & MEPF_ROWSTART))
      {
        rc.top = top;
        rc.bottom = bottom;
        if (cell->border.right.width > 0) {
          color = cell->border.right.colorRef;
          width = max(ME_twips2pointsX(c, cell->border.right.width), 1);
        } else {
          color = RGB(192,192,192);
          width = 1;
        }
        logBrush.lbStyle = BS_SOLID;
        logBrush.lbColor = color;
        logBrush.lbHatch = 0;
        pen = ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT|PS_JOIN_MITER,
                           width, &logBrush, 0, NULL);
        oldPen = SelectObject(c->hDC, pen);
        MoveToEx(c->hDC, rc.right - 1, rc.top, &oldPt);
        LineTo(c->hDC, rc.right - 1, rc.bottom);
        SelectObject(c->hDC, oldPen);
        DeleteObject(pen);
        MoveToEx(c->hDC, oldPt.x, oldPt.y, NULL);
      }
    }
  } else { /* v1.0 - 3.0 */
    /* Draw simple table border */
    if (para->fmt.dwMask & PFM_TABLE && para->fmt.wEffects & PFE_TABLE) {
      HPEN pen = NULL, oldpen = NULL;
      int i, firstX, startX, endX, rowY, rowBottom, nHeight;
      POINT oldPt;
      PARAFORMAT2 *pNextFmt;

      pen = CreatePen(PS_SOLID, 0, para->border.top.colorRef);
      oldpen = SelectObject(c->hDC, pen);

      /* Find the start relative to the text */
      firstX = c->pt.x + ME_FindItemFwd(paragraph, diRun)->member.run.pt.x;
      /* Go back by the horizontal gap, which is stored in dxOffset */
      firstX -= ME_twips2pointsX(c, para->fmt.dxOffset);
      /* The left edge, stored in dxStartIndent affected just the first edge */
      startX = firstX - ME_twips2pointsX(c, para->fmt.dxStartIndent);
      rowY = c->pt.y + para->pt.y;
      if (para->fmt.dwMask & PFM_SPACEBEFORE)
        rowY += ME_twips2pointsY(c, para->fmt.dySpaceBefore);
      nHeight = ME_FindItemFwd(paragraph, diStartRow)->member.row.nHeight;
      rowBottom = rowY + nHeight;

      /* Draw horizontal lines */
      MoveToEx(c->hDC, firstX, rowY, &oldPt);
      i = para->fmt.cTabCount - 1;
      endX = startX + ME_twips2pointsX(c, para->fmt.rgxTabs[i] & 0x00ffffff) + 1;
      LineTo(c->hDC, endX, rowY);
      pNextFmt = &para->next_para->member.para.fmt;
      /* The bottom of the row only needs to be drawn if the next row is
       * not a table. */
      if (!(pNextFmt && pNextFmt->dwMask & PFM_TABLE && pNextFmt->wEffects &&
            para->nRows == 1))
      {
        /* Decrement rowBottom to draw the bottom line within the row, and
         * to not draw over this line when drawing the vertical lines. */
        rowBottom--;
        MoveToEx(c->hDC, firstX, rowBottom, NULL);
        LineTo(c->hDC, endX, rowBottom);
      }

      /* Draw vertical lines */
      MoveToEx(c->hDC, firstX, rowY, NULL);
      LineTo(c->hDC, firstX, rowBottom);
      for (i = 0; i < para->fmt.cTabCount; i++)
      {
        int rightBoundary = para->fmt.rgxTabs[i] & 0x00ffffff;
        endX = startX + ME_twips2pointsX(c, rightBoundary);
        MoveToEx(c->hDC, endX, rowY, NULL);
        LineTo(c->hDC, endX, rowBottom);
      }

      MoveToEx(c->hDC, oldPt.x, oldPt.y, NULL);
      SelectObject(c->hDC, oldpen);
      DeleteObject(pen);
    }
  }
}