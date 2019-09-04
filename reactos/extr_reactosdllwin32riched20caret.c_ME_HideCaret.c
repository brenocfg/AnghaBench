#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  texthost; int /*<<< orphan*/  bHaveFocus; } ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyCaret () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ITextHost_TxShowCaret (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ME_IsSelection (TYPE_1__*) ; 

void ME_HideCaret(ME_TextEditor *ed)
{
  if(!ed->bHaveFocus || ME_IsSelection(ed))
  {
    ITextHost_TxShowCaret(ed->texthost, FALSE);
    DestroyCaret();
  }
}