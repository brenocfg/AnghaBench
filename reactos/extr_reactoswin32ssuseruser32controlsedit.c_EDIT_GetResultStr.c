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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ selection_end; scalar_t__ composition_start; scalar_t__ selection_start; scalar_t__ composition_len; } ;
typedef  scalar_t__* LPWSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HIMC ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GCS_RESULTSTR ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ImmGetCompositionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void EDIT_GetResultStr(HIMC hIMC, EDITSTATE *es)
{
    LONG buflen;
    LPWSTR lpResultStr;

    buflen = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);
    if (buflen <= 0)
    {
        return;
    }

    lpResultStr = HeapAlloc(GetProcessHeap(),0, buflen+sizeof(WCHAR));
    if (!lpResultStr)
    {
        ERR("Unable to alloc buffer for IME string\n");
        return;
    }

    ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpResultStr, buflen);
    lpResultStr[buflen/sizeof(WCHAR)] = 0;

    /* check for change in composition start */
    if (es->selection_end < es->composition_start)
        es->composition_start = es->selection_end;

    es->selection_start = es->composition_start;
    es->selection_end = es->composition_start + es->composition_len;
    EDIT_EM_ReplaceSel(es, TRUE, lpResultStr, TRUE, TRUE);
    es->composition_start = es->selection_end;
    es->composition_len = 0;

    HeapFree(GetProcessHeap(),0,lpResultStr);
}