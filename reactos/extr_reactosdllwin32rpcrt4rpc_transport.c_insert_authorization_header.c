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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  HINTERNET ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HTTP_ADDREQ_FLAG_ADD ; 
 int HTTP_ADDREQ_FLAG_REPLACE ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ HttpAddRequestHeadersW (int /*<<< orphan*/ ,char*,int,int) ; 
#define  RPC_C_HTTP_AUTHN_SCHEME_BASIC 130 
#define  RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE 129 
#define  RPC_C_HTTP_AUTHN_SCHEME_NTLM 128 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_SERVER_UNAVAILABLE ; 
 int encode_base64 (char*,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static RPC_STATUS insert_authorization_header(HINTERNET request, ULONG scheme, char *data, int data_len)
{
    static const WCHAR authW[] = {'A','u','t','h','o','r','i','z','a','t','i','o','n',':',' '};
    static const WCHAR basicW[] = {'B','a','s','i','c',' '};
    static const WCHAR negotiateW[] = {'N','e','g','o','t','i','a','t','e',' '};
    static const WCHAR ntlmW[] = {'N','T','L','M',' '};
    int scheme_len, auth_len = ARRAY_SIZE(authW), len = ((data_len + 2) * 4) / 3;
    const WCHAR *scheme_str;
    WCHAR *header, *ptr;
    RPC_STATUS status = RPC_S_SERVER_UNAVAILABLE;

    switch (scheme)
    {
    case RPC_C_HTTP_AUTHN_SCHEME_BASIC:
        scheme_str = basicW;
        scheme_len = ARRAY_SIZE(basicW);
        break;
    case RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE:
        scheme_str = negotiateW;
        scheme_len = ARRAY_SIZE(negotiateW);
        break;
    case RPC_C_HTTP_AUTHN_SCHEME_NTLM:
        scheme_str = ntlmW;
        scheme_len = ARRAY_SIZE(ntlmW);
        break;
    default:
        ERR("unknown scheme %u\n", scheme);
        return RPC_S_SERVER_UNAVAILABLE;
    }
    if ((header = HeapAlloc(GetProcessHeap(), 0, (auth_len + scheme_len + len + 2) * sizeof(WCHAR))))
    {
        memcpy(header, authW, auth_len * sizeof(WCHAR));
        ptr = header + auth_len;
        memcpy(ptr, scheme_str, scheme_len * sizeof(WCHAR));
        ptr += scheme_len;
        len = encode_base64(data, data_len, ptr);
        ptr[len++] = '\r';
        ptr[len++] = '\n';
        ptr[len] = 0;
        if (HttpAddRequestHeadersW(request, header, -1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE))
            status = RPC_S_OK;
        HeapFree(GetProcessHeap(), 0, header);
    }
    return status;
}