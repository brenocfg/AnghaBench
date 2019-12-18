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
typedef  int cmsUInt32Number ;
struct TYPE_3__ {int nEntries; int* Table16; } ;
typedef  TYPE_1__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsIT8Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsIT8Free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsIT8SaveToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cmsIT8SetDataFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  cmsIT8SetDataRowCol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  cmsIT8SetPropertyDbl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void DumpToneCurve(cmsToneCurve* gamma, const char* FileName)
{
    cmsHANDLE hIT8;
    cmsUInt32Number i;

    hIT8 = cmsIT8Alloc(DbgThread());

    cmsIT8SetPropertyDbl(DbgThread(), hIT8, "NUMBER_OF_FIELDS", 2);
    cmsIT8SetPropertyDbl(DbgThread(), hIT8, "NUMBER_OF_SETS", gamma ->nEntries);

    cmsIT8SetDataFormat(DbgThread(), hIT8, 0, "SAMPLE_ID");
    cmsIT8SetDataFormat(DbgThread(), hIT8, 1, "VALUE");

    for (i=0; i < gamma ->nEntries; i++) {
        char Val[30];

        sprintf(Val, "%u", i);
        cmsIT8SetDataRowCol(DbgThread(), hIT8, i, 0, Val);
        sprintf(Val, "0x%x", gamma ->Table16[i]);
        cmsIT8SetDataRowCol(DbgThread(), hIT8, i, 1, Val);
    }

    cmsIT8SaveToFile(DbgThread(), hIT8, FileName);
    cmsIT8Free(DbgThread(), hIT8);
}