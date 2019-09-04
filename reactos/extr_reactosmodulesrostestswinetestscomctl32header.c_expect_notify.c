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
struct TYPE_2__ {int /*<<< orphan*/  hdItem; int /*<<< orphan*/  fUnicode; int /*<<< orphan*/  iCode; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HDITEMA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_1__* expectedNotify ; 
 int nExpectedNotify ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void expect_notify(INT iCode, BOOL fUnicode, HDITEMA *lpItem)
{
    ok(nExpectedNotify < 10, "notification count %d\n", nExpectedNotify);
    if (nExpectedNotify < 10)
    {
        expectedNotify[nExpectedNotify].iCode = iCode;
        expectedNotify[nExpectedNotify].fUnicode = fUnicode;
        expectedNotify[nExpectedNotify].hdItem = *lpItem;
        nExpectedNotify++;
    }
}