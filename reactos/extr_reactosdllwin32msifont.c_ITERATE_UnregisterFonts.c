#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {scalar_t__ Action; int /*<<< orphan*/  Component; } ;
struct TYPE_17__ {int /*<<< orphan*/  TargetPath; TYPE_1__* Component; } ;
struct TYPE_16__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_15__ {int /*<<< orphan*/  Component; } ;
typedef  TYPE_2__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_3__ MSIFILE ;
typedef  TYPE_4__ MSICOMPONENT ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 scalar_t__ INSTALLSTATE_ABSENT ; 
 TYPE_2__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_2__*,int) ; 
 scalar_t__ MSI_RecordIsNull (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ font_name_from_file (int /*<<< orphan*/ ) ; 
 scalar_t__ msi_dup_record_field (TYPE_2__*,int) ; 
 int /*<<< orphan*/  msi_free (scalar_t__) ; 
 scalar_t__ msi_get_component_action (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* msi_get_loaded_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* msi_get_loaded_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regfont1 ; 
 int /*<<< orphan*/  regfont2 ; 
 scalar_t__ strdupW (int /*<<< orphan*/ ) ; 
 scalar_t__ strrchrW (scalar_t__,char) ; 

__attribute__((used)) static UINT ITERATE_UnregisterFonts( MSIRECORD *row, LPVOID param )
{
    MSIPACKAGE *package = param;
    LPWSTR name;
    LPCWSTR filename;
    MSIFILE *file;
    MSICOMPONENT *comp;
    HKEY hkey1, hkey2;
    MSIRECORD *uirow;
    LPWSTR uipath, p;

    filename = MSI_RecordGetString( row, 1 );
    file = msi_get_loaded_file( package, filename );
    if (!file)
    {
        WARN("unable to find file %s\n", debugstr_w(filename));
        return ERROR_SUCCESS;
    }
    comp = msi_get_loaded_component( package, file->Component->Component );
    if (!comp)
    {
        WARN("unable to find component %s\n", debugstr_w(file->Component->Component));
        return ERROR_SUCCESS;
    }
    comp->Action = msi_get_component_action( package, comp );
    if (comp->Action != INSTALLSTATE_ABSENT)
    {
        TRACE("component not scheduled for removal %s\n", debugstr_w(comp->Component));
        return ERROR_SUCCESS;
    }

    RegCreateKeyW( HKEY_LOCAL_MACHINE, regfont1, &hkey1 );
    RegCreateKeyW( HKEY_LOCAL_MACHINE, regfont2, &hkey2 );

    if (MSI_RecordIsNull( row, 2 ))
        name = font_name_from_file( file->TargetPath );
    else
        name = msi_dup_record_field( row, 2 );

    if (name)
    {
        RegDeleteValueW( hkey1, name );
        RegDeleteValueW( hkey2, name );
    }

    msi_free( name );
    RegCloseKey( hkey1 );
    RegCloseKey( hkey2 );

    /* the UI chunk */
    uirow = MSI_CreateRecord( 1 );
    uipath = strdupW( file->TargetPath );
    p = strrchrW( uipath,'\\' );
    if (p) p++;
    else p = uipath;
    MSI_RecordSetStringW( uirow, 1, p );
    MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
    msiobj_release( &uirow->hdr );
    msi_free( uipath );
    /* FIXME: call msi_ui_progress? */

    return ERROR_SUCCESS;
}