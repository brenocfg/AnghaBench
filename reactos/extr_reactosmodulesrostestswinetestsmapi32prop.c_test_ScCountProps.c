#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pv ;
typedef  char WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_30__ {int cValues; int /*<<< orphan*/ * lpft; } ;
struct TYPE_29__ {int cValues; int /*<<< orphan*/ * lpcur; } ;
struct TYPE_28__ {int cValues; double* lpdbl; } ;
struct TYPE_27__ {int cValues; float* lpflt; } ;
struct TYPE_26__ {int cValues; int /*<<< orphan*/ * lpli; } ;
struct TYPE_25__ {int cValues; int /*<<< orphan*/ * lpl; } ;
struct TYPE_24__ {int cValues; int /*<<< orphan*/ * lpi; } ;
struct TYPE_23__ {int cb; void* lpb; } ;
struct TYPE_22__ {int cValues; TYPE_14__* lpbin; } ;
struct TYPE_21__ {int cb; void* lpb; } ;
struct TYPE_18__ {int cValues; char** lppszW; } ;
struct TYPE_17__ {int cValues; char** lppszA; } ;
struct TYPE_19__ {char* lpszA; char* lpszW; TYPE_1__ MVbin; TYPE_11__ MVszW; TYPE_10__ MVszA; TYPE_9__ MVft; TYPE_8__ MVcur; TYPE_7__ MVdbl; TYPE_6__ MVflt; TYPE_5__ MVli; TYPE_4__ MVl; TYPE_3__ MVi; TYPE_2__ bin; int /*<<< orphan*/ * lpguid; } ;
struct TYPE_20__ {TYPE_12__ Value; int /*<<< orphan*/  ulPropTag; } ;
typedef  TYPE_13__ SPropValue ;
typedef  int /*<<< orphan*/  SHORT ;
typedef  int /*<<< orphan*/  SCODE ;
typedef  TYPE_14__ SBinary ;
typedef  char* LPWSTR ;
typedef  char* LPSTR ;
typedef  void* LPBYTE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int /*<<< orphan*/  CY ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  MAPI_E_INVALID_PARAMETER ; 
 scalar_t__ PROP_ID_INVALID ; 
 int /*<<< orphan*/  PROP_TAG (scalar_t__,unsigned int) ; 
 int PROP_TYPE (scalar_t__) ; 
