#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uc ;
struct AUTO_PROXY_SCRIPT_BUFFER {int dwStructSize; char* lpszScriptBuffer; int /*<<< orphan*/  dwScriptBufferSize; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WINHTTP_PROXY_INFO ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int dwStructSize; int dwHostNameLength; int /*<<< orphan*/  lpszHostName; } ;
typedef  TYPE_1__ URL_COMPONENTSW ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InternetDeInitializeAutoProxyDll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetGetProxyInfo (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetInitializeAutoProxyDll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct AUTO_PROXY_SCRIPT_BUFFER*) ; 
 scalar_t__ WinHttpCrackUrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_script_result (char*,int /*<<< orphan*/ *) ; 
 char* strdupWA (int /*<<< orphan*/  const*) ; 
 char* strdupWA_sized (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static BOOL run_script( char *script, DWORD size, const WCHAR *url, WINHTTP_PROXY_INFO *info )
{
    BOOL ret;
    char *result, *urlA;
    DWORD len_result;
    struct AUTO_PROXY_SCRIPT_BUFFER buffer;
    URL_COMPONENTSW uc;

    buffer.dwStructSize = sizeof(buffer);
    buffer.lpszScriptBuffer = script;
    buffer.dwScriptBufferSize = size;

    if (!(urlA = strdupWA( url ))) return FALSE;
    if (!(ret = InternetInitializeAutoProxyDll( 0, NULL, NULL, NULL, &buffer )))
    {
        heap_free( urlA );
        return FALSE;
    }

    memset( &uc, 0, sizeof(uc) );
    uc.dwStructSize = sizeof(uc);
    uc.dwHostNameLength = -1;

    if (WinHttpCrackUrl( url, 0, 0, &uc ))
    {
        char *hostnameA = strdupWA_sized( uc.lpszHostName, uc.dwHostNameLength );

        if ((ret = InternetGetProxyInfo( urlA, strlen(urlA),
                        hostnameA, strlen(hostnameA), &result, &len_result )))
        {
            ret = parse_script_result( result, info );
            heap_free( result );
        }

        heap_free( hostnameA );
    }
    heap_free( urlA );
    return InternetDeInitializeAutoProxyDll( NULL, 0 );
}