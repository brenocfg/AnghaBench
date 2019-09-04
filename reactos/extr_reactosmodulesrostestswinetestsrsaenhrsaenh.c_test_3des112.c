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
typedef  int /*<<< orphan*/  des112 ;
struct TYPE_2__ {unsigned char* origstr; int strlen; int enclen; int buflen; int const* decstr; } ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_3DES_112 ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int NTE_BAD_ALGID ; 
 int NTE_BAD_DATA ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* cTestData ; 
 int derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  printBytes (char*,unsigned char*,int) ; 

__attribute__((used)) static void test_3des112(void)
{
    HCRYPTKEY hKey;
    BOOL result;
    DWORD dwLen;
    unsigned char pbData[16], enc_data[16], bad_data[16];
    static const BYTE des112[16] = {
        0x8e, 0x0c, 0x3c, 0xa3, 0x05, 0x88, 0x5f, 0x7a,
        0x32, 0xa1, 0x06, 0x52, 0x64, 0xd2, 0x44, 0x1c };
    int i;

    result = derive_key(CALG_3DES_112, &hKey, 0);
    if (!result) {
        /* rsaenh compiled without OpenSSL */
        ok(GetLastError() == NTE_BAD_ALGID, "%08x\n", GetLastError());
        return;
    }

    for (i=0; i<sizeof(pbData); i++) pbData[i] = (unsigned char)i;
    
    dwLen = 13;
    result = CryptEncrypt(hKey, 0, TRUE, 0, pbData, &dwLen, 16);
    ok(result, "%08x\n", GetLastError());
    
    ok(!memcmp(pbData, des112, sizeof(des112)), "3DES_112 encryption failed!\n");

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
      ok(memcmp(pbData,cTestData[i].decstr,cTestData[1].enclen)==0,"decryption incorrect %d\n",i);
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
}