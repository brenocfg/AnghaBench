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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptGetProvParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NTE_BAD_TYPE ; 
 int /*<<< orphan*/  PP_KEYX_KEYSIZE_INC ; 
 int /*<<< orphan*/  PP_SIG_KEYSIZE_INC ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  nt4 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_prov(void) 
{
    BOOL result;
    DWORD dwLen, dwInc;
    
    dwLen = (DWORD)sizeof(DWORD);
    SetLastError(0xdeadbeef);
    result = CryptGetProvParam(hProv, PP_SIG_KEYSIZE_INC, (BYTE*)&dwInc, &dwLen, 0);
    if (!result && GetLastError() == NTE_BAD_TYPE)
    {
        skip("PP_SIG_KEYSIZE_INC is not supported (win9x or NT)\n");
        nt4++;
    }
    else
        ok(result && dwInc==8, "%08x, %d\n", GetLastError(), dwInc);
    
    dwLen = (DWORD)sizeof(DWORD);
    SetLastError(0xdeadbeef);
    result = CryptGetProvParam(hProv, PP_KEYX_KEYSIZE_INC, (BYTE*)&dwInc, &dwLen, 0);
    if (!result && GetLastError() == NTE_BAD_TYPE)
        skip("PP_KEYX_KEYSIZE_INC is not supported (win9x or NT)\n");
    else
        ok(result && dwInc==8, "%08x, %d\n", GetLastError(), dwInc);
}