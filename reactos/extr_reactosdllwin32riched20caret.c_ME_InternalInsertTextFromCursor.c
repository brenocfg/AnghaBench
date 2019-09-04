#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {TYPE_1__* pRun; } ;
struct TYPE_8__ {int /*<<< orphan*/  bCaretAtEnd; TYPE_3__* pCursors; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  int /*<<< orphan*/  ME_DisplayItem ;
typedef  TYPE_3__ ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * ME_InsertRunAtCursor (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diRun ; 

__attribute__((used)) static ME_DisplayItem *
ME_InternalInsertTextFromCursor(ME_TextEditor *editor, int nCursor,
                                const WCHAR *str, int len, ME_Style *style,
                                int flags)
{
  ME_Cursor *p = &editor->pCursors[nCursor];

  editor->bCaretAtEnd = FALSE;
  
  assert(p->pRun->type == diRun);
  
  return ME_InsertRunAtCursor(editor, p, style, str, len, flags);
}