#define  PT_APPTIME 153 
#define  PT_BINARY 152 
#define  PT_BOOLEAN 151 
#define  PT_CLSID 150 
#define  PT_CURRENCY 149 
#define  PT_ERROR 148 
#define  PT_I2 147 
#define  PT_I4 146 
#define  PT_I8 145 
#define  PT_MV_APPTIME 144 
#define  PT_MV_BINARY 143 
#define  PT_MV_CURRENCY 142 
#define  PT_MV_I2 141 
#define  PT_MV_I4 140 
#define  PT_MV_I8 139 
#define  PT_MV_R4 138 
#define  PT_MV_R8 137 
#define  PT_MV_STRING8 136 
#define  PT_MV_SYSTIME 135 
#define  PT_MV_UNICODE 134 
#define  PT_OBJECT 133 
#define  PT_R4 132 
#define  PT_R8 131 
#define  PT_STRING8 130 
#define  PT_SYSTIME 129 
#define  PT_UNICODE 128 
 int /*<<< orphan*/  S_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  memset (TYPE_13__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  pScCountProps (int,TYPE_13__*,scalar_t__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_ScCountProps(void)
{
    static char szHiA[] = "Hi!";
    static WCHAR szHiW[] = { 'H', 'i', '!', '\0' };
    static const ULONG ULHILEN = 4; /* chars in szHiA/W incl. NUL */
    LPSTR  buffa[3];
    LPWSTR buffw[3];
    SBinary buffbin[3];
    GUID iids[4], *iid = iids;
    SCODE res;
    ULONG pt, exp, ulRet;
    BOOL success = TRUE;

    if (!pScCountProps)
    {
        win_skip("ScCountProps is not available\n");
        return;
    }

    for (pt = 0; pt < PROP_ID_INVALID && success; pt++)
    {
        SPropValue pv;

        memset(&pv, 0 ,sizeof(pv));
        pv.ulPropTag = PROP_TAG(pt, 1u);

        switch (PROP_TYPE(pt))
        {
        case PT_I2:
        case PT_I4:
        case PT_R4:
        case PT_R8:
        case PT_CURRENCY:
        case PT_APPTIME:
        case PT_SYSTIME:
        case PT_ERROR:
        case PT_BOOLEAN:
        case PT_OBJECT:
        case PT_I8:
            exp = sizeof(pv);
            break;
        case PT_CLSID:
            pv.Value.lpguid = iid;
            exp = sizeof(GUID) + sizeof(pv);
            break;
        case PT_STRING8:
            pv.Value.lpszA = szHiA;
            exp = 4 + sizeof(pv);
            break;
        case PT_UNICODE:
            pv.Value.lpszW = szHiW;
            exp = 4 * sizeof(WCHAR) + sizeof(pv);
            break;
        case PT_BINARY:
            pv.Value.bin.cb = 2;
            pv.Value.bin.lpb = (LPBYTE)iid;
            exp = 2 + sizeof(pv);
            break;
        case PT_MV_I2:
            pv.Value.MVi.cValues = 3;
            pv.Value.MVi.lpi = (SHORT*)iid;
            exp = 3 * sizeof(SHORT) + sizeof(pv);
            break;
        case PT_MV_I4:
            pv.Value.MVl.cValues = 3;
            pv.Value.MVl.lpl = (LONG*)iid;
            exp = 3 * sizeof(LONG) + sizeof(pv);
            break;
        case PT_MV_I8:
            pv.Value.MVli.cValues = 3;
            pv.Value.MVli.lpli = (LARGE_INTEGER*)iid;
            exp = 3 * sizeof(LARGE_INTEGER) + sizeof(pv);
            break;
        case PT_MV_R4:
            pv.Value.MVflt.cValues = 3;
            pv.Value.MVflt.lpflt = (float*)iid;
            exp = 3 * sizeof(float) + sizeof(pv);
            break;
        case PT_MV_APPTIME:
        case PT_MV_R8:
            pv.Value.MVdbl.cValues = 3;
            pv.Value.MVdbl.lpdbl = (double*)iid;
            exp = 3 * sizeof(double) + sizeof(pv);
            break;
        case PT_MV_CURRENCY:
            pv.Value.MVcur.cValues = 3;
            pv.Value.MVcur.lpcur = (CY*)iid;
            exp = 3 * sizeof(CY) + sizeof(pv);
            break;
        case PT_MV_SYSTIME:
            pv.Value.MVft.cValues = 3;
            pv.Value.MVft.lpft = (FILETIME*)iid;
            exp = 3 * sizeof(CY) + sizeof(pv);
            break;
        case PT_MV_STRING8:
            pv.Value.MVszA.cValues = 3;
            pv.Value.MVszA.lppszA = buffa;
            buffa[0] = szHiA;
            buffa[1] = szHiA;
            buffa[2] = szHiA;
            exp = ULHILEN * 3 + 3 * sizeof(char*) + sizeof(pv);
            break;
        case PT_MV_UNICODE:
            pv.Value.MVszW.cValues = 3;
            pv.Value.MVszW.lppszW = buffw;
            buffw[0] = szHiW;
            buffw[1] = szHiW;
            buffw[2] = szHiW;
            exp = ULHILEN * 3 * sizeof(WCHAR) + 3 * sizeof(WCHAR*) + sizeof(pv);
            break;
        case PT_MV_BINARY:
            pv.Value.MVbin.cValues = 3;
            pv.Value.MVbin.lpbin = buffbin;
            buffbin[0].cb = 17;
            buffbin[0].lpb = (LPBYTE)&iid;
            buffbin[1].cb = 2;
            buffbin[1].lpb = (LPBYTE)&iid;
            buffbin[2].cb = 1;
            buffbin[2].lpb = (LPBYTE)&iid;
            exp = 20 + sizeof(pv) + sizeof(SBinary) * 3;
            break;
        default:
            exp = 0;
        }

        ulRet = 0xffffffff;
        res = pScCountProps(1, &pv, &ulRet);
        if (!exp) {
            success = res == MAPI_E_INVALID_PARAMETER && ulRet == 0xffffffff;
            ok(success, "pt= %d: Expected failure, got %d, ret=0x%08X\n",
               pt, ulRet, res);
        }
        else {
            success = res == S_OK && ulRet == exp;
            ok(success, "pt= %d: Expected %d, got %d, ret=0x%08X\n",
               pt, exp, ulRet, res);
        }
    }

}