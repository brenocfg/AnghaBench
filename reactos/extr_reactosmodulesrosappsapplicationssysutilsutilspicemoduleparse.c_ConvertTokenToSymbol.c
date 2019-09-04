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
typedef  int /*<<< orphan*/ * PULONG ;
typedef  scalar_t__ PDEBUG_MODULE ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindFunctionInModuleByName (char*,scalar_t__) ; 
 scalar_t__ IsModuleLoaded (char*) ; 
 char* PICE_strchr (char*,char) ; 
 int /*<<< orphan*/  PICE_strcpy (char*,char*) ; 
 int /*<<< orphan*/  ScanExports (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ pCurrentMod ; 

BOOLEAN ConvertTokenToSymbol(LPSTR pToken,PULONG pValue)
{
    LPSTR pEx;
    char temp[64];
    LPSTR p;
	PDEBUG_MODULE pModFound;

    DPRINT((0,"ConvertTokenToSymbol()\n"));

    PICE_strcpy(temp,pToken);
    p = temp;

    // test for module!symbol string
    pEx = PICE_strchr(p,'!');
    if(pEx)
    {
        DPRINT((0,"ConvertTokenToSymbol(): module!symbol syntax detected\n"));
        // terminate module name
        *pEx = 0;
        // now we have two pointers
        pEx++;
        DPRINT((0,"ConvertTokenToSymbol(): module = %s symbol = %s\n",p,pEx));

		if( pModFound=IsModuleLoaded(p) )
        {
            if((*pValue = FindFunctionInModuleByName(pEx,pModFound)))
                return TRUE;
        }
    }
    else
    {
        if(pCurrentMod)
        {
            if((*pValue = FindFunctionInModuleByName(p,pCurrentMod)))
                return TRUE;
        }
    	return ScanExports(p,pValue);
    }
    return FALSE;
}