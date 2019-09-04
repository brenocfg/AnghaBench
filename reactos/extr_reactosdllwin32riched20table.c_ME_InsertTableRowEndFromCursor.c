#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* prev_para; } ;
struct TYPE_7__ {TYPE_1__ para; } ;
struct TYPE_8__ {TYPE_2__ member; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_3__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  MEPF_ROWEND ; 
 TYPE_3__* ME_InsertEndParaFromCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr_lf ; 

ME_DisplayItem* ME_InsertTableRowEndFromCursor(ME_TextEditor *editor)
{
  ME_DisplayItem *para;
  para = ME_InsertEndParaFromCursor(editor, 0, cr_lf, 2, MEPF_ROWEND);
  return para->member.para.prev_para;
}