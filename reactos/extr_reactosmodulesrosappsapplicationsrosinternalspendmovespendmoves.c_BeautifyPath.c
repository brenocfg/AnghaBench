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
typedef  scalar_t__ TCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ _T (char) ; 

__attribute__((used)) static
TCHAR *
BeautifyPath(TCHAR * Path, DWORD * Len)
{
    DWORD LocalLen = *Len;

    /* If there's a ! marking that existing file can be overwritten,
     * drop it
     */
    if (LocalLen > 1)
    {
        if (Path[0] == _T('!'))
        {
            ++Path;
            --LocalLen;
        }
    }

    /* Remove namespace if prefixed */
    if (LocalLen > 4)
    {
        if (Path[0] == _T('\\') && Path[1] == _T('?') &&
            Path[2] == _T('?') && Path[3] == _T('\\'))
        {
            Path += 4;
            LocalLen -= 4;
        }
    }

    /* Return modified string + len */
    *Len = LocalLen;
    return Path;
}