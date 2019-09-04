#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_14__ {scalar_t__ Action; } ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_2__ MSICOMPONENT ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 scalar_t__ INSTALLSTATE_LOCAL ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordGetInteger (TYPE_1__*,int) ; 
 char* MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  deformat_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  delete_tree (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  delete_value (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* get_root_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 scalar_t__ msi_get_component_action (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* msi_get_loaded_component (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcatW (char*,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static UINT ITERATE_RemoveRegistryValuesOnInstall( MSIRECORD *row, LPVOID param )
{
    MSIPACKAGE *package = param;
    LPCWSTR component, name, key_str, root_key_str;
    LPWSTR deformated_key, deformated_name, ui_key_str;
    MSICOMPONENT *comp;
    MSIRECORD *uirow;
    BOOL delete_key = FALSE;
    HKEY hkey_root;
    UINT size;
    INT root;

    component = MSI_RecordGetString( row, 5 );
    comp = msi_get_loaded_component( package, component );
    if (!comp)
        return ERROR_SUCCESS;

    comp->Action = msi_get_component_action( package, comp );
    if (comp->Action != INSTALLSTATE_LOCAL)
    {
        TRACE("component not scheduled for installation %s\n", debugstr_w(component));
        return ERROR_SUCCESS;
    }

    if ((name = MSI_RecordGetString( row, 4 )))
    {
        if (name[0] == '-' && !name[1])
        {
            delete_key = TRUE;
            name = NULL;
        }
    }

    root = MSI_RecordGetInteger( row, 2 );
    key_str = MSI_RecordGetString( row, 3 );

    root_key_str = get_root_key( package, root, &hkey_root );
    if (!root_key_str)
        return ERROR_SUCCESS;

    deformat_string( package, key_str, &deformated_key );
    size = strlenW( deformated_key ) + strlenW( root_key_str ) + 1;
    ui_key_str = msi_alloc( size * sizeof(WCHAR) );
    strcpyW( ui_key_str, root_key_str );
    strcatW( ui_key_str, deformated_key );

    deformat_string( package, name, &deformated_name );

    if (delete_key) delete_tree( comp, hkey_root, deformated_key );
    else delete_value( comp, hkey_root, deformated_key, deformated_name );
    msi_free( deformated_key );

    uirow = MSI_CreateRecord( 2 );
    MSI_RecordSetStringW( uirow, 1, ui_key_str );
    MSI_RecordSetStringW( uirow, 2, deformated_name );
    MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
    msiobj_release( &uirow->hdr );

    msi_free( ui_key_str );
    msi_free( deformated_name );
    return ERROR_SUCCESS;
}