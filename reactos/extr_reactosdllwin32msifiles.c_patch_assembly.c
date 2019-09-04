#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_9__ {int /*<<< orphan*/  display_name; } ;
struct TYPE_8__ {TYPE_1__* File; } ;
struct TYPE_7__ {int /*<<< orphan*/ * TargetPath; } ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_2__ MSIFILEPATCH ;
typedef  TYPE_3__ MSIASSEMBLY ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int /*<<< orphan*/  IAssemblyEnum ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CopyFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_SUCCESS ; 
 scalar_t__ E_NOT_SUFFICIENT_BUFFER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ IAssemblyEnum_GetNextAssembly (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAssemblyEnum_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAssemblyName_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAssemblyName_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/ * msi_create_assembly_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_get_assembly_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int patch_file (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static UINT patch_assembly( MSIPACKAGE *package, MSIASSEMBLY *assembly, MSIFILEPATCH *patch )
{
    UINT r = ERROR_FUNCTION_FAILED;
    IAssemblyName *name;
    IAssemblyEnum *iter;

    if (!(iter = msi_create_assembly_enum( package, assembly->display_name )))
        return ERROR_FUNCTION_FAILED;

    while ((IAssemblyEnum_GetNextAssembly( iter, NULL, &name, 0 ) == S_OK))
    {
        WCHAR *displayname, *path;
        UINT len = 0;
        HRESULT hr;

        hr = IAssemblyName_GetDisplayName( name, NULL, &len, 0 );
        if (hr != E_NOT_SUFFICIENT_BUFFER || !(displayname = msi_alloc( len * sizeof(WCHAR) )))
            break;

        hr = IAssemblyName_GetDisplayName( name, displayname, &len, 0 );
        if (FAILED( hr ))
        {
            msi_free( displayname );
            break;
        }

        if ((path = msi_get_assembly_path( package, displayname )))
        {
            if (!CopyFileW( path, patch->File->TargetPath, FALSE ))
            {
                ERR("Failed to copy file %s -> %s (%u)\n", debugstr_w(path),
                    debugstr_w(patch->File->TargetPath), GetLastError() );
                msi_free( path );
                msi_free( displayname );
                IAssemblyName_Release( name );
                break;
            }
            r = patch_file( package, patch );
            msi_free( path );
        }

        msi_free( displayname );
        IAssemblyName_Release( name );
        if (r == ERROR_SUCCESS) break;
    }

    IAssemblyEnum_Release( iter );
    return r;
}