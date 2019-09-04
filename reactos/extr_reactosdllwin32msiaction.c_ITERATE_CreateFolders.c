#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {scalar_t__ Action; } ;
struct TYPE_13__ {scalar_t__ State; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_2__ MSIFOLDER ;
typedef  TYPE_3__ MSICOMPONENT ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FOLDER_STATE_CREATED ; 
 scalar_t__ FOLDER_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 scalar_t__ INSTALLSTATE_LOCAL ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_create_full_path (int /*<<< orphan*/ ) ; 
 scalar_t__ msi_get_component_action (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* msi_get_loaded_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* msi_get_loaded_folder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_get_target_folder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT ITERATE_CreateFolders(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE *package = param;
    LPCWSTR dir, component, full_path;
    MSIRECORD *uirow;
    MSIFOLDER *folder;
    MSICOMPONENT *comp;

    component = MSI_RecordGetString(row, 2);
    if (!component)
        return ERROR_SUCCESS;

    comp = msi_get_loaded_component(package, component);
    if (!comp)
        return ERROR_SUCCESS;

    comp->Action = msi_get_component_action( package, comp );
    if (comp->Action != INSTALLSTATE_LOCAL)
    {
        TRACE("component not scheduled for installation: %s\n", debugstr_w(component));
        return ERROR_SUCCESS;
    }

    dir = MSI_RecordGetString(row,1);
    if (!dir)
    {
        ERR("Unable to get folder id\n");
        return ERROR_SUCCESS;
    }

    uirow = MSI_CreateRecord(1);
    MSI_RecordSetStringW(uirow, 1, dir);
    MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
    msiobj_release(&uirow->hdr);

    full_path = msi_get_target_folder( package, dir );
    if (!full_path)
    {
        ERR("Unable to retrieve folder %s\n", debugstr_w(dir));
        return ERROR_SUCCESS;
    }
    TRACE("folder is %s\n", debugstr_w(full_path));

    folder = msi_get_loaded_folder( package, dir );
    if (folder->State == FOLDER_STATE_UNINITIALIZED) msi_create_full_path( full_path );
    folder->State = FOLDER_STATE_CREATED;
    return ERROR_SUCCESS;
}