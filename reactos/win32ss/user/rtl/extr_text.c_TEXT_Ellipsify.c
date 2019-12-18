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
typedef  char WCHAR ;
struct TYPE_5__ {int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 char* ELLIPSISW ; 
 scalar_t__ GetTextExtentExPointW (int /*<<< orphan*/ ,char*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ GreGetTextExtentExW (int /*<<< orphan*/ ,char*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 unsigned int strlenW (char*) ; 

__attribute__((used)) static void TEXT_Ellipsify (HDC hdc, WCHAR *str, unsigned int max_len,
                            unsigned int *len_str, int width, SIZE *size,
                            WCHAR *modstr,
                            int *len_before, int *len_ellip)
{
    unsigned int len_ellipsis;
    unsigned int lo, mid, hi;
    len_ellipsis = strlenW (ELLIPSISW);
    if (len_ellipsis > max_len) len_ellipsis = max_len;
    if (*len_str > max_len - len_ellipsis)
        *len_str = max_len - len_ellipsis;

    /* First do a quick binary search to get an upper bound for *len_str. */
    if (*len_str > 0 &&
#ifdef _WIN32K_
        GreGetTextExtentExW(hdc, str, *len_str, width, NULL, NULL, size, 0) &&
#else
        GetTextExtentExPointW(hdc, str, *len_str, width, NULL, NULL, size) &&
#endif
        size->cx > width)
    {
        for (lo = 0, hi = *len_str; lo < hi; )
        {
            mid = (lo + hi) / 2;
#ifdef _WIN32K_
            if (!GreGetTextExtentExW(hdc, str, mid, width, NULL, NULL, size, 0))
#else
            if (!GetTextExtentExPointW(hdc, str, mid, width, NULL, NULL, size))
#endif
                break;
            if (size->cx > width)
                hi = mid;
            else
                lo = mid + 1;
        }
        *len_str = hi;
    }
    /* Now this should take only a couple iterations at most. */
    for ( ; ; )
    {
        memcpy(str + *len_str, ELLIPSISW, len_ellipsis*sizeof(WCHAR));
#ifdef _WIN32K_
        if (!GreGetTextExtentExW (hdc, str, *len_str + len_ellipsis, width,
                                    NULL, NULL, size, 0)) break;
#else
        if (!GetTextExtentExPointW (hdc, str, *len_str + len_ellipsis, width,
                                    NULL, NULL, size)) break;
#endif
        if (!*len_str || size->cx <= width) break;

        (*len_str)--;
    }
    *len_ellip = len_ellipsis;
    *len_before = *len_str;
    *len_str += len_ellipsis;

    if (modstr)
    {
        memcpy (modstr, str, *len_str * sizeof(WCHAR));
        modstr[*len_str] = '\0';
    }
}