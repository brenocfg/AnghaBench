#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nOffset; TYPE_6__* pRun; TYPE_3__* pPara; } ;
struct TYPE_12__ {int nCharOfs; } ;
struct TYPE_13__ {TYPE_4__ run; } ;
struct TYPE_14__ {TYPE_5__ member; } ;
struct TYPE_9__ {int nCharOfs; } ;
struct TYPE_10__ {TYPE_1__ para; } ;
struct TYPE_11__ {TYPE_2__ member; } ;
typedef  TYPE_7__ ME_Cursor ;

/* Variables and functions */

int ME_GetCursorOfs(const ME_Cursor *cursor)
{
  return cursor->pPara->member.para.nCharOfs
         + cursor->pRun->member.run.nCharOfs + cursor->nOffset;
}