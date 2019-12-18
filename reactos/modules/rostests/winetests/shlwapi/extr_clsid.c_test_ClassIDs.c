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
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int E_FAIL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  const IID_Endianness ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/ ** TEST_guids ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pSHLWAPI_23 (int /*<<< orphan*/  const*,char*,int) ; 
 scalar_t__ pSHLWAPI_269 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_ClassIDs(void)
{
  const GUID **guids = TEST_guids;
  char szBuff[256];
  GUID guid;
  DWORD dwLen;
  BOOL bRet;
  int i = 0;
  BOOL is_vista = FALSE;

  if (!pSHLWAPI_269 || !pSHLWAPI_23)
    return;

  while (*guids)
  {
    dwLen = pSHLWAPI_23(*guids, szBuff, 256);
    if (!i && dwLen == S_OK) is_vista = TRUE;  /* seems to return an HRESULT on vista */
    ok(dwLen == (is_vista ? S_OK : 39), "wrong size %u for id %d\n", dwLen, i);

    bRet = pSHLWAPI_269(szBuff, &guid);
    ok(bRet != FALSE, "created invalid string '%s'\n", szBuff);

    if (bRet)
      ok(IsEqualGUID(*guids, &guid), "GUID created wrong %d\n", i);

    guids++;
    i++;
  }

  /* Test endianness */
  dwLen = pSHLWAPI_23(&IID_Endianness, szBuff, 256);
  ok(dwLen == (is_vista ? S_OK : 39), "wrong size %u for IID_Endianness\n", dwLen);

  ok(!strcmp(szBuff, "{01020304-0506-0708-090A-0B0C0D0E0F0A}"),
     "Endianness Broken, got '%s'\n", szBuff);

  /* test lengths */
  szBuff[0] = ':';
  dwLen = pSHLWAPI_23(&IID_Endianness, szBuff, 0);
  ok(dwLen == (is_vista ? E_FAIL : 0), "accepted bad length\n");
  ok(szBuff[0] == ':', "wrote to buffer with no length\n");

  szBuff[0] = ':';
  dwLen = pSHLWAPI_23(&IID_Endianness, szBuff, 38);
  ok(dwLen == (is_vista ? E_FAIL : 0), "accepted bad length\n");
  ok(szBuff[0] == ':', "wrote to buffer with no length\n");

  szBuff[0] = ':';
  dwLen = pSHLWAPI_23(&IID_Endianness, szBuff, 39);
  ok(dwLen == (is_vista ? S_OK : 39), "rejected ok length\n");
  ok(szBuff[0] == '{', "Didn't write to buffer with ok length\n");

  /* Test string */
  strcpy(szBuff, "{xxx-");
  bRet = pSHLWAPI_269(szBuff, &guid);
  ok(bRet == FALSE, "accepted invalid string\n");

  dwLen = pSHLWAPI_23(&IID_Endianness, szBuff, 39);
  ok(dwLen == (is_vista ? S_OK : 39), "rejected ok length\n");
  ok(szBuff[0] == '{', "Didn't write to buffer with ok length\n");
}