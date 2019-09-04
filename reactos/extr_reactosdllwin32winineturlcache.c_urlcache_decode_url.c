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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int dwStructSize; int dwHostNameLength; scalar_t__ nScheme; char const* lpszHostName; } ;
typedef  TYPE_1__ URL_COMPONENTSA ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ERROR_INTERNET_INVALID_URL ; 
 scalar_t__ INTERNET_SCHEME_HTTP ; 
 scalar_t__ INTERNET_SCHEME_HTTPS ; 
 scalar_t__ INTERNET_SCHEME_UNKNOWN ; 
 int IdnToUnicode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InternetCrackUrlA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int urlcache_decode_url(const char *url, WCHAR *decoded_url, int decoded_len)
{
    URL_COMPONENTSA uc;
    DWORD len, part_len;
    WCHAR *host_name;

    memset(&uc, 0, sizeof(uc));
    uc.dwStructSize = sizeof(uc);
    uc.dwHostNameLength = 1;
    if(!InternetCrackUrlA(url, 0, 0, &uc))
        uc.nScheme = INTERNET_SCHEME_UNKNOWN;

    if(uc.nScheme!=INTERNET_SCHEME_HTTP && uc.nScheme!=INTERNET_SCHEME_HTTPS)
        return MultiByteToWideChar(CP_UTF8, 0, url, -1, decoded_url, decoded_len);

    if(!decoded_url)
        decoded_len = 0;

    len = MultiByteToWideChar(CP_UTF8, 0, url, uc.lpszHostName-url, decoded_url, decoded_len);
    if(!len)
        return 0;
    if(decoded_url)
        decoded_len -= len;

    host_name = heap_alloc(uc.dwHostNameLength*sizeof(WCHAR));
    if(!host_name)
        return 0;
    if(!MultiByteToWideChar(CP_UTF8, 0, uc.lpszHostName, uc.dwHostNameLength,
                host_name, uc.dwHostNameLength)) {
        heap_free(host_name);
        return 0;
    }
    part_len = IdnToUnicode(0, host_name, uc.dwHostNameLength,
            decoded_url ? decoded_url+len : NULL, decoded_len);
    heap_free(host_name);
    if(!part_len) {
        SetLastError(ERROR_INTERNET_INVALID_URL);
        return 0;
    }
    len += part_len;
    if(decoded_url)
        decoded_len -= part_len;

    part_len = MultiByteToWideChar(CP_UTF8, 0,
            uc.lpszHostName+uc.dwHostNameLength,
            -1, decoded_url ? decoded_url+len : NULL, decoded_len);
    if(!part_len)
        return 0;
    len += part_len;

    return len;
}