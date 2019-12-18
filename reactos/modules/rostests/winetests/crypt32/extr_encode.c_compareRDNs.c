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
struct TYPE_4__ {scalar_t__ cRDNAttr; int /*<<< orphan*/ * rgRDNAttr; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CERT_RDN ;

/* Variables and functions */
 int /*<<< orphan*/  compareRDNAttrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void compareRDNs(const CERT_RDN *expected, const CERT_RDN *got)
{
    ok(got->cRDNAttr == expected->cRDNAttr,
     "Expected %d RDN attrs, got %d\n", expected->cRDNAttr, got->cRDNAttr);
    if (got->cRDNAttr)
    {
        DWORD i;

        for (i = 0; i < got->cRDNAttr; i++)
            compareRDNAttrs(&expected->rgRDNAttr[i], &got->rgRDNAttr[i]);
    }
}