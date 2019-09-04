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
typedef  char* LPSTR ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pFBadRglpszA (char**,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FBadRglpszA(void)
{
    LPSTR lpStrs[4];
    static CHAR szString[] = "A String";
    BOOL bRet;

    if (!pFBadRglpszA)
    {
        win_skip("FBadRglpszA is not available\n");
        return;
    }

    bRet = pFBadRglpszA(NULL, 10);
    ok(bRet == TRUE, "FBadRglpszA(Null): expected TRUE, got FALSE\n");

    lpStrs[0] = lpStrs[1] = lpStrs[2] = lpStrs[3] = NULL;
    bRet = pFBadRglpszA(lpStrs, 4);
    ok(bRet == TRUE, "FBadRglpszA(Nulls): expected TRUE, got FALSE\n");

    lpStrs[0] = lpStrs[1] = lpStrs[2] = szString;
    bRet = pFBadRglpszA(lpStrs, 3);
    ok(bRet == FALSE, "FBadRglpszA(valid): expected FALSE, got TRUE\n");

    bRet = pFBadRglpszA(lpStrs, 4);
    ok(bRet == TRUE, "FBadRglpszA(1 invalid): expected TRUE, got FALSE\n");
}