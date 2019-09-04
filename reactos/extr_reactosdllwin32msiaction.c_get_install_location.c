#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  ProductCode; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MSIREG_OpenInstallProps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_reg_get_val_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szInstallLocation ; 

__attribute__((used)) static WCHAR *get_install_location( MSIPACKAGE *package )
{
    HKEY hkey;
    WCHAR *path;

    if (!package->ProductCode) return NULL;
    if (MSIREG_OpenInstallProps( package->ProductCode, package->Context, NULL, &hkey, FALSE )) return NULL;
    if ((path = msi_reg_get_val_str( hkey, szInstallLocation )) && !path[0])
    {
        msi_free( path );
        path = NULL;
    }
    RegCloseKey( hkey );
    return path;
}