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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTTP_QUERY_WWW_AUTHENTICATE ; 
 int /*<<< orphan*/  HttpQueryInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ auth_scheme_from_header (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL get_authvalue(HINTERNET request, DWORD scheme, WCHAR *buffer, DWORD buflen)
{
    DWORD len, index = 0;
    for (;;)
    {
        len = buflen;
        if (!HttpQueryInfoW(request, HTTP_QUERY_WWW_AUTHENTICATE, buffer, &len, &index)) return FALSE;
        if (auth_scheme_from_header(buffer) == scheme) break;
    }
    return TRUE;
}