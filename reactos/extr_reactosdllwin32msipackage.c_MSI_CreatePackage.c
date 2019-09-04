#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_16__ {int /*<<< orphan*/  path; int /*<<< orphan*/  hdr; } ;
struct TYPE_15__ {int WordCount; int ui_level; int /*<<< orphan*/  log_file; int /*<<< orphan*/  hdr; TYPE_2__* db; int /*<<< orphan*/  ProductCode; void* BaseURL; void* PackagePath; int /*<<< orphan*/  LastActionResult; int /*<<< orphan*/ * LastActionTemplate; int /*<<< orphan*/ * LastAction; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int INSTALLUILEVEL_MASK ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MSI_NULL_INTEGER ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  create_temp_property_table (TYPE_1__*) ; 
 int gUILevel ; 
 int /*<<< orphan*/  msi_adjust_privilege_properties (TYPE_1__*) ; 
 TYPE_1__* msi_alloc_package () ; 
 int /*<<< orphan*/  msi_clone_properties (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_dup_property (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_load_admin_properties (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_load_suminfo_properties (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_set_property (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int msidbSumInfoSourceTypeAdminImage ; 
 int /*<<< orphan*/  msiobj_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_installer_properties (TYPE_1__*) ; 
 int sprintfW (char*,char const*,int) ; 
 void* strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szProductCode ; 
 int /*<<< orphan*/  szUILevel ; 

MSIPACKAGE *MSI_CreatePackage( MSIDATABASE *db, LPCWSTR base_url )
{
    static const WCHAR fmtW[] = {'%','u',0};
    MSIPACKAGE *package;
    WCHAR uilevel[11];
    int len;
    UINT r;

    TRACE("%p\n", db);

    package = msi_alloc_package();
    if (package)
    {
        msiobj_addref( &db->hdr );
        package->db = db;

        package->LastAction = NULL;
        package->LastActionTemplate = NULL;
        package->LastActionResult = MSI_NULL_INTEGER;
        package->WordCount = 0;
        package->PackagePath = strdupW( db->path );
        package->BaseURL = strdupW( base_url );

        create_temp_property_table( package );
        msi_clone_properties( package->db );
        msi_adjust_privilege_properties( package );

        package->ProductCode = msi_dup_property( package->db, szProductCode );

        set_installer_properties( package );

        package->ui_level = gUILevel;
        len = sprintfW( uilevel, fmtW, gUILevel & INSTALLUILEVEL_MASK );
        msi_set_property( package->db, szUILevel, uilevel, len );

        r = msi_load_suminfo_properties( package );
        if (r != ERROR_SUCCESS)
        {
            msiobj_release( &package->hdr );
            return NULL;
        }

        if (package->WordCount & msidbSumInfoSourceTypeAdminImage)
            msi_load_admin_properties( package );

        package->log_file = INVALID_HANDLE_VALUE;
    }
    return package;
}