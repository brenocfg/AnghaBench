#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ status_code; void* statusText; void* version; int /*<<< orphan*/  receive_timeout; int /*<<< orphan*/  netconn; } ;
typedef  TYPE_1__ http_request_t ;
typedef  char WCHAR ;
typedef  char* LPWSTR ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int ERROR_HTTP_INVALID_SERVER_RESPONSE ; 
 int ERROR_SUCCESS ; 
 int FALSE ; 
 int HTTP_ADDHDR_FLAG_ADD ; 
 int HTTP_ADDHDR_FLAG_REPLACE ; 
 int HTTP_ADDREQ_FLAG_ADD ; 
 int /*<<< orphan*/  HTTP_FreeTokens (char**) ; 
 char** HTTP_InterpretHttpHeader (char*) ; 
 int /*<<< orphan*/  HTTP_ProcessHeader (TYPE_1__*,char*,char*,int) ; 
 scalar_t__ HTTP_STATUS_CONTINUE ; 
 scalar_t__ HTTP_STATUS_OK ; 
 int /*<<< orphan*/  HTTP_clear_response_headers (TYPE_1__*) ; 
 int MAX_REPLY_LEN ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  NETCON_set_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ atoiW (char*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* emptyW ; 
 char* g_szHttp1_0 ; 
 int /*<<< orphan*/  heap_free (void*) ; 
 void* heap_strdupW (char*) ; 
 int /*<<< orphan*/  is_valid_netconn (int /*<<< orphan*/ ) ; 
 int read_line (TYPE_1__*,char*,int*) ; 
 char* strchrW (char*,char) ; 
 int /*<<< orphan*/  strncmpW (char*,char*,int) ; 
 char* szOK ; 
 char* szStatus ; 

__attribute__((used)) static DWORD HTTP_GetResponseHeaders(http_request_t *request, INT *len)
{
    INT cbreaks = 0;
    WCHAR buffer[MAX_REPLY_LEN];
    DWORD buflen = MAX_REPLY_LEN;
    INT  rc = 0;
    char bufferA[MAX_REPLY_LEN];
    LPWSTR status_code = NULL, status_text = NULL;
    DWORD res = ERROR_HTTP_INVALID_SERVER_RESPONSE;
    BOOL codeHundred = FALSE;

    TRACE("-->\n");

    if(!is_valid_netconn(request->netconn))
        goto lend;

    /* clear old response headers (eg. from a redirect response) */
    HTTP_clear_response_headers( request );

    NETCON_set_timeout( request->netconn, FALSE, request->receive_timeout );
    do {
        /*
         * We should first receive 'HTTP/1.x nnn OK' where nnn is the status code.
         */
        buflen = MAX_REPLY_LEN;
        if ((res = read_line(request, bufferA, &buflen)))
            goto lend;

        if (!buflen) goto lend;

        rc += buflen;
        MultiByteToWideChar( CP_ACP, 0, bufferA, buflen, buffer, MAX_REPLY_LEN );
        /* check is this a status code line? */
        if (!strncmpW(buffer, g_szHttp1_0, 4))
        {
            /* split the version from the status code */
            status_code = strchrW( buffer, ' ' );
            if( !status_code )
                goto lend;
            *status_code++=0;

            /* split the status code from the status text */
            status_text = strchrW( status_code, ' ' );
            if( status_text )
                *status_text++=0;

            request->status_code = atoiW(status_code);

            TRACE("version [%s] status code [%s] status text [%s]\n",
               debugstr_w(buffer), debugstr_w(status_code), debugstr_w(status_text) );

            codeHundred = request->status_code == HTTP_STATUS_CONTINUE;
        }
        else if (!codeHundred)
        {
            WARN("No status line at head of response (%s)\n", debugstr_w(buffer));

            heap_free(request->version);
            heap_free(request->statusText);

            request->status_code = HTTP_STATUS_OK;
            request->version = heap_strdupW(g_szHttp1_0);
            request->statusText = heap_strdupW(szOK);

            goto lend;
        }
    } while (codeHundred);

    /* Add status code */
    HTTP_ProcessHeader(request, szStatus, status_code,
                       HTTP_ADDHDR_FLAG_REPLACE | HTTP_ADDHDR_FLAG_ADD);

    heap_free(request->version);
    heap_free(request->statusText);

    request->version = heap_strdupW(buffer);
    request->statusText = heap_strdupW(status_text ? status_text : emptyW);

    /* Restore the spaces */
    *(status_code-1) = ' ';
    if (status_text)
        *(status_text-1) = ' ';

    /* Parse each response line */
    do
    {
        buflen = MAX_REPLY_LEN;
        if (!read_line(request, bufferA, &buflen) && buflen)
        {
            LPWSTR * pFieldAndValue;

            TRACE("got line %s, now interpreting\n", debugstr_a(bufferA));

            if (!bufferA[0]) break;
            MultiByteToWideChar( CP_ACP, 0, bufferA, buflen, buffer, MAX_REPLY_LEN );

            pFieldAndValue = HTTP_InterpretHttpHeader(buffer);
            if (pFieldAndValue)
            {
                HTTP_ProcessHeader(request, pFieldAndValue[0], pFieldAndValue[1],
                                   HTTP_ADDREQ_FLAG_ADD );
                HTTP_FreeTokens(pFieldAndValue);
            }
        }
        else
        {
            cbreaks++;
            if (cbreaks >= 2)
                break;
        }
    }while(1);

    res = ERROR_SUCCESS;

lend:

    *len = rc;
    TRACE("<--\n");
    return res;
}