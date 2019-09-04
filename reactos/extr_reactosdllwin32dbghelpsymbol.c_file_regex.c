#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static WCHAR* file_regex(const char* srcfile)
{
    WCHAR* mask;
    WCHAR* p;

    if (!srcfile || !*srcfile)
    {
        if (!(p = mask = HeapAlloc(GetProcessHeap(), 0, 3 * sizeof(WCHAR)))) return NULL;
        *p++ = '?';
        *p++ = '#';
    }
    else
    {
        DWORD  sz = MultiByteToWideChar(CP_ACP, 0, srcfile, -1, NULL, 0);
        WCHAR* srcfileW;

        /* FIXME: we use here the largest conversion for every char... could be optimized */
        p = mask = HeapAlloc(GetProcessHeap(), 0, (5 * strlen(srcfile) + 1 + sz) * sizeof(WCHAR));
        if (!mask) return NULL;
        srcfileW = mask + 5 * strlen(srcfile) + 1;
        MultiByteToWideChar(CP_ACP, 0, srcfile, -1, srcfileW, sz);

        while (*srcfileW)
        {
            switch (*srcfileW)
            {
            case '\\':
            case '/':
                *p++ = '[';
                *p++ = '\\';
                *p++ = '\\';
                *p++ = '/';
                *p++ = ']';
                break;
            case '.':
                *p++ = '?';
                break;
            default:
                *p++ = *srcfileW;
                break;
            }
            srcfileW++;
        }
    }
    *p = 0;
    return mask;
}