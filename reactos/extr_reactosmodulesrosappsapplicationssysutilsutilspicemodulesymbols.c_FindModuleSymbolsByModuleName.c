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
typedef  size_t ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ PICE_SYMBOLFILE_HEADER ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int DEBUG_MODULE_NAME_LEN ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PICE_MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ PICE_wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__** apSymbols ; 
 size_t ulNumSymbolsLoaded ; 

PICE_SYMBOLFILE_HEADER* FindModuleSymbolsByModuleName(LPSTR modname)
{
    ULONG i;
	WCHAR tempstr[DEBUG_MODULE_NAME_LEN];

    DPRINT((0,"FindModuleSymbols()\n"));
	if( !PICE_MultiByteToWideChar(CP_ACP, NULL, modname, -1, tempstr, DEBUG_MODULE_NAME_LEN ) )
	{
		DPRINT((0,"Can't convert module name in FindModuleSymbols.\n"));
		return NULL;
	}

    for(i=0;i<ulNumSymbolsLoaded;i++)
    {
        if(PICE_wcsicmp(tempstr,apSymbols[i]->name) == 0)
            return apSymbols[i];
    }

    return NULL;
}