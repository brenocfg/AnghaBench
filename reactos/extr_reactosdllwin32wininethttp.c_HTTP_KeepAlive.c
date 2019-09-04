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
typedef  int /*<<< orphan*/  szVersion ;
typedef  int /*<<< orphan*/  szConnectionResponse ;
typedef  int /*<<< orphan*/  http_request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ HTTP_HttpQueryInfoW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTTP_QUERY_CONNECTION ; 
 int /*<<< orphan*/  HTTP_QUERY_PROXY_CONNECTION ; 
 int /*<<< orphan*/  HTTP_QUERY_VERSION ; 
 int TRUE ; 
 int /*<<< orphan*/  g_szHttp1_1 ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szKeepAlive ; 

__attribute__((used)) static BOOL HTTP_KeepAlive(http_request_t *request)
{
    WCHAR szVersion[10];
    WCHAR szConnectionResponse[20];
    DWORD dwBufferSize = sizeof(szVersion);
    BOOL keepalive = FALSE;

    /* as per RFC 2068, S8.1.2.1, if the client is HTTP/1.1 then assume that
     * the connection is keep-alive by default */
    if (HTTP_HttpQueryInfoW(request, HTTP_QUERY_VERSION, szVersion, &dwBufferSize, NULL) == ERROR_SUCCESS
        && !strcmpiW(szVersion, g_szHttp1_1))
    {
        keepalive = TRUE;
    }

    dwBufferSize = sizeof(szConnectionResponse);
    if (HTTP_HttpQueryInfoW(request, HTTP_QUERY_PROXY_CONNECTION, szConnectionResponse, &dwBufferSize, NULL) == ERROR_SUCCESS
        || HTTP_HttpQueryInfoW(request, HTTP_QUERY_CONNECTION, szConnectionResponse, &dwBufferSize, NULL) == ERROR_SUCCESS)
    {
        keepalive = !strcmpiW(szConnectionResponse, szKeepAlive);
    }

    return keepalive;
}