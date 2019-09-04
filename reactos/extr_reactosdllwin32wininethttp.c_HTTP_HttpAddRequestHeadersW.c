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
typedef  int /*<<< orphan*/  http_request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 unsigned int ERROR_HTTP_INVALID_HEADER ; 
 unsigned int ERROR_SUCCESS ; 
 unsigned int HTTP_ADDHDR_FLAG_REQ ; 
 int /*<<< orphan*/  HTTP_FreeTokens (char**) ; 
 char** HTTP_InterpretHttpHeader (char*) ; 
 unsigned int HTTP_ProcessHeader (int /*<<< orphan*/ *,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/ ,unsigned int) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD HTTP_HttpAddRequestHeadersW(http_request_t *request,
	LPCWSTR lpszHeader, DWORD dwHeaderLength, DWORD dwModifier)
{
    LPWSTR lpszStart;
    LPWSTR lpszEnd;
    LPWSTR buffer;
    DWORD len, res = ERROR_HTTP_INVALID_HEADER;

    TRACE("copying header: %s\n", debugstr_wn(lpszHeader, dwHeaderLength));

    if( dwHeaderLength == ~0U )
        len = strlenW(lpszHeader);
    else
        len = dwHeaderLength;
    buffer = heap_alloc(sizeof(WCHAR)*(len+1));
    lstrcpynW( buffer, lpszHeader, len + 1);

    lpszStart = buffer;

    do
    {
        LPWSTR * pFieldAndValue;

        lpszEnd = lpszStart;

        while (*lpszEnd != '\0')
        {
            if (*lpszEnd == '\r' || *lpszEnd == '\n')
                 break;
            lpszEnd++;
        }

        if (*lpszStart == '\0')
	    break;

        if (*lpszEnd == '\r' || *lpszEnd == '\n')
        {
            *lpszEnd = '\0';
            lpszEnd++; /* Jump over newline */
        }
        TRACE("interpreting header %s\n", debugstr_w(lpszStart));
        if (*lpszStart == '\0')
        {
            /* Skip 0-length headers */
            lpszStart = lpszEnd;
            res = ERROR_SUCCESS;
            continue;
        }
        pFieldAndValue = HTTP_InterpretHttpHeader(lpszStart);
        if (pFieldAndValue)
        {
            res = HTTP_ProcessHeader(request, pFieldAndValue[0],
                pFieldAndValue[1], dwModifier | HTTP_ADDHDR_FLAG_REQ);
            HTTP_FreeTokens(pFieldAndValue);
        }

        lpszStart = lpszEnd;
    } while (res == ERROR_SUCCESS);

    heap_free(buffer);
    return res;
}