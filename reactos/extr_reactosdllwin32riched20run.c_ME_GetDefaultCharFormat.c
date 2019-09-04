#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* pBuffer; } ;
struct TYPE_6__ {TYPE_1__* pDefaultStyle; } ;
struct TYPE_5__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  int /*<<< orphan*/  CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/  ME_CopyCharFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ME_GetDefaultCharFormat(ME_TextEditor *editor, CHARFORMAT2W *pFmt)
{
  ME_CopyCharFormat(pFmt, &editor->pBuffer->pDefaultStyle->fmt);
}