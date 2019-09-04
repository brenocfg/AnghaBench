#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nEventMask; scalar_t__ nTotalLength; int /*<<< orphan*/  texthost; int /*<<< orphan*/  nTotalWidth; } ;
struct TYPE_10__ {scalar_t__ bottom; int /*<<< orphan*/  right; } ;
struct TYPE_8__ {int /*<<< orphan*/  code; scalar_t__ idFrom; int /*<<< orphan*/ * hwndFrom; } ;
struct TYPE_9__ {TYPE_1__ nmhdr; TYPE_3__ rc; } ;
typedef  TYPE_2__ REQRESIZE ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ENM_REQUESTRESIZE ; 
 int /*<<< orphan*/  EN_REQUESTRESIZE ; 
 int /*<<< orphan*/  ITextHost_TxGetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ITextHost_TxNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
ME_SendRequestResize(ME_TextEditor *editor, BOOL force)
{
  if (editor->nEventMask & ENM_REQUESTRESIZE)
  {
    RECT rc;

    ITextHost_TxGetClientRect(editor->texthost, &rc);

    if (force || rc.bottom != editor->nTotalLength)
    {
      REQRESIZE info;

      info.nmhdr.hwndFrom = NULL;
      info.nmhdr.idFrom = 0;
      info.nmhdr.code = EN_REQUESTRESIZE;
      info.rc = rc;
      info.rc.right = editor->nTotalWidth;
      info.rc.bottom = editor->nTotalLength;

      editor->nEventMask &= ~ENM_REQUESTRESIZE;
      ITextHost_TxNotify(editor->texthost, info.nmhdr.code, &info);
      editor->nEventMask |= ENM_REQUESTRESIZE;
    }
  }
}