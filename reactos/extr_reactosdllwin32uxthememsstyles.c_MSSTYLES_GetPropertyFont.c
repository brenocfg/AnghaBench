#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dwValueLen; scalar_t__ lpValue; } ;
typedef  TYPE_1__* PTHEME_PROPERTY ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  MSSTYLES_GetFont (scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 

HRESULT MSSTYLES_GetPropertyFont(PTHEME_PROPERTY tp, HDC hdc, LOGFONTW *pFont)
{
    LPCWSTR lpCur = tp->lpValue;
    LPCWSTR lpEnd = tp->lpValue + tp->dwValueLen;
    HRESULT hr; 

    ZeroMemory(pFont, sizeof(LOGFONTW));
    hr = MSSTYLES_GetFont (lpCur, lpEnd, &lpCur, pFont);

    return hr;
}