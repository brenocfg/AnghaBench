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
typedef  int /*<<< orphan*/  mySig ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CALG_SHA1 ; 
 scalar_t__ CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptHashData (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptSignHashA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void verifySig(HCRYPTPROV csp, const BYTE *toSign, size_t toSignLen,
 const BYTE *sig, unsigned int sigLen)
{
    HCRYPTHASH hash;
    BOOL ret = CryptCreateHash(csp, CALG_SHA1, 0, 0, &hash);

    ok(ret, "CryptCreateHash failed: %08x\n", GetLastError());
    if (ret)
    {
        BYTE mySig[64];
        DWORD mySigSize = sizeof(mySig);

        ret = CryptHashData(hash, toSign, toSignLen, 0);
        ok(ret, "CryptHashData failed: %08x\n", GetLastError());
        /* use the A variant so the test can run on Win9x */
        ret = CryptSignHashA(hash, AT_SIGNATURE, NULL, 0, mySig, &mySigSize);
        ok(ret, "CryptSignHash failed: %08x\n", GetLastError());
        if (ret)
        {
            ok(mySigSize == sigLen, "Expected sig length %d, got %d\n",
             sigLen, mySigSize);
            ok(!memcmp(mySig, sig, sigLen), "Unexpected signature\n");
        }
        CryptDestroyHash(hash);
    }
}