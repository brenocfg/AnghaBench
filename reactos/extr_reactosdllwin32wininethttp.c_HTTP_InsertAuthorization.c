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
struct HttpAuthInfo {char const* scheme; char* auth_data; scalar_t__ auth_data_len; } ;
typedef  int /*<<< orphan*/  http_request_t ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HTTP_ADDHDR_FLAG_ADD ; 
 int HTTP_ADDHDR_FLAG_REPLACE ; 
 int HTTP_ADDHDR_FLAG_REQ ; 
 int HTTP_ADDREQ_FLAG_ADD ; 
 int /*<<< orphan*/  HTTP_ProcessHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* encode_auth_data (char const*,char*,scalar_t__) ; 
 char* get_host_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 scalar_t__ retrieve_cached_basic_authorization (char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmpiW (char const*,char const*) ; 
 int /*<<< orphan*/  szAuthorization ; 

__attribute__((used)) static BOOL HTTP_InsertAuthorization( http_request_t *request, struct HttpAuthInfo *pAuthInfo, LPCWSTR header )
{
    static const WCHAR wszBasic[] = {'B','a','s','i','c',0};
    WCHAR *host, *authorization = NULL;

    if (pAuthInfo)
    {
        if (pAuthInfo->auth_data_len)
        {
            if (!(authorization = encode_auth_data(pAuthInfo->scheme, pAuthInfo->auth_data, pAuthInfo->auth_data_len)))
                return FALSE;

            /* clear the data as it isn't valid now that it has been sent to the
             * server, unless it's Basic authentication which doesn't do
             * connection tracking */
            if (strcmpiW(pAuthInfo->scheme, wszBasic))
            {
                heap_free(pAuthInfo->auth_data);
                pAuthInfo->auth_data = NULL;
                pAuthInfo->auth_data_len = 0;
            }
        }

        TRACE("Inserting authorization: %s\n", debugstr_w(authorization));

        HTTP_ProcessHeader(request, header, authorization,
                           HTTP_ADDHDR_FLAG_REQ | HTTP_ADDHDR_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
        heap_free(authorization);
    }
    else if (!strcmpW(header, szAuthorization) && (host = get_host_header(request)))
    {
        UINT data_len;
        char *data;

        if ((data_len = retrieve_cached_basic_authorization(host, NULL, &data)))
        {
            TRACE("Found cached basic authorization for %s\n", debugstr_w(host));

            if (!(authorization = encode_auth_data(wszBasic, data, data_len)))
            {
                heap_free(data);
                heap_free(host);
                return FALSE;
            }

            TRACE("Inserting authorization: %s\n", debugstr_w(authorization));

            HTTP_ProcessHeader(request, header, authorization,
                               HTTP_ADDHDR_FLAG_REQ | HTTP_ADDHDR_FLAG_REPLACE | HTTP_ADDHDR_FLAG_ADD);
            heap_free(data);
            heap_free(authorization);
        }
        heap_free(host);
    }
    return TRUE;
}