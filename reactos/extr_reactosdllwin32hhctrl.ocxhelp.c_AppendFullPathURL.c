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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetFullPathNameW (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ ,char const*,char*,char const*,char*) ; 

__attribute__((used)) static BOOL AppendFullPathURL(LPCWSTR file, LPWSTR buf, LPCWSTR index)
{
    static const WCHAR url_format[] =
        {'m','k',':','@','M','S','I','T','S','t','o','r','e',':','%','s',':',':','%','s','%','s',0};
    static const WCHAR slash[] = {'/',0};
    static const WCHAR empty[] = {0};
    WCHAR full_path[MAX_PATH];

    TRACE("%s %p %s\n", debugstr_w(file), buf, debugstr_w(index));

    if (!GetFullPathNameW(file, ARRAY_SIZE(full_path), full_path, NULL)) {
        WARN("GetFullPathName failed: %u\n", GetLastError());
        return FALSE;
    }

    wsprintfW(buf, url_format, full_path, (!index || index[0] == '/') ? empty : slash, index);
    return TRUE;
}