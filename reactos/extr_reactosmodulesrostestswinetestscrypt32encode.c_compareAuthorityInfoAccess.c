#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cAccDescr; TYPE_1__* rgAccDescr; } ;
struct TYPE_5__ {int /*<<< orphan*/  AccessLocation; int /*<<< orphan*/  pszAccessMethod; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CERT_AUTHORITY_INFO_ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  compareAltNameEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,size_t,scalar_t__,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compareAuthorityInfoAccess(LPCSTR header,
 const CERT_AUTHORITY_INFO_ACCESS *expected,
 const CERT_AUTHORITY_INFO_ACCESS *got)
{
    DWORD i;

    ok(expected->cAccDescr == got->cAccDescr,
     "%s: expected %d access descriptions, got %d\n", header,
     expected->cAccDescr, got->cAccDescr);
    for (i = 0; i < expected->cAccDescr; i++)
    {
        ok(!strcmp(expected->rgAccDescr[i].pszAccessMethod,
         got->rgAccDescr[i].pszAccessMethod), "%s[%d]: expected %s, got %s\n",
         header, i, expected->rgAccDescr[i].pszAccessMethod,
         got->rgAccDescr[i].pszAccessMethod);
        compareAltNameEntry(&expected->rgAccDescr[i].AccessLocation,
         &got->rgAccDescr[i].AccessLocation);
    }
}