#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cRDN; int /*<<< orphan*/ * rgRDN; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CERT_NAME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  compareRDNs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void compareNames(const CERT_NAME_INFO *expected,
 const CERT_NAME_INFO *got)
{
    ok(got->cRDN == expected->cRDN, "Expected %d RDNs, got %d\n",
     expected->cRDN, got->cRDN);
    if (got->cRDN)
    {
        DWORD i;

        for (i = 0; i < got->cRDN; i++)
            compareRDNs(&expected->rgRDN[i], &got->rgRDN[i]);
    }
}