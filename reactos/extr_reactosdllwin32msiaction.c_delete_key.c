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
typedef  int REGSAM ;
typedef  int /*<<< orphan*/  MSICOMPONENT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int READ_CONTROL ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegDeleteKeyExW (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int get_registry_view (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 int /*<<< orphan*/  open_key (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* strdupW (scalar_t__ const*) ; 
 scalar_t__* strrchrW (scalar_t__*,char) ; 

__attribute__((used)) static void delete_key( const MSICOMPONENT *comp, HKEY root, const WCHAR *path )
{
    REGSAM access = 0;
    WCHAR *subkey, *p;
    HKEY hkey;
    LONG res;

    access |= get_registry_view( comp );

    if (!(subkey = strdupW( path ))) return;
    do
    {
        if ((p = strrchrW( subkey, '\\' )))
        {
            *p = 0;
            if (!p[1]) continue; /* trailing backslash */
            hkey = open_key( comp, root, subkey, FALSE, access | READ_CONTROL );
            if (!hkey) break;
            res = RegDeleteKeyExW( hkey, p + 1, access, 0 );
            RegCloseKey( hkey );
        }
        else
            res = RegDeleteKeyExW( root, subkey, access, 0 );
        if (res)
        {
            TRACE("failed to delete key %s (%d)\n", debugstr_w(subkey), res);
            break;
        }
    } while (p);
    msi_free( subkey );
}