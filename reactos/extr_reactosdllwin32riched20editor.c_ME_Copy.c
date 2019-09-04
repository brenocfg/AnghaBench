#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cpMin; scalar_t__ cpMax; } ;
struct TYPE_6__ {scalar_t__ lpOleCallback; scalar_t__ cPasswordMask; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/ * LPDATAOBJECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ CHARRANGE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRichEditOleCallback_GetClipboardData (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ME_GetCursorOfs (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ME_GetDataObject (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  OleSetClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECO_COPY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static BOOL ME_Copy(ME_TextEditor *editor, const ME_Cursor *start, int nChars)
{
  LPDATAOBJECT dataObj = NULL;
  HRESULT hr = S_OK;

  if (editor->cPasswordMask)
    return FALSE; /* Copying or Cutting masked text isn't allowed */

  if(editor->lpOleCallback)
  {
    CHARRANGE range;
    range.cpMin = ME_GetCursorOfs(start);
    range.cpMax = range.cpMin + nChars;
    hr = IRichEditOleCallback_GetClipboardData(editor->lpOleCallback, &range, RECO_COPY, &dataObj);
  }
  if(FAILED(hr) || !dataObj)
    hr = ME_GetDataObject(editor, start, nChars, &dataObj);
  if(SUCCEEDED(hr)) {
    hr = OleSetClipboard(dataObj);
    IDataObject_Release(dataObj);
  }
  return SUCCEEDED(hr);
}