#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ft ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {TYPE_1__* rgBlob; } ;
struct TYPE_10__ {int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  lpszLocalFileName; } ;
struct TYPE_9__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_2__ INTERNET_CACHE_ENTRY_INFOW ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int DWORD ;
typedef  TYPE_3__ CRYPT_BLOB_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_ENTRY_EXPTIME_FC ; 
 int CRYPT_STICKY_CACHE_RETRIEVAL ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CommitUrlCacheEntryW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CompareFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateUrlCacheEntryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteUrlCacheEntryW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 
 scalar_t__ GetUrlCacheEntryInfoW (int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int NORMAL_CACHE_ENTRY ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int STICKY_CACHE_ENTRY ; 
 int /*<<< orphan*/  SetUrlCacheEntryInfoW (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CRYPT_CacheURL(LPCWSTR pszURL, const CRYPT_BLOB_ARRAY *pObject,
 DWORD dwRetrievalFlags, FILETIME expires)
{
    WCHAR cacheFileName[MAX_PATH];
    HANDLE hCacheFile;
    DWORD size = 0, entryType;
    FILETIME ft;

    GetUrlCacheEntryInfoW(pszURL, NULL, &size);
    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        INTERNET_CACHE_ENTRY_INFOW *info = CryptMemAlloc(size);

        if (!info)
        {
            ERR("out of memory\n");
            return;
        }

        if (GetUrlCacheEntryInfoW(pszURL, info, &size))
        {
            lstrcpyW(cacheFileName, info->lpszLocalFileName);
            /* Check if the existing cache entry is up to date.  If it isn't,
             * remove the existing cache entry, and create a new one with the
             * new value.
             */
            GetSystemTimeAsFileTime(&ft);
            if (CompareFileTime(&info->ExpireTime, &ft) < 0)
            {
                DeleteUrlCacheEntryW(pszURL);
            }
            else
            {
                info->ExpireTime = expires;
                SetUrlCacheEntryInfoW(pszURL, info, CACHE_ENTRY_EXPTIME_FC);
                CryptMemFree(info);
                return;
            }
        }
        CryptMemFree(info);
    }

    if (!CreateUrlCacheEntryW(pszURL, pObject->rgBlob[0].cbData, NULL, cacheFileName, 0))
        return;

    hCacheFile = CreateFileW(cacheFileName, GENERIC_WRITE, 0,
            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hCacheFile == INVALID_HANDLE_VALUE)
        return;

    WriteFile(hCacheFile, pObject->rgBlob[0].pbData,
            pObject->rgBlob[0].cbData, &size, NULL);
    CloseHandle(hCacheFile);

    if (!(dwRetrievalFlags & CRYPT_STICKY_CACHE_RETRIEVAL))
        entryType = NORMAL_CACHE_ENTRY;
    else
        entryType = STICKY_CACHE_ENTRY;
    memset(&ft, 0, sizeof(ft));
    CommitUrlCacheEntryW(pszURL, cacheFileName, expires, ft, entryType,
            NULL, 0, NULL, NULL);
}