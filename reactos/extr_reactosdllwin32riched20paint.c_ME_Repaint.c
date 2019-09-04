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
struct TYPE_5__ {int /*<<< orphan*/  texthost; } ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  ITextHost_TxViewChange (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_UpdateScrollBar (TYPE_1__*) ; 
 scalar_t__ ME_WrapMarkedParagraphs (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

void ME_Repaint(ME_TextEditor *editor)
{
  if (ME_WrapMarkedParagraphs(editor))
  {
    ME_UpdateScrollBar(editor);
    FIXME("ME_Repaint had to call ME_WrapMarkedParagraphs\n");
  }
  ITextHost_TxViewChange(editor->texthost, TRUE);
}