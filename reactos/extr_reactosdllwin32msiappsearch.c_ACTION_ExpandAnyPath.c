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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;

/* Variables and functions */
 int /*<<< orphan*/  deformat_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 size_t lstrlenW (char*) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 char* strchrW (char*,char) ; 
 size_t strlenW (char*) ; 

__attribute__((used)) static void ACTION_ExpandAnyPath(MSIPACKAGE *package, WCHAR *src, WCHAR *dst,
 size_t len)
{
    WCHAR *ptr, *deformatted;

    if (!src || !dst || !len)
    {
        if (dst) *dst = '\0';
        return;
    }

    dst[0] = '\0';

    /* Ignore the short portion of the path */
    if ((ptr = strchrW(src, '|')))
        ptr++;
    else
        ptr = src;

    deformat_string(package, ptr, &deformatted);
    if (!deformatted || strlenW(deformatted) > len - 1)
    {
        msi_free(deformatted);
        return;
    }

    lstrcpyW(dst, deformatted);
    dst[lstrlenW(deformatted)] = '\0';
    msi_free(deformatted);
}