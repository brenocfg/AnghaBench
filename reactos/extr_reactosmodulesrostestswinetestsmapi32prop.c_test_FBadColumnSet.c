#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int cValues; scalar_t__* aulPropTag; } ;
typedef  TYPE_1__ SPropTagArray ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MV_FLAG ; 
 scalar_t__ PROP_ID_INVALID ; 
 scalar_t__ PROP_TYPE_MASK ; 
#define  PT_APPTIME 143 
#define  PT_BINARY 142 
#define  PT_BOOLEAN 141 
#define  PT_CLSID 140 
#define  PT_CURRENCY 139 
 scalar_t__ PT_ERROR ; 
#define  PT_I2 138 
#define  PT_I4 137 
#define  PT_I8 136 
#define  PT_NULL 135 
#define  PT_OBJECT 134 
#define  PT_R4 133 
#define  PT_R8 132 
#define  PT_STRING8 131 
#define  PT_SYSTIME 130 
#define  PT_UNICODE 129 
#define  PT_UNSPECIFIED 128 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFBadColumnSet (TYPE_1__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FBadColumnSet(void)
{
    SPropTagArray pta;
    ULONG pt, res;

    if (!pFBadColumnSet)
    {
        win_skip("FBadColumnSet is not available\n");
        return;
    }

    res = pFBadColumnSet(NULL);
    ok(res != 0, "(null): Expected non-zero, got 0\n");

    pta.cValues = 1;

    for (pt = 0; pt < PROP_ID_INVALID; pt++)
    {
        BOOL bBad = TRUE;

        pta.aulPropTag[0] = pt;

        switch (pt & (~MV_FLAG & PROP_TYPE_MASK))
        {
        case PT_UNSPECIFIED:
        case PT_NULL:
        case PT_I2:
        case PT_I4:
        case PT_R4:
        case PT_R8:
        case PT_CURRENCY:
        case PT_APPTIME:
        case PT_BOOLEAN:
        case PT_OBJECT:
        case PT_I8:
        case PT_STRING8:
        case PT_UNICODE:
        case PT_SYSTIME:
        case PT_CLSID:
        case PT_BINARY:
            bBad = FALSE;
        }
        if (pt == (MV_FLAG|PT_ERROR))
            bBad = FALSE;

        res = pFBadColumnSet(&pta);
        if (bBad)
            ok(res != 0, "pt= %d: Expected non-zero, got 0\n", pt);
        else
            ok(res == 0,
               "pt= %d: Expected zero, got %d\n", pt, res);
    }
}