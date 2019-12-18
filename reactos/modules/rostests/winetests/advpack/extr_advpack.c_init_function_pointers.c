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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hAdvPack ; 
 void* pCloseINFEngine ; 
 void* pDelNode ; 
 void* pGetVersionFromFile ; 
 void* pOpenINFEngine ; 
 void* pSetPerUserSecValues ; 
 void* pTranslateInfString ; 
 void* pTranslateInfStringEx ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_function_pointers(void)
{
    hAdvPack = LoadLibraryA("advpack.dll");

    if (!hAdvPack)
        return FALSE;

    pCloseINFEngine = (void*)GetProcAddress(hAdvPack, "CloseINFEngine");
    pDelNode = (void *)GetProcAddress(hAdvPack, "DelNode");
    pGetVersionFromFile = (void *)GetProcAddress(hAdvPack, "GetVersionFromFile");
    pOpenINFEngine = (void*)GetProcAddress(hAdvPack, "OpenINFEngine");
    pSetPerUserSecValues = (void*)GetProcAddress(hAdvPack, "SetPerUserSecValues");
    pTranslateInfString = (void *)GetProcAddress(hAdvPack, "TranslateInfString");
    pTranslateInfStringEx = (void*)GetProcAddress(hAdvPack, "TranslateInfStringEx");

    if (!pCloseINFEngine || !pDelNode || !pGetVersionFromFile ||
        !pOpenINFEngine || !pSetPerUserSecValues || !pTranslateInfString)
    {
        win_skip("Needed functions are not available\n");
        FreeLibrary(hAdvPack);
        return FALSE;
    }

    return TRUE;
}