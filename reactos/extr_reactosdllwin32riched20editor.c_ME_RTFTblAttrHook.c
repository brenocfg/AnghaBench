#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_2__* pCursors; int /*<<< orphan*/  bEmulateVersion10; } ;
struct TYPE_18__ {int* rgxTabs; } ;
struct TYPE_15__ {TYPE_6__ fmt; } ;
struct TYPE_16__ {TYPE_3__ para; } ;
struct TYPE_19__ {TYPE_4__ member; } ;
struct TYPE_17__ {int rtfMinor; int rtfParam; TYPE_11__* tableDef; void* borderType; TYPE_9__* editor; } ;
struct TYPE_14__ {TYPE_7__* pPara; } ;
struct TYPE_13__ {int rightBoundary; } ;
struct TYPE_12__ {int numCellsDefined; int gapH; int leftEdge; TYPE_1__* cells; } ;
typedef  TYPE_5__ RTF_Info ;
typedef  TYPE_6__ PARAFORMAT2 ;
typedef  TYPE_7__ ME_DisplayItem ;

/* Variables and functions */
 int MAX_TABLE_CELLS ; 
 int MAX_TAB_STOPS ; 
 int /*<<< orphan*/  ME_InitTableDef (TYPE_9__*,TYPE_11__*) ; 
 void* ME_MakeTableDef (TYPE_9__*) ; 
 void* RTFBorderCellBottom ; 
 void* RTFBorderCellLeft ; 
 void* RTFBorderCellRight ; 
 void* RTFBorderCellTop ; 
 void* RTFBorderRowBottom ; 
 void* RTFBorderRowLeft ; 
 void* RTFBorderRowRight ; 
 void* RTFBorderRowTop ; 
#define  rtfCellBordBottom 139 
#define  rtfCellBordLeft 138 
#define  rtfCellBordRight 137 
#define  rtfCellBordTop 136 
#define  rtfCellPos 135 
#define  rtfRowBordBottom 134 
#define  rtfRowBordLeft 133 
#define  rtfRowBordRight 132 
#define  rtfRowBordTop 131 
#define  rtfRowDef 130 
#define  rtfRowGapH 129 
#define  rtfRowLeftEdge 128 

void ME_RTFTblAttrHook(RTF_Info *info)
{
  switch (info->rtfMinor)
  {
    case rtfRowDef:
    {
      if (!info->editor->bEmulateVersion10) /* v4.1 */
        info->borderType = 0; /* Not sure */
      else /* v1.0 - 3.0 */
        info->borderType = RTFBorderRowTop;
      if (!info->tableDef) {
        info->tableDef = ME_MakeTableDef(info->editor);
      } else {
        ME_InitTableDef(info->editor, info->tableDef);
      }
      break;
    }
    case rtfCellPos:
    {
      int cellNum;
      if (!info->tableDef)
      {
        info->tableDef = ME_MakeTableDef(info->editor);
      }
      cellNum = info->tableDef->numCellsDefined;
      if (cellNum >= MAX_TABLE_CELLS)
        break;
      info->tableDef->cells[cellNum].rightBoundary = info->rtfParam;
      if (cellNum < MAX_TAB_STOPS) {
        /* Tab stops were used to store cell positions before v4.1 but v4.1
         * still seems to set the tabstops without using them. */
        ME_DisplayItem *para = info->editor->pCursors[0].pPara;
        PARAFORMAT2 *pFmt = &para->member.para.fmt;
        pFmt->rgxTabs[cellNum] &= ~0x00FFFFFF;
        pFmt->rgxTabs[cellNum] |= 0x00FFFFFF & info->rtfParam;
      }
      info->tableDef->numCellsDefined++;
      break;
    }
    case rtfRowBordTop:
      info->borderType = RTFBorderRowTop;
      break;
    case rtfRowBordLeft:
      info->borderType = RTFBorderRowLeft;
      break;
    case rtfRowBordBottom:
      info->borderType = RTFBorderRowBottom;
      break;
    case rtfRowBordRight:
      info->borderType = RTFBorderRowRight;
      break;
    case rtfCellBordTop:
      info->borderType = RTFBorderCellTop;
      break;
    case rtfCellBordLeft:
      info->borderType = RTFBorderCellLeft;
      break;
    case rtfCellBordBottom:
      info->borderType = RTFBorderCellBottom;
      break;
    case rtfCellBordRight:
      info->borderType = RTFBorderCellRight;
      break;
    case rtfRowGapH:
      if (info->tableDef)
        info->tableDef->gapH = info->rtfParam;
      break;
    case rtfRowLeftEdge:
      if (info->tableDef)
        info->tableDef->leftEdge = info->rtfParam;
      break;
  }
}