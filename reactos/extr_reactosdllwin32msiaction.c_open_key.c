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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int /*<<< orphan*/  MSICOMPONENT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  get_registry_view (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 scalar_t__* strchrW (scalar_t__*,char) ; 
 scalar_t__* strdupW (scalar_t__ const*) ; 

__attribute__((used)) static HKEY open_key( const MSICOMPONENT *comp, HKEY root, const WCHAR *path, BOOL create, REGSAM access )
{
    WCHAR *subkey, *p, *q;
    HKEY hkey, ret = NULL;
    LONG res;

    access |= get_registry_view( comp );

    if (!(subkey = strdupW( path ))) return NULL;
    p = subkey;
    if ((q = strchrW( p, '\\' ))) *q = 0;
    if (create)
        res = RegCreateKeyExW( root, subkey, 0, NULL, 0, access, NULL, &hkey, NULL );
    else
        res = RegOpenKeyExW( root, subkey, 0, access, &hkey );
    if (res)
    {
        TRACE("failed to open key %s (%d)\n", debugstr_w(subkey), res);
        msi_free( subkey );
        return NULL;
    }
    if (q && q[1])
    {
        ret = open_key( comp, hkey, q + 1, create, access );
        RegCloseKey( hkey );
    }
    else ret = hkey;
    msi_free( subkey );
    return ret;
}