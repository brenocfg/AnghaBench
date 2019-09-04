#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pvRight ;
typedef  int /*<<< orphan*/  pvLeft ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {void* cb; void* lpb; } ;
struct TYPE_8__ {char* lpszA; TYPE_1__ bin; } ;
struct TYPE_9__ {TYPE_2__ Value; scalar_t__ ulPropTag; } ;
typedef  TYPE_3__ SPropValue ;
typedef  void* LPBYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FL_FULLSTRING ; 
 int FL_IGNORECASE ; 
 int FL_PREFIX ; 
 int FL_SUBSTRING ; 
 scalar_t__ PROP_ID_INVALID ; 
 scalar_t__ PT_BINARY ; 
 scalar_t__ PT_STRING8 ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFPropContainsProp (TYPE_3__*,TYPE_3__*,int) ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FPropContainsProp(void)
{
    static char szFull[] = "Full String";
    static char szFullLower[] = "full string";
    static char szPrefix[] = "Full";
    static char szPrefixLower[] = "full";
    static char szSubstring[] = "ll St";
    static char szSubstringLower[] = "ll st";
    SPropValue pvLeft, pvRight;
    ULONG pt;
    BOOL bRet;

    if (!pFPropContainsProp)
    {
        win_skip("FPropContainsProp is not available\n");
        return;
    }

    /* Ensure that only PT_STRING8 and PT_BINARY are handled */
    for (pt = 0; pt < PROP_ID_INVALID; pt++)
    {
        if (pt == PT_STRING8 || pt == PT_BINARY)
            continue; /* test these later */

        memset(&pvLeft, 0 ,sizeof(pvLeft));
        memset(&pvRight, 0 ,sizeof(pvRight));
        pvLeft.ulPropTag = pvRight.ulPropTag = pt;

        bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
        ok(bRet == FALSE, "pt= %d: Expected FALSE, got %d\n", pt, bRet);
    }

    /* test the various flag combinations */
    pvLeft.ulPropTag = pvRight.ulPropTag = PT_STRING8;
    pvLeft.Value.lpszA = szFull;
    pvRight.Value.lpszA = szFull;

    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
    ok(bRet == TRUE, "(full,full)[] match failed\n");
    pvRight.Value.lpszA = szPrefix;
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
    ok(bRet == FALSE, "(full,prefix)[] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == TRUE, "(full,prefix)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == TRUE, "(full,prefix)[SUBSTRING] match failed\n");
    pvRight.Value.lpszA = szPrefixLower;
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == FALSE, "(full,prefixlow)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == FALSE, "(full,prefixlow)[SUBSTRING] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX|FL_IGNORECASE);
    ok(bRet == TRUE, "(full,prefixlow)[PREFIX|IGNORECASE] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING|FL_IGNORECASE);
    ok(bRet == TRUE, "(full,prefixlow)[SUBSTRING|IGNORECASE] match failed\n");
    pvRight.Value.lpszA = szSubstring;
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
    ok(bRet == FALSE, "(full,substr)[] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == FALSE, "(full,substr)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == TRUE, "(full,substr)[SUBSTRING] match failed\n");
    pvRight.Value.lpszA = szSubstringLower;
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == FALSE, "(full,substrlow)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == FALSE, "(full,substrlow)[SUBSTRING] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX|FL_IGNORECASE);
    ok(bRet == FALSE, "(full,substrlow)[PREFIX|IGNORECASE] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING|FL_IGNORECASE);
    ok(bRet == TRUE, "(full,substrlow)[SUBSTRING|IGNORECASE] match failed\n");
    pvRight.Value.lpszA = szFullLower;
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING|FL_IGNORECASE);
    ok(bRet == TRUE, "(full,fulllow)[IGNORECASE] match failed\n");

    pvLeft.ulPropTag = pvRight.ulPropTag = PT_BINARY;
    pvLeft.Value.bin.lpb = (LPBYTE)szFull;
    pvRight.Value.bin.lpb = (LPBYTE)szFull;
    pvLeft.Value.bin.cb = pvRight.Value.bin.cb = strlen(szFull);

    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
    ok(bRet == TRUE, "bin(full,full)[] match failed\n");
    pvRight.Value.bin.lpb = (LPBYTE)szPrefix;
    pvRight.Value.bin.cb = strlen(szPrefix);
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
    ok(bRet == FALSE, "bin(full,prefix)[] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == TRUE, "bin(full,prefix)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == TRUE, "bin(full,prefix)[SUBSTRING] match failed\n");
    pvRight.Value.bin.lpb = (LPBYTE)szPrefixLower;
    pvRight.Value.bin.cb = strlen(szPrefixLower);
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == FALSE, "bin(full,prefixlow)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == FALSE, "bin(full,prefixlow)[SUBSTRING] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX|FL_IGNORECASE);
    ok(bRet == FALSE, "bin(full,prefixlow)[PREFIX|IGNORECASE] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING|FL_IGNORECASE);
    ok(bRet == FALSE, "bin(full,prefixlow)[SUBSTRING|IGNORECASE] match failed\n");
    pvRight.Value.bin.lpb = (LPBYTE)szSubstring;
    pvRight.Value.bin.cb = strlen(szSubstring);
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING);
    ok(bRet == FALSE, "bin(full,substr)[] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == FALSE, "bin(full,substr)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == TRUE, "bin(full,substr)[SUBSTRING] match failed\n");
    pvRight.Value.bin.lpb = (LPBYTE)szSubstringLower;
    pvRight.Value.bin.cb = strlen(szSubstringLower);
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX);
    ok(bRet == FALSE, "bin(full,substrlow)[PREFIX] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING);
    ok(bRet == FALSE, "bin(full,substrlow)[SUBSTRING] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_PREFIX|FL_IGNORECASE);
    ok(bRet == FALSE, "bin(full,substrlow)[PREFIX|IGNORECASE] match failed\n");
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_SUBSTRING|FL_IGNORECASE);
    ok(bRet == FALSE, "bin(full,substrlow)[SUBSTRING|IGNORECASE] match failed\n");
    pvRight.Value.bin.lpb = (LPBYTE)szFullLower;
    pvRight.Value.bin.cb = strlen(szFullLower);
    bRet = pFPropContainsProp(&pvLeft, &pvRight, FL_FULLSTRING|FL_IGNORECASE);
    ok(bRet == FALSE, "bin(full,fulllow)[IGNORECASE] match failed\n");
}