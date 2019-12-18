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
typedef  char* LPWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pFBadRglpszW (char**,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FBadRglpszW(void)
{
    LPWSTR lpStrs[4];
    static WCHAR szString[] = { 'A',' ','S','t','r','i','n','g','\0' };
    BOOL bRet;

    if (!pFBadRglpszW)
    {
        win_skip("FBadRglpszW is not available\n");
        return;
    }

    bRet = pFBadRglpszW(NULL, 10);
    ok(bRet == TRUE, "FBadRglpszW(Null): expected TRUE, got FALSE\n");

    lpStrs[0] = lpStrs[1] = lpStrs[2] = lpStrs[3] = NULL;
    bRet = pFBadRglpszW(lpStrs, 4);
    ok(bRet == TRUE, "FBadRglpszW(Nulls): expected TRUE, got FALSE\n");

    lpStrs[0] = lpStrs[1] = lpStrs[2] = szString;
    bRet = pFBadRglpszW(lpStrs, 3);
    ok(bRet == FALSE, "FBadRglpszW(valid): expected FALSE, got TRUE\n");

    bRet = pFBadRglpszW(lpStrs, 4);
    ok(bRet == TRUE, "FBadRglpszW(1 invalid): expected TRUE, got FALSE\n");
}