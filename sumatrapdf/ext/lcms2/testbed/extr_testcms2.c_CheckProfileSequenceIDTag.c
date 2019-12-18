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
struct TYPE_9__ {int n; TYPE_2__* seq; } ;
typedef  TYPE_3__ cmsSEQ ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
struct TYPE_7__ {int /*<<< orphan*/  ID8; } ;
struct TYPE_8__ {int /*<<< orphan*/  Description; TYPE_1__ ProfileID; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckOneStr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  SetOneStr (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_3__* cmsAllocProfileSequenceDescription (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsFreeProfileSequenceDescription (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigProfileSequenceIdTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckProfileSequenceIDTag(cmsInt32Number Pass,  cmsHPROFILE hProfile)
{
    cmsSEQ* s;
    cmsInt32Number i;

    switch (Pass) {

    case 1:

        s = cmsAllocProfileSequenceDescription(DbgThread(), 3);
        if (s == NULL) return 0;

        memcpy(s ->seq[0].ProfileID.ID8, "0123456789ABCDEF", 16);
        memcpy(s ->seq[1].ProfileID.ID8, "1111111111111111", 16);
        memcpy(s ->seq[2].ProfileID.ID8, "2222222222222222", 16);


        SetOneStr(&s -> seq[0].Description, L"Hello, world 0", L"Hola, mundo 0");
        SetOneStr(&s -> seq[1].Description, L"Hello, world 1", L"Hola, mundo 1");
        SetOneStr(&s -> seq[2].Description, L"Hello, world 2", L"Hola, mundo 2");

        if (!cmsWriteTag(DbgThread(), hProfile, cmsSigProfileSequenceIdTag, s)) return 0;
        cmsFreeProfileSequenceDescription(DbgThread(), s);
        return 1;

    case 2:

        s = (cmsSEQ *) cmsReadTag(DbgThread(), hProfile, cmsSigProfileSequenceIdTag);
        if (s == NULL) return 0;

        if (s ->n != 3) return 0;

        if (memcmp(s ->seq[0].ProfileID.ID8, "0123456789ABCDEF", 16) != 0) return 0;
        if (memcmp(s ->seq[1].ProfileID.ID8, "1111111111111111", 16) != 0) return 0;
        if (memcmp(s ->seq[2].ProfileID.ID8, "2222222222222222", 16) != 0) return 0;

        for (i=0; i < 3; i++) {

            if (!CheckOneStr(s -> seq[i].Description, i)) return 0;
        }

        return 1;

    default:
        return 0;
    }
}