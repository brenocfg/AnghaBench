#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nCustHeaders; char* version; char* statusText; int /*<<< orphan*/  headers_section; TYPE_1__* custHeaders; int /*<<< orphan*/  status_code; } ;
typedef  TYPE_2__ http_request_t ;
typedef  char WCHAR ;
struct TYPE_4__ {int wFlags; char* lpszField; char* lpszValue; } ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int HDR_ISREQUEST ; 
 char* HTTP_build_req (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char** heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char const**) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmpW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szStatus ; 

__attribute__((used)) static WCHAR* build_response_header(http_request_t *request, BOOL use_cr)
{
    static const WCHAR colonW[] = { ':',' ',0 };
    static const WCHAR crW[] = { '\r',0 };
    static const WCHAR lfW[] = { '\n',0 };
    static const WCHAR status_fmt[] = { ' ','%','u',' ',0 };
    const WCHAR **req;
    WCHAR *ret, buf[14];
    DWORD i, n = 0;

    EnterCriticalSection( &request->headers_section );

    if (!(req = heap_alloc( (request->nCustHeaders * 5 + 8) * sizeof(WCHAR *) )))
    {
        LeaveCriticalSection( &request->headers_section );
        return NULL;
    }

    if (request->status_code)
    {
        req[n++] = request->version;
        sprintfW(buf, status_fmt, request->status_code);
        req[n++] = buf;
        req[n++] = request->statusText;
        if (use_cr)
            req[n++] = crW;
        req[n++] = lfW;
    }

    for(i = 0; i < request->nCustHeaders; i++)
    {
        if(!(request->custHeaders[i].wFlags & HDR_ISREQUEST)
                && strcmpW(request->custHeaders[i].lpszField, szStatus))
        {
            req[n++] = request->custHeaders[i].lpszField;
            req[n++] = colonW;
            req[n++] = request->custHeaders[i].lpszValue;
            if(use_cr)
                req[n++] = crW;
            req[n++] = lfW;

            TRACE("Adding custom header %s (%s)\n",
                    debugstr_w(request->custHeaders[i].lpszField),
                    debugstr_w(request->custHeaders[i].lpszValue));
        }
    }
    if(use_cr)
        req[n++] = crW;
    req[n++] = lfW;
    req[n] = NULL;

    ret = HTTP_build_req(req, 0);
    heap_free(req);
    LeaveCriticalSection( &request->headers_section );
    return ret;
}