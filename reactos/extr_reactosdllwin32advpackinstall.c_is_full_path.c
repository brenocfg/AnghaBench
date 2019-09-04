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
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int const lstrlenW (char*) ; 

__attribute__((used)) static BOOL is_full_path(LPCWSTR path)
{
    const int MIN_PATH_LEN = 3;

    if (!path || lstrlenW(path) < MIN_PATH_LEN)
        return FALSE;

    if ((path[1] == ':' && path[2] == '\\') || (path[0] == '\\' && path[1] == '\\'))
        return TRUE;

    return FALSE;
}