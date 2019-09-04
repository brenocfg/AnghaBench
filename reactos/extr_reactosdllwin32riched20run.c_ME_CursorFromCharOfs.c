#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nOffset; int /*<<< orphan*/  pRun; int /*<<< orphan*/  pPara; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_1__ ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  ME_RunOfsFromCharOfs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ME_CursorFromCharOfs(ME_TextEditor *editor, int nCharOfs, ME_Cursor *pCursor)
{
  ME_RunOfsFromCharOfs(editor, nCharOfs, &pCursor->pPara,
                       &pCursor->pRun, &pCursor->nOffset);
}