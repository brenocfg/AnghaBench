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
struct TYPE_9__ {scalar_t__ nPos; } ;
struct TYPE_8__ {scalar_t__ nPos; } ;
struct TYPE_11__ {TYPE_2__ vert_si; TYPE_1__ horz_si; int /*<<< orphan*/  texthost; } ;
struct TYPE_10__ {int right; int bottom; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ITextHost_TxGetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ME_FindPixelPos (TYPE_4__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL ME_CharFromPos(ME_TextEditor *editor, int x, int y,
                    ME_Cursor *cursor, BOOL *isExact)
{
  RECT rc;
  BOOL bResult;

  ITextHost_TxGetClientRect(editor->texthost, &rc);
  if (x < 0 || y < 0 || x >= rc.right || y >= rc.bottom) {
    if (isExact) *isExact = FALSE;
    return FALSE;
  }
  x += editor->horz_si.nPos;
  y += editor->vert_si.nPos;
  bResult = ME_FindPixelPos(editor, x, y, cursor, NULL, FALSE);
  if (isExact) *isExact = bResult;
  return TRUE;
}