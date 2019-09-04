#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  texthost; scalar_t__ bHaveFocus; } ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_TxShowCaret (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_IsSelection (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_MoveCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

void ME_ShowCaret(ME_TextEditor *ed)
{
  ME_MoveCaret(ed);
  if(ed->bHaveFocus && !ME_IsSelection(ed))
    ITextHost_TxShowCaret(ed->texthost, TRUE);
}