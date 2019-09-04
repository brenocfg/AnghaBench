#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
struct TYPE_26__ {int dwFlags; int /*<<< orphan*/  children; int /*<<< orphan*/  decoding; } ;
struct TYPE_23__ {scalar_t__ hostPort; TYPE_8__ hdr; int /*<<< orphan*/  hostName; int /*<<< orphan*/  receive_timeout; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; TYPE_6__* appInfo; } ;
typedef  TYPE_4__ http_session_t ;
struct TYPE_27__ {int /*<<< orphan*/  hInternet; int /*<<< orphan*/  entry; int /*<<< orphan*/  decoding; void* dwContext; scalar_t__ dwFlags; int /*<<< orphan*/  htype; } ;
struct TYPE_19__ {TYPE_3__* DebugInfo; } ;
struct TYPE_20__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_21__ {TYPE_1__ data_stream; } ;
struct TYPE_24__ {unsigned int contentLength; char* path; TYPE_9__ hdr; void* version; void* verb; int /*<<< orphan*/  security_flags; int /*<<< orphan*/  server; TYPE_4__* session; TYPE_11__ read_section; TYPE_11__ headers_section; int /*<<< orphan*/  receive_timeout; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; TYPE_2__ netconn_stream; TYPE_1__* data_stream; } ;
typedef  TYPE_5__ http_request_t ;
struct TYPE_25__ {scalar_t__* proxy; } ;
typedef  TYPE_6__ appinfo_t ;
typedef  char WCHAR ;
struct TYPE_22__ {void** Spare; } ;
typedef  char const* LPCWSTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  void* DWORD_PTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  HTTPREQVtbl ; 
 int /*<<< orphan*/  HTTP_ACCEPT ; 
 int HTTP_ADDHDR_FLAG_ADD ; 
 int HTTP_ADDHDR_FLAG_COALESCE_WITH_COMMA ; 
 int HTTP_ADDHDR_FLAG_REPLACE ; 
 int HTTP_ADDHDR_FLAG_REQ ; 
 int HTTP_ADDREQ_FLAG_ADD ; 
 int /*<<< orphan*/  HTTP_DealWithProxy (TYPE_6__*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  HTTP_ProcessHeader (TYPE_5__*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  HTTP_REFERER ; 
 int /*<<< orphan*/  HTTP_ShouldBypassProxy (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ INTERNET_DEFAULT_HTTPS_PORT ; 
 scalar_t__ INTERNET_DEFAULT_HTTP_PORT ; 
 scalar_t__ INTERNET_FLAG_IGNORE_CERT_CN_INVALID ; 
 scalar_t__ INTERNET_FLAG_IGNORE_CERT_DATE_INVALID ; 
 int INTERNET_FLAG_SECURE ; 
 scalar_t__ INTERNET_INVALID_PORT_NUMBER ; 
 int /*<<< orphan*/  INTERNET_STATUS_HANDLE_CREATED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_8__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_11__*) ; 
 int /*<<< orphan*/  SECURITY_FLAG_IGNORE_CERT_CN_INVALID ; 
 int /*<<< orphan*/  SECURITY_FLAG_IGNORE_CERT_DATE_INVALID ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URL_ESCAPE_SPACES_ONLY ; 
 scalar_t__ UrlCanonicalizeW (char const*,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WH_HHTTPREQ ; 
 int /*<<< orphan*/  WININET_AddRef (TYPE_8__*) ; 
 int /*<<< orphan*/  WININET_Release (TYPE_9__*) ; 
 TYPE_5__* alloc_object (TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 char const* g_szHttp1_1 ; 
 int /*<<< orphan*/  get_server (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 char* heap_alloc (scalar_t__) ; 
 void* heap_strdupW (char const*) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netconn_stream_vtbl ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 
 int /*<<< orphan*/  substrz (int /*<<< orphan*/ ) ; 
 char const* szGET ; 

__attribute__((used)) static DWORD HTTP_HttpOpenRequestW(http_session_t *session,
        LPCWSTR lpszVerb, LPCWSTR lpszObjectName, LPCWSTR lpszVersion,
        LPCWSTR lpszReferrer , LPCWSTR *lpszAcceptTypes,
        DWORD dwFlags, DWORD_PTR dwContext, HINTERNET *ret)
{
    appinfo_t *hIC = session->appInfo;
    http_request_t *request;
    DWORD port, len;

    TRACE("-->\n");

    request = alloc_object(&session->hdr, &HTTPREQVtbl, sizeof(http_request_t));
    if(!request)
        return ERROR_OUTOFMEMORY;

    request->hdr.htype = WH_HHTTPREQ;
    request->hdr.dwFlags = dwFlags;
    request->hdr.dwContext = dwContext;
    request->hdr.decoding = session->hdr.decoding;
    request->contentLength = ~0u;

    request->netconn_stream.data_stream.vtbl = &netconn_stream_vtbl;
    request->data_stream = &request->netconn_stream.data_stream;
    request->connect_timeout = session->connect_timeout;
    request->send_timeout = session->send_timeout;
    request->receive_timeout = session->receive_timeout;

    InitializeCriticalSection( &request->headers_section );
    request->headers_section.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": http_request_t.headers_section");

    InitializeCriticalSection( &request->read_section );
    request->read_section.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": http_request_t.read_section");

    WININET_AddRef( &session->hdr );
    request->session = session;
    list_add_head( &session->hdr.children, &request->hdr.entry );

    port = session->hostPort;
    if (port == INTERNET_INVALID_PORT_NUMBER)
        port = (session->hdr.dwFlags & INTERNET_FLAG_SECURE) ?
                INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT;

    request->server = get_server(substrz(session->hostName), port, (dwFlags & INTERNET_FLAG_SECURE) != 0, TRUE);
    if(!request->server) {
        WININET_Release(&request->hdr);
        return ERROR_OUTOFMEMORY;
    }

    if (dwFlags & INTERNET_FLAG_IGNORE_CERT_CN_INVALID)
        request->security_flags |= SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
    if (dwFlags & INTERNET_FLAG_IGNORE_CERT_DATE_INVALID)
        request->security_flags |= SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;

    if (lpszObjectName && *lpszObjectName) {
        HRESULT rc;
        WCHAR dummy;

        len = 1;
        rc = UrlCanonicalizeW(lpszObjectName, &dummy, &len, URL_ESCAPE_SPACES_ONLY);
        if (rc != E_POINTER)
            len = strlenW(lpszObjectName)+1;
        request->path = heap_alloc(len*sizeof(WCHAR));
        rc = UrlCanonicalizeW(lpszObjectName, request->path, &len,
                   URL_ESCAPE_SPACES_ONLY);
        if (rc != S_OK)
        {
            ERR("Unable to escape string!(%s) (%d)\n",debugstr_w(lpszObjectName),rc);
            strcpyW(request->path,lpszObjectName);
        }
    }else {
        static const WCHAR slashW[] = {'/',0};

        request->path = heap_strdupW(slashW);
    }

    if (lpszReferrer && *lpszReferrer)
        HTTP_ProcessHeader(request, HTTP_REFERER, lpszReferrer, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDHDR_FLAG_REQ);

    if (lpszAcceptTypes)
    {
        int i;
        for (i = 0; lpszAcceptTypes[i]; i++)
        {
            if (!*lpszAcceptTypes[i]) continue;
            HTTP_ProcessHeader(request, HTTP_ACCEPT, lpszAcceptTypes[i],
                               HTTP_ADDHDR_FLAG_COALESCE_WITH_COMMA |
                               HTTP_ADDHDR_FLAG_REQ |
                               (i == 0 ? (HTTP_ADDHDR_FLAG_REPLACE | HTTP_ADDHDR_FLAG_ADD) : 0));
        }
    }

    request->verb = heap_strdupW(lpszVerb && *lpszVerb ? lpszVerb : szGET);
    request->version = heap_strdupW(lpszVersion && *lpszVersion ? lpszVersion : g_szHttp1_1);

    if (hIC->proxy && hIC->proxy[0] && !HTTP_ShouldBypassProxy(hIC, session->hostName))
        HTTP_DealWithProxy( hIC, session, request );

    INTERNET_SendCallback(&session->hdr, dwContext,
                          INTERNET_STATUS_HANDLE_CREATED, &request->hdr.hInternet,
                          sizeof(HINTERNET));

    TRACE("<-- (%p)\n", request);

    *ret = request->hdr.hInternet;
    return ERROR_SUCCESS;
}