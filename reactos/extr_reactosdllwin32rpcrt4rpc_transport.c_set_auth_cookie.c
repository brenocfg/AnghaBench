#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uc ;
typedef  char WCHAR ;
struct TYPE_6__ {int dwStructSize; char* lpszScheme; scalar_t__ dwExtraInfoLength; int /*<<< orphan*/ * lpszExtraInfo; scalar_t__ dwUrlPathLength; int /*<<< orphan*/ * lpszUrlPath; scalar_t__ dwPasswordLength; int /*<<< orphan*/ * lpszPassword; scalar_t__ dwUserNameLength; int /*<<< orphan*/ * lpszUserName; scalar_t__ nPort; scalar_t__ dwHostNameLength; int /*<<< orphan*/  lpszHostName; scalar_t__ dwSchemeLength; } ;
typedef  TYPE_1__ URL_COMPONENTSW ;
struct TYPE_7__ {int /*<<< orphan*/  servername; } ;
typedef  TYPE_2__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InternetCreateUrlW (TYPE_1__*,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  InternetSetCookieW (char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  RPC_S_SERVER_UNAVAILABLE ; 
 scalar_t__ is_secure (TYPE_2__*) ; 

__attribute__((used)) static RPC_STATUS set_auth_cookie(RpcConnection_http *httpc, const WCHAR *value)
{
    static WCHAR httpW[] = {'h','t','t','p',0};
    static WCHAR httpsW[] = {'h','t','t','p','s',0};
    URL_COMPONENTSW uc;
    DWORD len;
    WCHAR *url;
    BOOL ret;

    if (!value) return RPC_S_OK;

    uc.dwStructSize     = sizeof(uc);
    uc.lpszScheme       = is_secure(httpc) ? httpsW : httpW;
    uc.dwSchemeLength   = 0;
    uc.lpszHostName     = httpc->servername;
    uc.dwHostNameLength = 0;
    uc.nPort            = 0;
    uc.lpszUserName     = NULL;
    uc.dwUserNameLength = 0;
    uc.lpszPassword     = NULL;
    uc.dwPasswordLength = 0;
    uc.lpszUrlPath      = NULL;
    uc.dwUrlPathLength  = 0;
    uc.lpszExtraInfo    = NULL;
    uc.dwExtraInfoLength = 0;

    if (!InternetCreateUrlW(&uc, 0, NULL, &len) && (GetLastError() != ERROR_INSUFFICIENT_BUFFER))
        return RPC_S_SERVER_UNAVAILABLE;

    if (!(url = HeapAlloc(GetProcessHeap(), 0, len))) return RPC_S_OUT_OF_MEMORY;

    len = len / sizeof(WCHAR) - 1;
    if (!InternetCreateUrlW(&uc, 0, url, &len))
    {
        HeapFree(GetProcessHeap(), 0, url);
        return RPC_S_SERVER_UNAVAILABLE;
    }

    ret = InternetSetCookieW(url, NULL, value);
    HeapFree(GetProcessHeap(), 0, url);
    if (!ret) return RPC_S_SERVER_UNAVAILABLE;

    return RPC_S_OK;
}