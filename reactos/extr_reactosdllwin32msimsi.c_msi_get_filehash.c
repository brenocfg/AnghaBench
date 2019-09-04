#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  digest; } ;
struct TYPE_7__ {int /*<<< orphan*/  dwData; } ;
typedef  TYPE_1__ MSIFILEHASHINFO ;
typedef  TYPE_2__ MD5_CTX ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MD5Final (TYPE_2__*) ; 
 int /*<<< orphan*/  MD5Init (TYPE_2__*) ; 
 int /*<<< orphan*/  MD5Update (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 void* MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  UnmapViewOfFile (void*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

UINT msi_get_filehash( const WCHAR *path, MSIFILEHASHINFO *hash )
{
    HANDLE handle, mapping;
    void *p;
    DWORD length;
    UINT r = ERROR_FUNCTION_FAILED;

    handle = CreateFileW( path, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, NULL );
    if (handle == INVALID_HANDLE_VALUE)
    {
        WARN("can't open file %u\n", GetLastError());
        return ERROR_FILE_NOT_FOUND;
    }
    if ((length = GetFileSize( handle, NULL )))
    {
        if ((mapping = CreateFileMappingW( handle, NULL, PAGE_READONLY, 0, 0, NULL )))
        {
            if ((p = MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, length )))
            {
                MD5_CTX ctx;

                MD5Init( &ctx );
                MD5Update( &ctx, p, length );
                MD5Final( &ctx );
                UnmapViewOfFile( p );

                memcpy( hash->dwData, ctx.digest, sizeof(hash->dwData) );
                r = ERROR_SUCCESS;
            }
            CloseHandle( mapping );
        }
    }
    else
    {
        /* Empty file -> set hash to 0 */
        memset( hash->dwData, 0, sizeof(hash->dwData) );
        r = ERROR_SUCCESS;
    }

    CloseHandle( handle );
    return r;
}