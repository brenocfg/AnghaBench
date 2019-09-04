#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 scalar_t__* msi_alloc (int) ; 
 scalar_t__* msi_dup_property (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 int /*<<< orphan*/  msi_reset_folders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_set_property (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  strcatW (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  strcmpW (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__*) ; 
 int strlenW (scalar_t__*) ; 
 scalar_t__* szSemiColon ; 
 int /*<<< orphan*/  szSourceDir ; 

__attribute__((used)) static void append_productcode(MSIPACKAGE* package, LPCWSTR action_property,
                               LPCWSTR productid)
{
    LPWSTR prop;
    LPWSTR newprop;
    DWORD len;
    UINT r;

    prop = msi_dup_property(package->db, action_property );
    if (prop)
        len = strlenW(prop);
    else
        len = 0;

    /*separator*/
    len ++;

    len += strlenW(productid);

    /*null*/
    len++;

    newprop = msi_alloc( len*sizeof(WCHAR) );

    if (prop)
    {
        strcpyW(newprop,prop);
        strcatW(newprop,szSemiColon);
    }
    else
        newprop[0] = 0;
    strcatW(newprop,productid);

    r = msi_set_property( package->db, action_property, newprop, -1 );
    if (r == ERROR_SUCCESS && !strcmpW( action_property, szSourceDir ))
        msi_reset_folders( package, TRUE );

    TRACE("Found Related Product... %s now %s\n",
          debugstr_w(action_property), debugstr_w(newprop));

    msi_free( prop );
    msi_free( newprop );
}