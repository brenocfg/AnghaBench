#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pv ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ ULONG ;
struct TYPE_34__ {scalar_t__ cValues; } ;
struct TYPE_33__ {scalar_t__ cValues; } ;
struct TYPE_32__ {scalar_t__ cValues; } ;
struct TYPE_31__ {scalar_t__ cValues; } ;
struct TYPE_30__ {scalar_t__ cValues; } ;
struct TYPE_29__ {scalar_t__ cValues; } ;
struct TYPE_28__ {scalar_t__ cValues; } ;
struct TYPE_27__ {scalar_t__ cValues; } ;
struct TYPE_26__ {scalar_t__ cValues; } ;
struct TYPE_25__ {int cb; } ;
struct TYPE_22__ {int cValues; TYPE_16__* lpbin; } ;
struct TYPE_21__ {int cValues; char** lppszW; } ;
struct TYPE_20__ {int cValues; char** lppszA; } ;
struct TYPE_19__ {scalar_t__ cb; } ;
struct TYPE_23__ {char* lpszA; char* lpszW; TYPE_13__ MVbin; TYPE_12__ MVszW; TYPE_11__ MVszA; TYPE_10__ bin; TYPE_9__ MVguid; TYPE_8__ MVli; TYPE_7__ MVft; TYPE_6__ MVat; TYPE_5__ MVcur; TYPE_4__ MVdbl; TYPE_3__ MVflt; TYPE_2__ MVl; TYPE_1__ MVi; } ;
struct TYPE_24__ {TYPE_14__ Value; scalar_t__ ulPropTag; } ;
typedef  TYPE_15__ SPropValue ;
typedef  int /*<<< orphan*/  SCODE ;
typedef  TYPE_16__ SBinary ;
typedef  char* LPWSTR ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LONG64 ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int /*<<< orphan*/  CY ;

/* Variables and functions */
 scalar_t__ PROP_ID_INVALID ; 
 int PROP_TYPE (scalar_t__) ; 
#define  PT_APPTIME 154 
#define  PT_BINARY 153 
#define  PT_BOOLEAN 152 
#define  PT_CLSID 151 
#define  PT_CURRENCY 150 
#define  PT_ERROR 149 
#define  PT_I2 148 
#define  PT_I4 147 
#define  PT_I8 146 
#define  PT_MV_APPTIME 145 
#define  PT_MV_BINARY 144 
#define  PT_MV_CLSID 143 
#define  PT_MV_CURRENCY 142 
#define  PT_MV_DOUBLE 141 
#define  PT_MV_I2 140 
#define  PT_MV_I4 139 
#define  PT_MV_I8 138 
#define  PT_MV_R4 137 
#define  PT_MV_STRING8 136 
#define  PT_MV_SYSTIME 135 
#define  PT_MV_UNICODE 134 
#define  PT_OBJECT 133 
#define  PT_R4 132 
#define  PT_R8 131 
#define  PT_STRING8 130 
#define  PT_SYSTIME 129 
#define  PT_UNICODE 128 
 int /*<<< orphan*/  memset (TYPE_15__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ pUlPropSize (TYPE_15__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UlPropSize(void)
{
    static char szHiA[] = "Hi!";
    static WCHAR szHiW[] = { 'H', 'i', '!', '\0' };
    LPSTR  buffa[2];
    LPWSTR buffw[2];
    SBinary buffbin[2];
    ULONG pt, exp, res;

    if (!pUlPropSize)
    {
        win_skip("UlPropSize is not available\n");
        return;
    }

    for (pt = 0; pt < PROP_ID_INVALID; pt++)
    {
        SPropValue pv;

        memset(&pv, 0 ,sizeof(pv));
        pv.ulPropTag = pt;

        exp = 1u; /* Default to one item for non-MV properties */

        switch (PROP_TYPE(pt))
        {
        case PT_MV_I2:       pv.Value.MVi.cValues = exp = 2;
        case PT_I2:          exp *= sizeof(USHORT); break;
        case PT_MV_I4:       pv.Value.MVl.cValues = exp = 2;
        case PT_I4:          exp *= sizeof(LONG); break;
        case PT_MV_R4:       pv.Value.MVflt.cValues = exp = 2;
        case PT_R4:          exp *= sizeof(float); break;
        case PT_MV_DOUBLE:   pv.Value.MVdbl.cValues = exp = 2;
        case PT_R8:          exp *= sizeof(double); break;
        case PT_MV_CURRENCY: pv.Value.MVcur.cValues = exp = 2;
        case PT_CURRENCY:    exp *= sizeof(CY); break;
        case PT_MV_APPTIME:  pv.Value.MVat.cValues = exp = 2;
        case PT_APPTIME:     exp *= sizeof(double); break;
        case PT_MV_SYSTIME:  pv.Value.MVft.cValues = exp = 2;
        case PT_SYSTIME:     exp *= sizeof(FILETIME); break;
        case PT_ERROR:       exp = sizeof(SCODE); break;
        case PT_BOOLEAN:     exp = sizeof(USHORT); break;
        case PT_OBJECT:      exp = 0; break;
        case PT_MV_I8:       pv.Value.MVli.cValues = exp = 2;
        case PT_I8:          exp *= sizeof(LONG64); break;
#if 0
        /* My version of native mapi returns 0 for PT_MV_CLSID even if a valid
         * array is given. This _has_ to be a bug, so Wine does
         * the right thing(tm) and we don't test it here.
         */
        case PT_MV_CLSID:    pv.Value.MVguid.cValues = exp = 2;
#endif
        case PT_CLSID:       exp *= sizeof(GUID); break;
        case PT_STRING8:
            pv.Value.lpszA = szHiA;
            exp = 4;
            break;
        case PT_UNICODE:
            pv.Value.lpszW = szHiW;
            exp = 4 * sizeof(WCHAR);
            break;
        case PT_BINARY:
            pv.Value.bin.cb = exp = 19;
            break;
        case PT_MV_STRING8:
            pv.Value.MVszA.cValues = 2;
            pv.Value.MVszA.lppszA = buffa;
            buffa[0] = szHiA;
            buffa[1] = szHiA;
            exp = 8;
            break;
        case PT_MV_UNICODE:
            pv.Value.MVszW.cValues = 2;
            pv.Value.MVszW.lppszW = buffw;
            buffw[0] = szHiW;
            buffw[1] = szHiW;
            exp = 8 * sizeof(WCHAR);
            break;
        case PT_MV_BINARY:
            pv.Value.MVbin.cValues = 2;
            pv.Value.MVbin.lpbin = buffbin;
            buffbin[0].cb = 19;
            buffbin[1].cb = 1;
            exp = 20;
            break;
        default:
            exp = 0;
        }

        res = pUlPropSize(&pv);
        ok(res == exp,
           "pt= %d: Expected %d, got %d\n", pt, exp, res);
    }
}