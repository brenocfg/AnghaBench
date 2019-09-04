#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIDATABASE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INSTALL_PACKAGE_INVALID ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/  const*) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  MSIDBOPEN_READONLY ; 
 int /*<<< orphan*/  MSI_OpenDatabaseW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/ * get_package_code (TYPE_1__*) ; 
 int /*<<< orphan*/ * get_product_code (TYPE_1__*) ; 
 int /*<<< orphan*/  get_registered_local_package (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT get_local_package( const WCHAR *filename, WCHAR *localfile )
{
    WCHAR *product_code, *package_code;
    MSIDATABASE *db;
    UINT r;

    if ((r = MSI_OpenDatabaseW( filename, MSIDBOPEN_READONLY, &db )) != ERROR_SUCCESS)
    {
        if (GetFileAttributesW( filename ) == INVALID_FILE_ATTRIBUTES)
            return ERROR_FILE_NOT_FOUND;
        return r;
    }
    if (!(product_code = get_product_code( db )))
    {
        msiobj_release( &db->hdr );
        return ERROR_INSTALL_PACKAGE_INVALID;
    }
    if (!(package_code = get_package_code( db )))
    {
        msi_free( product_code );
        msiobj_release( &db->hdr );
        return ERROR_INSTALL_PACKAGE_INVALID;
    }
    r = get_registered_local_package( product_code, package_code, localfile );
    msi_free( package_code );
    msi_free( product_code );
    msiobj_release( &db->hdr );
    return r;
}