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
typedef  int /*<<< orphan*/  nsChannelBSC ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IWinInetHttpInfo ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_QUERY_RAW_HEADERS_CRLF ; 
 int /*<<< orphan*/  IWinInetHttpInfo_QueryInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  process_response_headers (int /*<<< orphan*/ *,char const*) ; 
 char* strchrW (char*,char) ; 

__attribute__((used)) static void query_http_info(nsChannelBSC *This, IWinInetHttpInfo *wininet_info)
{
    const WCHAR *ptr;
    DWORD len = 0;
    WCHAR *buf;

    IWinInetHttpInfo_QueryInfo(wininet_info, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &len, NULL, NULL);
    if(!len)
        return;

    buf = heap_alloc(len);
    if(!buf)
        return;

    IWinInetHttpInfo_QueryInfo(wininet_info, HTTP_QUERY_RAW_HEADERS_CRLF, buf, &len, NULL, NULL);
    if(!len) {
        heap_free(buf);
        return;
    }

    ptr = strchrW(buf, '\r');
    if(ptr && ptr[1] == '\n') {
        ptr += 2;
        process_response_headers(This, ptr);
    }

    heap_free(buf);
}