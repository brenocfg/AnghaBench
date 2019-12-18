#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int cmsInt32Number ;
struct TYPE_4__ {char member_0; } ;
struct TYPE_5__ {int member_0; char* data; int len; int /*<<< orphan*/  flag; TYPE_1__ member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ cmsICCData ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static
cmsInt32Number CheckData(cmsInt32Number Pass,  cmsHPROFILE hProfile, cmsTagSignature tag)
{
    cmsICCData *Pt;
    cmsICCData d = { 1, 0, { '?' }};
    cmsInt32Number rc;


    switch (Pass) {

        case 1:
            rc = cmsWriteTag(DbgThread(), hProfile, tag, &d);
            return rc;

        case 2:
            Pt = (cmsICCData *) cmsReadTag(DbgThread(), hProfile, tag);
            if (Pt == NULL) return 0;
            return (Pt ->data[0] == '?') && (Pt ->flag == 0) && (Pt ->len == 1);

        default:
            return 0;
    }
}