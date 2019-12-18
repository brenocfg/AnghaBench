#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pbData ;
typedef  int /*<<< orphan*/  des ;
struct TYPE_2__ {unsigned char* origstr; scalar_t__ strlen; scalar_t__ enclen; int buflen; int const* decstr; } ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_DES ; 
 scalar_t__ CRYPT_MODE_ECB ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,scalar_t__*) ; 
 int CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,scalar_t__*,int) ; 
 int CryptGetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  KP_MODE ; 
 int NTE_BAD_ALGID ; 
 int NTE_BAD_DATA ; 
 scalar_t__ STRONG_PROV ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 TYPE_1__* cTestData ; 
 int derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (unsigned char*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  printBytes (char*,unsigned char*,scalar_t__) ; 

__attribute__((used)) static void test_des(void) 
{
    HCRYPTKEY hKey;
    BOOL result;
    DWORD dwLen, dwMode;
    unsigned char pbData[16], enc_data[16], bad_data[16];
    static const BYTE des[16] = {
        0x58, 0x86, 0x42, 0x46, 0x65, 0x4b, 0x92, 0x62,
        0xcf, 0x0f, 0x65, 0x37, 0x43, 0x7a, 0x82, 0xb9 };
    static const BYTE des_old_behavior[16] = {
        0xb0, 0xfd, 0x11, 0x69, 0x76, 0xb1, 0xa1, 0x03,
        0xf7, 0xbc, 0x23, 0xaa, 0xd4, 0xc1, 0xc9, 0x55 };
    static const BYTE des_old_strong[16] = {
        0x9b, 0xc1, 0x2a, 0xec, 0x4a, 0xf9, 0x0f, 0x14,
        0x0a, 0xed, 0xf6, 0xd3, 0xdc, 0xad, 0xf7, 0x0c };
    int i;

    result = derive_key(CALG_DES, &hKey, 0);
    if (!result) {
        /* rsaenh compiled without OpenSSL */
        ok(GetLastError()==NTE_BAD_ALGID, "%08x\n", GetLastError());
        return;
    }

    dwMode = CRYPT_MODE_ECB;
    result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
    ok(result, "%08x\n", GetLastError());
    
    dwLen = sizeof(DWORD);
    result = CryptGetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, &dwLen, 0);
    ok(result, "%08x\n", GetLastError());
    ok(dwMode == CRYPT_MODE_ECB, "Expected CRYPT_MODE_ECB, got %d\n", dwMode);
    
    for (i=0; i<sizeof(pbData); i++) pbData[i] = (unsigned char)i;
    
    dwLen = 13;
    result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwLen, 16);
    ok(result, "%08x\n", GetLastError());
    
    ok(!memcmp(pbData, des, sizeof(des)), "DES encryption failed!\n");

    result = CryptDecrypt(hKey, 0, TRUE, 0, pbData, &dwLen);
    ok(result, "%08x\n", GetLastError());

    for (i=0; i<4; i++)
    {
      memcpy(pbData,cTestData[i].origstr,cTestData[i].strlen);

      dwLen = cTestData[i].enclen;
      result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwLen, cTestData[i].buflen);
      ok(result, "%08x\n", GetLastError());
      ok(dwLen==cTestData[i].buflen,"length incorrect, got %d, expected %d\n",dwLen,cTestData[i].buflen);
      memcpy(enc_data, pbData, cTestData[i].buflen);

      result = CryptDecrypt(hKey, 0, TRUE, 0, pbData, &dwLen);
      ok(result, "%08x\n", GetLastError());
      ok(dwLen==cTestData[i].enclen,"length incorrect, got %d, expected %d\n",dwLen,cTestData[i].enclen);
      ok(memcmp(pbData,cTestData[i].decstr,cTestData[i].enclen)==0,"decryption incorrect %d\n",i);
      if((dwLen != cTestData[i].enclen) ||
         memcmp(pbData,cTestData[i].decstr,cTestData[i].enclen))
      {
          printBytes("expected",cTestData[i].decstr,cTestData[i].strlen);
          printBytes("got",pbData,dwLen);
      }

      /* Test bad data:
         Decrypting a block of bad data with Final = TRUE should restore the
         initial state of the key as well as decrypting a block of good data.
       */

      /* Changing key state by setting Final = FALSE */
      dwLen = cTestData[i].buflen;
      memcpy(pbData, enc_data, cTestData[i].buflen);
      result = CryptDecrypt(hKey, 0, FALSE, 0, pbData, &dwLen);
      ok(result, "%08x\n", GetLastError());

      /* Restoring key state by decrypting bad_data with Final = TRUE */
      memcpy(bad_data, enc_data, cTestData[i].buflen);
      bad_data[cTestData[i].buflen - 1] = ~bad_data[cTestData[i].buflen - 1];
      SetLastError(0xdeadbeef);
      result = CryptDecrypt(hKey, 0, TRUE, 0, bad_data, &dwLen);
      ok(!result, "CryptDecrypt should failed!\n");
      ok(GetLastError() == NTE_BAD_DATA, "%08x\n", GetLastError());
      ok(dwLen==cTestData[i].buflen,"length incorrect, got %d, expected %d\n",dwLen,cTestData[i].buflen);
      ok(memcmp(pbData,cTestData[i].decstr,cTestData[1].enclen)==0,"decryption incorrect %d\n",i);

      /* Checking key state */
      dwLen = cTestData[i].buflen;
      memcpy(pbData, enc_data, cTestData[i].buflen);
      result = CryptDecrypt(hKey, 0, TRUE, 0, pbData, &dwLen);
      ok(result, "%08x\n", GetLastError());
      ok(dwLen==cTestData[i].enclen,"length incorrect, got %d, expected %d\n",dwLen,cTestData[i].enclen);
      ok(memcmp(pbData,cTestData[i].decstr,cTestData[1].enclen)==0,"decryption incorrect %d\n",i);
      if((dwLen != cTestData[i].enclen) ||
         memcmp(pbData,cTestData[i].decstr,cTestData[i].enclen))
      {
          printBytes("expected",cTestData[i].decstr,cTestData[i].strlen);
          printBytes("got",pbData,dwLen);
      }
    }

    result = CryptDestroyKey(hKey);
    ok(result, "%08x\n", GetLastError());

    /* Windows >= XP changed the way DES keys are derived, this test ensures we don't break that */
    derive_key(CALG_DES, &hKey, 56);

    dwMode = CRYPT_MODE_ECB;
    result = CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0);
    ok(result, "%08x\n", GetLastError());

    for (i=0; i<sizeof(pbData); i++) pbData[i] = (unsigned char)i;

    dwLen = 13;
    result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwLen, 16);
    ok(result, "%08x\n", GetLastError());
    ok(!memcmp(pbData, des, sizeof(des)) || broken(
    !memcmp(pbData, des_old_behavior, sizeof(des)) ||
    (STRONG_PROV && !memcmp(pbData, des_old_strong, sizeof(des)))) /* <= 2000 */,
       "DES encryption failed!\n");

    result = CryptDestroyKey(hKey);
    ok(result, "%08x\n", GetLastError());
}