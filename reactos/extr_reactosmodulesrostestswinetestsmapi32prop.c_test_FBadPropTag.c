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
typedef  int ULONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MV_FLAG ; 
 int PROP_ID_INVALID ; 
 int PROP_TYPE_MASK ; 
#define  PT_APPTIME 144 
#define  PT_BINARY 143 
#define  PT_BOOLEAN 142 
#define  PT_CLSID 141 
#define  PT_CURRENCY 140 
#define  PT_ERROR 139 
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
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pFBadPropTag (int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FBadPropTag(void)
{
    ULONG pt, res;

    if (!pFBadPropTag)
    {
        win_skip("FBadPropTag is not available\n");
        return;
    }

    for (pt = 0; pt < PROP_ID_INVALID; pt++)
    {
        BOOL bBad = TRUE;

        switch (pt & (~MV_FLAG & PROP_TYPE_MASK))
        {
        case PT_UNSPECIFIED:
        case PT_NULL: case PT_I2: case PT_I4: case PT_R4:
        case PT_R8: case PT_CURRENCY: case PT_APPTIME:
        case PT_ERROR: case PT_BOOLEAN: case PT_OBJECT:
        case PT_I8: case PT_STRING8: case PT_UNICODE:
        case PT_SYSTIME: case PT_CLSID: case PT_BINARY:
            bBad = FALSE;
        }

        res = pFBadPropTag(pt);
        if (bBad)
            ok(res != 0, "pt= %d: Expected non-zero, got 0\n", pt);
        else
            ok(res == 0,
               "pt= %d: Expected zero, got %d\n", pt, res);
    }
}