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
struct TYPE_6__ {int nFlags; int nCharOfs; int /*<<< orphan*/ * clusters; scalar_t__ max_clusters; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * advances; int /*<<< orphan*/ * vis_attrs; int /*<<< orphan*/ * glyphs; scalar_t__ max_glyphs; scalar_t__ num_glyphs; int /*<<< orphan*/ * para; scalar_t__ len; int /*<<< orphan*/ * reobj; int /*<<< orphan*/ * style; } ;
struct TYPE_7__ {TYPE_1__ run; } ;
struct TYPE_8__ {TYPE_2__ member; } ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_3__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ME_AddRefStyle (int /*<<< orphan*/ *) ; 
 TYPE_3__* ME_MakeDI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diRun ; 

ME_DisplayItem *ME_MakeRun(ME_Style *s, int nFlags)
{
  ME_DisplayItem *item = ME_MakeDI(diRun);
  item->member.run.style = s;
  item->member.run.reobj = NULL;
  item->member.run.nFlags = nFlags;
  item->member.run.nCharOfs = -1;
  item->member.run.len = 0;
  item->member.run.para = NULL;
  item->member.run.num_glyphs = 0;
  item->member.run.max_glyphs = 0;
  item->member.run.glyphs = NULL;
  item->member.run.vis_attrs = NULL;
  item->member.run.advances = NULL;
  item->member.run.offsets = NULL;
  item->member.run.max_clusters = 0;
  item->member.run.clusters = NULL;
  ME_AddRefStyle(s);
  return item;
}