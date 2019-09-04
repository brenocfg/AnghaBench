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
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_FLAG_RANDOM_ACCESS ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 void* MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 

__attribute__((used)) static void *map_fileW( LPCWSTR name, LPDWORD filesize )
{
    HANDLE hFile, hMapping;
    LPVOID ptr = NULL;

    hFile = CreateFileW( name, GENERIC_READ, FILE_SHARE_READ, NULL,
                         OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0 );
    if (hFile != INVALID_HANDLE_VALUE)
    {
        hMapping = CreateFileMappingW( hFile, NULL, PAGE_READONLY, 0, 0, NULL );
        if (hMapping)
        {
            ptr = MapViewOfFile( hMapping, FILE_MAP_READ, 0, 0, 0 );
            CloseHandle( hMapping );
            if (filesize)
                *filesize = GetFileSize( hFile, NULL );
        }
        CloseHandle( hFile );
    }
    return ptr;
}