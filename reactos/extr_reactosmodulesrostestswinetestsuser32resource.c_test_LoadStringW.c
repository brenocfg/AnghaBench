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
typedef  int /*<<< orphan*/  returnedstringw ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int LoadStringW (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LoadStringW(void)
{
    HINSTANCE hInst = GetModuleHandleA(NULL);
    WCHAR copiedstringw[128], returnedstringw[128], *resourcepointer = NULL;
    char copiedstring[128], returnedstring[128];
    int length1, length2, retvalue;

    /* Check that the string which is returned by LoadStringW matches
       the string at the pointer returned by LoadStringW when called with buflen = 0 */
    SetLastError(0xdeadbeef);
    length1 = LoadStringW(hInst, 2, (WCHAR *) &resourcepointer, 0); /* get pointer to resource. */
    if (!length1)
    {
        if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
            win_skip( "LoadStringW not implemented\n" );
        else
            win_skip( "LoadStringW does not return a pointer to the resource\n" );
        return;
    }
    length2 = LoadStringW(hInst, 2, returnedstringw, sizeof(returnedstringw) /sizeof(WCHAR)); /* get resource string */
    ok(length2 > 0, "LoadStringW failed to load resource 2, ret %d, err %d\n", length2, GetLastError());
    ok(length1 == length2, "LoadStringW returned different values dependent on buflen. ret1 %d, ret2 %d\n",
        length1, length2);
    ok(length1 > 0 && resourcepointer != NULL, "LoadStringW failed to get pointer to resource 2, ret %d, err %d\n",
        length1, GetLastError());

    /* Copy the resource since it is not '\0' terminated, and add '\0' to the end */
    if(resourcepointer != NULL) /* Check that the resource pointer was loaded to avoid access violation */
    {
        memcpy(copiedstringw, resourcepointer, length1 * sizeof(WCHAR));
        copiedstringw[length1] = '\0';
        /* check that strings match */
        WideCharToMultiByte( CP_ACP, 0, returnedstringw, -1, returnedstring, 128, NULL, NULL );
        WideCharToMultiByte( CP_ACP, 0, copiedstringw, -1, copiedstring, 128, NULL, NULL );
        ok(!memcmp(copiedstringw, returnedstringw, (length2 + 1)*sizeof(WCHAR)),
           "strings don't match: returnedstring = %s, copiedstring = %s\n", returnedstring, copiedstring);
    }

    /* check that calling LoadStringW with buffer = NULL returns zero */
    retvalue = LoadStringW(hInst, 2, NULL, 0);
    ok(!retvalue, "LoadStringW returned a non-zero value when called with buffer = NULL, retvalue = %d\n", retvalue);
    /* check again, with a different buflen value, that calling LoadStringW with buffer = NULL returns zero */
    retvalue = LoadStringW(hInst, 2, NULL, 128);
    ok(!retvalue, "LoadStringW returned a non-zero value when called with buffer = NULL, retvalue = %d\n", retvalue);
}