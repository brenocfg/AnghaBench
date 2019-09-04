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
struct TYPE_6__ {TYPE_1__* assembly; } ;
struct TYPE_5__ {char const* display_name; } ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_2__ MSICOMPONENT ;
typedef  int DWORD ;

/* Variables and functions */
 char* msi_alloc (int) ; 
 char* resolve_keypath (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *build_full_keypath( MSIPACKAGE *package, MSICOMPONENT *comp )
{
    if (comp->assembly)
    {
        const WCHAR prefixW[] = {'<','\\',0};
        DWORD len = strlenW( prefixW ) + strlenW( comp->assembly->display_name );
        WCHAR *keypath = msi_alloc( (len + 1) * sizeof(WCHAR) );

        if (keypath)
        {
            strcpyW( keypath, prefixW );
            strcatW( keypath, comp->assembly->display_name );
        }
        return keypath;
    }
    return resolve_keypath( package, comp );
}