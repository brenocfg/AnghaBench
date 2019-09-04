#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  unicode; TYPE_1__* ofnInfos; } ;
struct TYPE_9__ {int nMaxFile; scalar_t__* lpstrCustomFilter; scalar_t__* lpstrFilter; scalar_t__* lpstrFile; int /*<<< orphan*/  lpstrTitle; int /*<<< orphan*/  lpstrDefExt; int /*<<< orphan*/  lpstrInitialDir; } ;
struct TYPE_8__ {void* lpstrFile; int nMaxFile; void* lpstrCustomFilter; void* lpstrInitialDir; void* lpstrFilter; void* lpstrTitle; void* lpstrDefExt; } ;
typedef  TYPE_1__ OPENFILENAMEW ;
typedef  TYPE_2__ OPENFILENAMEA ;
typedef  scalar_t__* LPCSTR ;
typedef  TYPE_3__ FileOpenDlgInfos ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,void*,int) ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (void*) ; 
 void* heap_strdupAtoW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_filedlg_infoW (TYPE_1__*,TYPE_3__*) ; 
 int strlen (scalar_t__*) ; 

__attribute__((used)) static void init_filedlg_infoA(OPENFILENAMEA *ofn, FileOpenDlgInfos *info)
{
    OPENFILENAMEW ofnW;
    int len;

    ofnW = *(OPENFILENAMEW *)ofn;

    ofnW.lpstrInitialDir = heap_strdupAtoW(ofn->lpstrInitialDir);
    ofnW.lpstrDefExt = heap_strdupAtoW(ofn->lpstrDefExt);
    ofnW.lpstrTitle = heap_strdupAtoW(ofn->lpstrTitle);

    if (ofn->lpstrFile)
    {
        len = MultiByteToWideChar(CP_ACP, 0, ofn->lpstrFile, ofn->nMaxFile, NULL, 0);
        ofnW.lpstrFile = heap_alloc(len * sizeof(WCHAR));
        MultiByteToWideChar(CP_ACP, 0, ofn->lpstrFile, ofn->nMaxFile, ofnW.lpstrFile, len);
        ofnW.nMaxFile = len;
    }

    if (ofn->lpstrFilter)
    {
        LPCSTR s;
        int n;

        /* filter is a list...  title\0ext\0......\0\0 */
        s = ofn->lpstrFilter;
        while (*s) s = s+strlen(s)+1;
        s++;
        n = s - ofn->lpstrFilter;
        len = MultiByteToWideChar(CP_ACP, 0, ofn->lpstrFilter, n, NULL, 0);
        ofnW.lpstrFilter = heap_alloc(len * sizeof(WCHAR));
        MultiByteToWideChar(CP_ACP, 0, ofn->lpstrFilter, n, (WCHAR *)ofnW.lpstrFilter, len);
    }

    /* convert lpstrCustomFilter */
    if (ofn->lpstrCustomFilter)
    {
        int n, len;
        LPCSTR s;

        /* customfilter contains a pair of strings...  title\0ext\0 */
        s = ofn->lpstrCustomFilter;
        if (*s) s = s+strlen(s)+1;
        if (*s) s = s+strlen(s)+1;
        n = s - ofn->lpstrCustomFilter;
        len = MultiByteToWideChar(CP_ACP, 0, ofn->lpstrCustomFilter, n, NULL, 0);
        ofnW.lpstrCustomFilter = heap_alloc(len * sizeof(WCHAR));
        MultiByteToWideChar(CP_ACP, 0, ofn->lpstrCustomFilter, n, ofnW.lpstrCustomFilter, len);
    }

    init_filedlg_infoW(&ofnW, info);

    /* fixup A-specific fields */
    info->ofnInfos = (OPENFILENAMEW *)ofn;
    info->unicode = FALSE;

    /* free what was duplicated */
    heap_free((void *)ofnW.lpstrInitialDir);
    heap_free(ofnW.lpstrFile);
}