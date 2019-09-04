#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* style; } ;
struct TYPE_8__ {TYPE_2__ run; } ;
struct TYPE_9__ {TYPE_3__ member; } ;
struct TYPE_6__ {int /*<<< orphan*/  fmt; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/  ME_CopyCharFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ME_GetRunCharFormat(ME_TextEditor *editor, ME_DisplayItem *run, CHARFORMAT2W *pFmt)
{
  ME_CopyCharFormat(pFmt, &run->member.run.style->fmt);
}