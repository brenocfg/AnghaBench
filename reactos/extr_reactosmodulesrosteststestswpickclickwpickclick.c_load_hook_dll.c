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
typedef  int /*<<< orphan*/  dllpath ;
typedef  int /*<<< orphan*/ * HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * LoadLibrary (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static HINSTANCE load_hook_dll()
{
    HINSTANCE hinstDll;
    char dllpath[MAX_PATH];
    char* p;

    hinstDll=LoadLibrary("hook.dll");
    if (hinstDll != NULL)
        return hinstDll;

    if (!GetModuleFileName(NULL,dllpath,sizeof(dllpath)))
        return NULL;

    p=strrchr(dllpath,'\\');
    if (!p)
        return NULL;
    *p='\0';
    p=strrchr(dllpath,'\\');
    if (!p)
        return NULL;
    *p='\0';
    strcat(dllpath,"\\hookdll\\hook.dll");
    hinstDll=LoadLibrary(dllpath);
    return hinstDll;
}