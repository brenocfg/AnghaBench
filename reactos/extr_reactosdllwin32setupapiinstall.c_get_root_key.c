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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  strcmpiW (char const*,char const*) ; 

__attribute__((used)) static HKEY get_root_key( const WCHAR *name, HKEY def_root )
{
    static const WCHAR HKCR[] = {'H','K','C','R',0};
    static const WCHAR HKCU[] = {'H','K','C','U',0};
    static const WCHAR HKLM[] = {'H','K','L','M',0};
    static const WCHAR HKU[]  = {'H','K','U',0};
    static const WCHAR HKR[]  = {'H','K','R',0};

    if (!strcmpiW( name, HKCR )) return HKEY_CLASSES_ROOT;
    if (!strcmpiW( name, HKCU )) return HKEY_CURRENT_USER;
    if (!strcmpiW( name, HKLM )) return HKEY_LOCAL_MACHINE;
    if (!strcmpiW( name, HKU )) return HKEY_USERS;
    if (!strcmpiW( name, HKR )) return def_root;
    return 0;
}