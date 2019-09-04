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

/* Variables and functions */
 int /*<<< orphan*/  ApphelpCacheServiceDump ; 
 int /*<<< orphan*/  ApphelpCacheServiceFlush ; 
 int /*<<< orphan*/  ApphelpCacheServiceLookup ; 
 int /*<<< orphan*/  ApphelpCacheServiceRemove ; 
 int /*<<< orphan*/  ApphelpCacheServiceUpdate ; 
 int /*<<< orphan*/  ApphelpDBGReadRegistry ; 
 int /*<<< orphan*/  ApphelpDBGWriteRegistry ; 
 int /*<<< orphan*/  CallApphelp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpRegistryData (int) ; 
 int HandleDumpAttributes (int,char**,int*,char*) ; 
 int HandleImageArg (int,char**,int*,char,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IsOpt (char*,char*) ; 
 int /*<<< orphan*/  _getch () ; 
 int /*<<< orphan*/  xprintf (char*,...) ; 

int main(int argc, char* argv[])
{
    int n, unhandled = 0, keepopen = 0;

    for (n = 1; n < argc; ++n)
    {
        char* arg = argv[n];
        if (IsOpt(arg, "d"))
        {
            xprintf("Calling ApphelpCacheServiceDump\n");
            CallApphelp(ApphelpCacheServiceDump, NULL);
            unhandled = 0;
        }
        else if (IsOpt(arg, "h"))
        {
            DumpRegistryData(arg[1] == 'h');
            unhandled = 0;
        }
        else if (IsOpt(arg, "f"))
        {
            xprintf("Calling ApphelpCacheServiceFlush\n");
            CallApphelp(ApphelpCacheServiceFlush, NULL);
            unhandled = 0;
        }
        else if (IsOpt(arg, "z"))
        {
            xprintf("Calling ApphelpDBGReadRegistry\n");
            CallApphelp(ApphelpDBGReadRegistry, NULL);
            unhandled = 0;
        }
        else if (IsOpt(arg, "x"))
        {
            xprintf("Calling ApphelpDBGWriteRegistry\n");
            CallApphelp(ApphelpDBGWriteRegistry, NULL);
            unhandled = 0;
        }
        else if (IsOpt(arg, "l"))
        {
            unhandled |= HandleImageArg(argc, argv, &n, 'l',
                        ApphelpCacheServiceLookup, "ApphelpCacheServiceLookup");
        }
        else if (IsOpt(arg, "u"))
        {
            unhandled |= HandleImageArg(argc, argv, &n, 'u',
                        ApphelpCacheServiceUpdate, "ApphelpCacheServiceUpdate");
        }
        else if (IsOpt(arg, "r"))
        {
            unhandled |= HandleImageArg(argc, argv, &n, 'r',
                        ApphelpCacheServiceRemove, "ApphelpCacheServiceRemove");
        }
        else if (IsOpt(arg, "a"))
        {
            unhandled |= HandleDumpAttributes(argc, argv, &n, "a");
        }
        else if (IsOpt(arg, "k"))
        {
            keepopen = 1;
        }
        else
        {
            unhandled = 1;
        }
    }
    if (unhandled || argc == 1)
    {
        xprintf("Usage: %s [-d|-z|-x|-h|-H|-f|-[l|L] <image>|-[u|U] <image>|-[r|R] <image>|-k]\n", argv[0]);
        xprintf("           -d: Dump shim cache over debug output\n");
        xprintf("           -z: DEBUG Read shim cache from registry\n");
        xprintf("           -x: DEBUG Write shim cache to registry\n");
        xprintf("           -h: Hexdump shim registry key\n");
        xprintf("           -H: Crc + Length from shim registry key only\n");
        xprintf("           -f: Flush (clear) the shim cache\n");
        xprintf("           -l: Lookup <image> in the shim cache\n");
        xprintf("           -L: Lookup <image> in the shim cache without mapping it\n");
        xprintf("           -u: Update (insert) <image> in the shim cache\n");
        xprintf("           -U: Update (insert) <image> in the shim cache without mapping it\n");
        xprintf("           -r: Remove <image> from the shim cache\n");
        xprintf("           -R: Remove <image> from the shim cache without mapping it\n");
        xprintf("           -a: Dump file attributes as used in the appcompat database\n");
        xprintf("           -k: Keep the console open\n");
    }
    if (keepopen)
    {
        _getch();
    }
    return unhandled;
}