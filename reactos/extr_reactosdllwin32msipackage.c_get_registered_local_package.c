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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIINSTALLCONTEXT ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int GUID_SIZE ; 
 int /*<<< orphan*/  INSTALLPROPERTY_LOCALPACKAGEW ; 
 int /*<<< orphan*/  INSTALLPROPERTY_PACKAGECODEW ; 
 scalar_t__ MSIREG_OpenInstallProps (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MSIREG_OpenProductKey (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_locate_product (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_reg_get_val_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsquash_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT get_registered_local_package( const WCHAR *product, const WCHAR *package, WCHAR *localfile )
{
    MSIINSTALLCONTEXT context;
    HKEY product_key, props_key;
    WCHAR *registered_package = NULL, unsquashed[GUID_SIZE];
    UINT r;

    r = msi_locate_product( product, &context );
    if (r != ERROR_SUCCESS)
        return r;

    r = MSIREG_OpenProductKey( product, NULL, context, &product_key, FALSE );
    if (r != ERROR_SUCCESS)
        return r;

    r = MSIREG_OpenInstallProps( product, context, NULL, &props_key, FALSE );
    if (r != ERROR_SUCCESS)
    {
        RegCloseKey( product_key );
        return r;
    }
    r = ERROR_FUNCTION_FAILED;
    registered_package = msi_reg_get_val_str( product_key, INSTALLPROPERTY_PACKAGECODEW );
    if (!registered_package)
        goto done;

    unsquash_guid( registered_package, unsquashed );
    if (!strcmpiW( package, unsquashed ))
    {
        WCHAR *filename = msi_reg_get_val_str( props_key, INSTALLPROPERTY_LOCALPACKAGEW );
        if (!filename)
            goto done;

        strcpyW( localfile, filename );
        msi_free( filename );
        r = ERROR_SUCCESS;
    }
done:
    msi_free( registered_package );
    RegCloseKey( props_key );
    RegCloseKey( product_key );
    return r;
}