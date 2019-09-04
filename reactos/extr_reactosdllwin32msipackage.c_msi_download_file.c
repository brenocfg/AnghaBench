#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  lpszLocalFileName; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_1__* LPINTERNET_CACHE_ENTRY_INFOW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetUrlCacheEntryInfoW (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  URLDownloadToCacheFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

UINT msi_download_file( LPCWSTR szUrl, LPWSTR filename )
{
    LPINTERNET_CACHE_ENTRY_INFOW cache_entry;
    DWORD size = 0;
    HRESULT hr;

    /* call will always fail, because size is 0,
     * but will return ERROR_FILE_NOT_FOUND first
     * if the file doesn't exist
     */
    GetUrlCacheEntryInfoW( szUrl, NULL, &size );
    if ( GetLastError() != ERROR_FILE_NOT_FOUND )
    {
        cache_entry = msi_alloc( size );
        if ( !GetUrlCacheEntryInfoW( szUrl, cache_entry, &size ) )
        {
            UINT error = GetLastError();
            msi_free( cache_entry );
            return error;
        }

        lstrcpyW( filename, cache_entry->lpszLocalFileName );
        msi_free( cache_entry );
        return ERROR_SUCCESS;
    }

    hr = URLDownloadToCacheFileW( NULL, szUrl, filename, MAX_PATH, 0, NULL );
    if ( FAILED(hr) )
    {
        WARN("failed to download %s to cache file\n", debugstr_w(szUrl));
        return ERROR_FUNCTION_FAILED;
    }

    return ERROR_SUCCESS;
}