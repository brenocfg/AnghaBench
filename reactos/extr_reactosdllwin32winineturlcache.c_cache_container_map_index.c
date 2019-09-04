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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_MAP_WRITE ; 
 int MAX_PATH ; 
 scalar_t__ OpenFileMappingW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cache_container_create_object_name (char*,char) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HANDLE cache_container_map_index(HANDLE file, const WCHAR *path, DWORD size, BOOL *validate)
{
    static const WCHAR mapping_name_format[]
        = {'%','s','i','n','d','e','x','.','d','a','t','_','%','l','u',0};
    WCHAR mapping_name[MAX_PATH];
    HANDLE mapping;

    wsprintfW(mapping_name, mapping_name_format, path, size);
    cache_container_create_object_name(mapping_name, '_');

    mapping = OpenFileMappingW(FILE_MAP_WRITE, FALSE, mapping_name);
    if(mapping) {
        if(validate) *validate = FALSE;
        return mapping;
    }

    if(validate) *validate = TRUE;
    return CreateFileMappingW(file, NULL, PAGE_READWRITE, 0, 0, mapping_name);
}