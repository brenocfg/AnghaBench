#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nFlags; TYPE_4__* pCell; TYPE_4__* next_para; } ;
struct TYPE_10__ {TYPE_4__* next_cell; } ;
struct TYPE_11__ {TYPE_3__ para; TYPE_1__ cell; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_2__ member; } ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 TYPE_4__* ME_FindItemFwd (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 scalar_t__ diCell ; 
 int /*<<< orphan*/  diParagraph ; 

ME_DisplayItem* ME_GetTableRowEnd(ME_DisplayItem *para)
{
  ME_DisplayItem *cell;
  assert(para);
  if (para->member.para.nFlags & MEPF_ROWEND)
    return para;
  if (para->member.para.nFlags & MEPF_ROWSTART)
    para = para->member.para.next_para;
  cell = para->member.para.pCell;
  assert(cell && cell->type == diCell);
  while (cell->member.cell.next_cell)
    cell = cell->member.cell.next_cell;

  para = ME_FindItemFwd(cell, diParagraph);
  assert(para && para->member.para.nFlags & MEPF_ROWEND);
  return para;
}