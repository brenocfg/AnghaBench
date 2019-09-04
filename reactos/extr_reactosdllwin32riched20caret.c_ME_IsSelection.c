#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pCursors; } ;
struct TYPE_4__ {scalar_t__ pRun; scalar_t__ nOffset; } ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  int BOOL ;

/* Variables and functions */

BOOL ME_IsSelection(ME_TextEditor *editor)
{
  return editor->pCursors[0].pRun != editor->pCursors[1].pRun ||
         editor->pCursors[0].nOffset != editor->pCursors[1].nOffset;
}