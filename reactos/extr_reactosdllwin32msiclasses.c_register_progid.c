#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  ProgID; TYPE_1__* CurVer; scalar_t__ IconPath; int /*<<< orphan*/  Description; } ;
struct TYPE_5__ {scalar_t__ ProgID; } ;
typedef  TYPE_2__ MSIPROGID ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ get_clsid_of_progid (TYPE_2__ const*) ; 
 int /*<<< orphan*/  msi_reg_set_subkey_val (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msi_reg_set_val_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* szCLSID ; 
 char const* szDefaultIcon ; 

__attribute__((used)) static UINT register_progid( const MSIPROGID* progid )
{
    static const WCHAR szCurVer[] = {'C','u','r','V','e','r',0};
    HKEY hkey = 0;
    UINT rc;

    rc = RegCreateKeyW( HKEY_CLASSES_ROOT, progid->ProgID, &hkey );
    if (rc == ERROR_SUCCESS)
    {
        LPCWSTR clsid = get_clsid_of_progid( progid );

        if (clsid)
            msi_reg_set_subkey_val( hkey, szCLSID, NULL, clsid );
        else
            TRACE("%s has no class\n", debugstr_w( progid->ProgID ) );

        if (progid->Description)
            msi_reg_set_val_str( hkey, NULL, progid->Description );

        if (progid->IconPath)
            msi_reg_set_subkey_val( hkey, szDefaultIcon, NULL, progid->IconPath );

        /* write out the current version */
        if (progid->CurVer)
            msi_reg_set_subkey_val( hkey, szCurVer, NULL, progid->CurVer->ProgID );

        RegCloseKey(hkey);
    }
    else
        ERR("failed to create key %s\n", debugstr_w( progid->ProgID ) );

    return rc;
}