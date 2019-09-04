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
typedef  enum module_type { ____Placeholder_module_type } module_type ;
typedef  char WCHAR ;

/* Variables and functions */
 int DMT_DBG ; 
 int DMT_ELF ; 
 int DMT_MACHO ; 
 int DMT_PDB ; 
 int DMT_PE ; 
 int /*<<< orphan*/  S_DotDbgW ; 
 int /*<<< orphan*/  S_DotDylibW ; 
 int /*<<< orphan*/  S_DotPdbW ; 
 int /*<<< orphan*/  S_DotSoW ; 
 char* get_wine_loader_name () ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmpiW (char const*,char const*) ; 
 int strlenW (char const*) ; 
 int /*<<< orphan*/  strncmpiW (char const*,int /*<<< orphan*/ ,int) ; 

enum module_type module_get_type_by_name(const WCHAR* name)
{
    int loader_len, len = strlenW(name);
    const WCHAR *loader;

    /* Skip all version extensions (.[digits]) regex: "(\.\d+)*$" */
    do
    {
        int i = len;

        while (i && name[i - 1] >= '0' && name[i - 1] <= '9') i--;

        if (i && name[i - 1] == '.')
            len = i - 1;
        else
            break;
    } while (len);

    /* check for terminating .so or .so.[digit] */
    /* FIXME: Can't rely solely on extension; have to check magic or
     *        stop using .so on Mac OS X.  For now, base on platform. */
    if (len > 3 && !memcmp(name + len - 3, S_DotSoW, 3))
#ifdef __APPLE__
        return DMT_MACHO;
#else
        return DMT_ELF;
#endif

    if (len > 6 && !strncmpiW(name + len - 6, S_DotDylibW, 6))
        return DMT_MACHO;

    if (len > 4 && !strncmpiW(name + len - 4, S_DotPdbW, 4))
        return DMT_PDB;

    if (len > 4 && !strncmpiW(name + len - 4, S_DotDbgW, 4))
        return DMT_DBG;

    /* wine is also a native module (Mach-O on Mac OS X, ELF elsewhere) */
    loader = get_wine_loader_name();
    loader_len = strlenW( loader );
    if ((len == loader_len || (len > loader_len && name[len - loader_len - 1] == '/')) &&
        !strcmpiW(name + len - loader_len, loader))
    {
#ifdef __APPLE__
        return DMT_MACHO;
#else
        return DMT_ELF;
#endif
    }
    return DMT_PE;
}