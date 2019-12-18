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
typedef  int /*<<< orphan*/  hashProperty ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  PCCRL_CONTEXT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int CertGetCRLContextProperty (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int CryptHashCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void checkCRLHash(const BYTE *data, DWORD dataLen, ALG_ID algID,
 PCCRL_CONTEXT context, DWORD propID)
{
    BYTE hash[20] = { 0 }, hashProperty[20];
    BOOL ret;
    DWORD size;

    memset(hash, 0, sizeof(hash));
    memset(hashProperty, 0, sizeof(hashProperty));
    size = sizeof(hash);
    ret = CryptHashCertificate(0, algID, 0, data, dataLen, hash, &size);
    ok(ret, "CryptHashCertificate failed: %08x\n", GetLastError());
    ret = CertGetCRLContextProperty(context, propID, hashProperty, &size);
    ok(ret, "CertGetCRLContextProperty failed: %08x\n", GetLastError());
    ok(!memcmp(hash, hashProperty, size), "Unexpected hash for property %d\n",
     propID);
}