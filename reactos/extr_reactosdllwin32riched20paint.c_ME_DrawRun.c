#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ y; } ;
struct TYPE_29__ {TYPE_1__ pt; int /*<<< orphan*/  editor; } ;
struct TYPE_23__ {scalar_t__ y; } ;
struct TYPE_24__ {int /*<<< orphan*/  nHeight; TYPE_3__ pt; } ;
struct TYPE_26__ {int nCharOfs; int nFlags; } ;
struct TYPE_25__ {TYPE_4__ row; TYPE_6__ run; } ;
struct TYPE_28__ {TYPE_5__ member; } ;
struct TYPE_22__ {scalar_t__ y; } ;
struct TYPE_27__ {int nCharOfs; TYPE_2__ pt; } ;
typedef  TYPE_6__ ME_Run ;
typedef  TYPE_7__ ME_Paragraph ;
typedef  TYPE_8__ ME_DisplayItem ;
typedef  TYPE_9__ ME_Context ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int MERF_ENDCELL ; 
 int MERF_ENDPARA ; 
 int MERF_GRAPHICS ; 
 int MERF_HIDDEN ; 
 int MERF_TAB ; 
 int /*<<< orphan*/  ME_DrawOLE (TYPE_9__*,int,int,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ME_DrawTextWithStyle (TYPE_9__*,TYPE_6__*,int,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_8__* ME_FindItemBack (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (int /*<<< orphan*/ ,int*,int*) ; 
 int TRUE ; 
 int /*<<< orphan*/  diStartRow ; 
 int /*<<< orphan*/  draw_space (TYPE_9__*,TYPE_6__*,int,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ME_DrawRun(ME_Context *c, int x, int y, ME_DisplayItem *rundi, ME_Paragraph *para) 
{
  ME_Run *run = &rundi->member.run;
  ME_DisplayItem *start;
  int runofs = run->nCharOfs+para->nCharOfs;
  int nSelFrom, nSelTo;
  
  if (run->nFlags & MERF_HIDDEN)
    return;

  start = ME_FindItemBack(rundi, diStartRow);
  ME_GetSelectionOfs(c->editor, &nSelFrom, &nSelTo);

  /* Draw selected end-of-paragraph mark */
  if (run->nFlags & MERF_ENDPARA)
  {
    if (runofs >= nSelFrom && runofs < nSelTo)
    {
      draw_space( c, run, x, y, TRUE, FALSE,
                  c->pt.y + para->pt.y + start->member.row.pt.y,
                  start->member.row.nHeight );
    }
    return;
  }

  if (run->nFlags & (MERF_TAB | MERF_ENDCELL))
  {
    BOOL selected = runofs >= nSelFrom && runofs < nSelTo;

    draw_space( c, run, x, y, selected, TRUE,
                c->pt.y + para->pt.y + start->member.row.pt.y,
                start->member.row.nHeight );
    return;
  }

  if (run->nFlags & MERF_GRAPHICS)
    ME_DrawOLE(c, x, y, run, (runofs >= nSelFrom) && (runofs < nSelTo));
  else
  {
    ME_DrawTextWithStyle(c, run, x, y, nSelFrom - runofs, nSelTo - runofs,
                         c->pt.y + para->pt.y + start->member.row.pt.y,
                         start->member.row.nHeight);
  }
}