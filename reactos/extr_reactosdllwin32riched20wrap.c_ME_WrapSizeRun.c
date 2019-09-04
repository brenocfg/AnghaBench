#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  editor; } ;
struct TYPE_9__ {int /*<<< orphan*/  run; } ;
struct TYPE_13__ {TYPE_1__ member; } ;
struct TYPE_12__ {int /*<<< orphan*/  nFirstMargin; int /*<<< orphan*/  nLeftMargin; scalar_t__ nRow; TYPE_3__* pPara; TYPE_6__* context; } ;
struct TYPE_10__ {int /*<<< orphan*/  para; } ;
struct TYPE_11__ {TYPE_2__ member; } ;
typedef  TYPE_4__ ME_WrapContext ;
typedef  TYPE_5__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ME_UpdateRunFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calc_run_extent (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ME_WrapSizeRun(ME_WrapContext *wc, ME_DisplayItem *p)
{
  /* FIXME compose style (out of character and paragraph styles) here */

  ME_UpdateRunFlags(wc->context->editor, &p->member.run);

  calc_run_extent(wc->context, &wc->pPara->member.para,
                  wc->nRow ? wc->nLeftMargin : wc->nFirstMargin, &p->member.run);
}