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
struct TYPE_14__ {scalar_t__ nOffset; int /*<<< orphan*/  pPara; int /*<<< orphan*/  pRun; } ;
struct TYPE_13__ {TYPE_4__* pBuffer; } ;
struct TYPE_12__ {TYPE_3__* pFirst; } ;
struct TYPE_9__ {int /*<<< orphan*/  next_para; } ;
struct TYPE_10__ {TYPE_1__ para; } ;
struct TYPE_11__ {TYPE_2__ member; } ;
typedef  TYPE_5__ ME_TextEditor ;
typedef  TYPE_6__ ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  ME_FindItemFwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diRun ; 

void ME_SetCursorToStart(ME_TextEditor *editor, ME_Cursor *cursor)
{
  cursor->pPara = editor->pBuffer->pFirst->member.para.next_para;
  cursor->pRun = ME_FindItemFwd(cursor->pPara, diRun);
  cursor->nOffset = 0;
}