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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__* PULONG ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 char* PICE_strchr (char*,char) ; 
 int /*<<< orphan*/  PICE_strcpy (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ConvertTokenToModuleAndName(LPSTR pToken,PULONG pulModuleName,PULONG pulFunctionName)
{
    LPSTR pEx;
    char temp[64];
    LPSTR p;
    static char module_name[128];
    static char function_name[128];

    // test for module!symbol string
    PICE_strcpy(temp,pToken);
    p = temp;

    DPRINT((0,"ConvertTokenToModuleAndName(%s)\n",p));

    pEx = PICE_strchr(p,'!');
    if(pEx)
    {
        DPRINT((0,"ConvertTokenToModuleAndName(): module!symbol syntax detected\n"));
        // terminate module name
        *pEx = 0;
        // now we have two pointers
        pEx++;
        DPRINT((0,"ConvertTokenToModuleAndName(): module = %s symbol = %s\n",p,pEx));
        PICE_strcpy(module_name,p);
        PICE_strcpy(function_name,pEx);
        *pulModuleName = (ULONG)module_name;
        *pulFunctionName = (ULONG)function_name;
        return TRUE;

    }
    return FALSE;
}