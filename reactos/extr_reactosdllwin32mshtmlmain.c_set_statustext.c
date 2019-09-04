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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  frame; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int INT ;
typedef  TYPE_1__ HTMLDocumentObj ;
typedef  int DWORD ;

/* Variables and functions */
 int IDS_STATUS_FIRST ; 
 int /*<<< orphan*/  IOleInPlaceFrame_SetStatusText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int LoadStringW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,int) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** status_strings ; 

void set_statustext(HTMLDocumentObj* doc, INT id, LPCWSTR arg)
{
    int index = id - IDS_STATUS_FIRST;
    WCHAR *p = status_strings[index];
    DWORD len;

    if(!doc->frame)
        return;

    if(!p) {
        len = 255;
        p = heap_alloc(len * sizeof(WCHAR));
        len = LoadStringW(hInst, id, p, len) + 1;
        p = heap_realloc(p, len * sizeof(WCHAR));
        if(InterlockedCompareExchangePointer((void**)&status_strings[index], p, NULL)) {
            heap_free(p);
            p = status_strings[index];
        }
    }

    if(arg) {
        WCHAR *buf;

        len = lstrlenW(p) + lstrlenW(arg) - 1;
        buf = heap_alloc(len * sizeof(WCHAR));

        snprintfW(buf, len, p, arg);

        p = buf;
    }

    IOleInPlaceFrame_SetStatusText(doc->frame, p);

    if(arg)
        heap_free(p);
}