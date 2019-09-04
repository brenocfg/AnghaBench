#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_22__ {int Attributes; TYPE_1__* assembly; int /*<<< orphan*/  Action; } ;
struct TYPE_21__ {int /*<<< orphan*/  db; } ;
struct TYPE_20__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_19__ {int /*<<< orphan*/  application; } ;
typedef  TYPE_2__ MSIRECORD ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  TYPE_4__ MSICOMPONENT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 TYPE_2__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MSI_RecordGetInteger (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * MSI_RecordGetString (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PathAddBackslashW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveDirectoryW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/ * msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_get_component_action (TYPE_3__*,TYPE_4__*) ; 
 TYPE_4__* msi_get_loaded_component (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_reduce_to_long_filename (int /*<<< orphan*/ *) ; 
 int msidbComponentAttributesPermanent ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_comp_for_removal (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ITERATE_RemoveFiles(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE *package = param;
    MSICOMPONENT *comp;
    MSIRECORD *uirow;
    LPCWSTR component, dirprop;
    UINT install_mode;
    LPWSTR dir = NULL, path = NULL, filename = NULL;
    DWORD size;
    UINT ret = ERROR_SUCCESS;

    component = MSI_RecordGetString(row, 2);
    dirprop = MSI_RecordGetString(row, 4);
    install_mode = MSI_RecordGetInteger(row, 5);

    comp = msi_get_loaded_component(package, component);
    if (!comp)
        return ERROR_SUCCESS;

    comp->Action = msi_get_component_action( package, comp );
    if (!verify_comp_for_removal(comp, install_mode))
    {
        TRACE("Skipping removal due to install mode\n");
        return ERROR_SUCCESS;
    }
    if (comp->assembly && !comp->assembly->application)
    {
        return ERROR_SUCCESS;
    }
    if (comp->Attributes & msidbComponentAttributesPermanent)
    {
        TRACE("permanent component, not removing file\n");
        return ERROR_SUCCESS;
    }

    dir = msi_dup_property(package->db, dirprop);
    if (!dir)
    {
        WARN("directory property has no value\n");
        return ERROR_SUCCESS;
    }
    size = 0;
    if ((filename = strdupW( MSI_RecordGetString(row, 3) )))
    {
        msi_reduce_to_long_filename( filename );
        size = lstrlenW( filename );
    }
    size += lstrlenW(dir) + 2;
    path = msi_alloc(size * sizeof(WCHAR));
    if (!path)
    {
        ret = ERROR_OUTOFMEMORY;
        goto done;
    }

    if (filename)
    {
        lstrcpyW(path, dir);
        PathAddBackslashW(path);
        lstrcatW(path, filename);

        TRACE("Deleting misc file: %s\n", debugstr_w(path));
        DeleteFileW(path);
    }
    else
    {
        TRACE("Removing misc directory: %s\n", debugstr_w(dir));
        RemoveDirectoryW(dir);
    }

done:
    uirow = MSI_CreateRecord( 9 );
    MSI_RecordSetStringW( uirow, 1, MSI_RecordGetString(row, 1) );
    MSI_RecordSetStringW( uirow, 9, dir );
    MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
    msiobj_release( &uirow->hdr );

    msi_free(filename);
    msi_free(path);
    msi_free(dir);
    return ret;
}