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
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  ENHMETAHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileMappingA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EMF_Create_HENHMETAFILE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/ * MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HENHMETAFILE EMF_GetEnhMetaFile( HANDLE hFile )
{
    ENHMETAHEADER *emh;
    HANDLE hMapping;
    HENHMETAFILE hemf;

    hMapping = CreateFileMappingA( hFile, NULL, PAGE_READONLY, 0, 0, NULL );
    emh = MapViewOfFile( hMapping, FILE_MAP_READ, 0, 0, 0 );
    CloseHandle( hMapping );

    if (!emh) return 0;

    hemf = EMF_Create_HENHMETAFILE( emh, TRUE );
    if (!hemf)
        UnmapViewOfFile( emh );
    return hemf;
}