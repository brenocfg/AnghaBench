#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int top; int right; int /*<<< orphan*/  left; } ;
struct TYPE_4__ {int exStyleFlags; TYPE_3__ rcFormat; scalar_t__ selofs; int /*<<< orphan*/  texthost; } ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_TxGetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int WS_EX_CLIENTEDGE ; 

__attribute__((used)) static void ME_SetDefaultFormatRect(ME_TextEditor *editor)
{
  ITextHost_TxGetClientRect(editor->texthost, &editor->rcFormat);
  editor->rcFormat.top += editor->exStyleFlags & WS_EX_CLIENTEDGE ? 1 : 0;
  editor->rcFormat.left += 1 + editor->selofs;
  editor->rcFormat.right -= 1;
}