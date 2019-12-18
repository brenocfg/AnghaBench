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
struct TYPE_3__ {char* oid; scalar_t__ algID; scalar_t__ altAlgID; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CertOIDToAlgId (char*) ; 
 TYPE_1__* oidToAlgID ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void testOIDToAlgID(void)
{
    int i;
    DWORD alg;

    /* Test with a bogus one */
    alg = CertOIDToAlgId("1.2.3");
    ok(!alg, "Expected failure, got %d\n", alg);

    for (i = 0; i < ARRAY_SIZE(oidToAlgID); i++)
    {
        alg = CertOIDToAlgId(oidToAlgID[i].oid);
        ok(alg == oidToAlgID[i].algID || (oidToAlgID[i].altAlgID && alg == oidToAlgID[i].altAlgID),
         "Expected %d, got %d\n", oidToAlgID[i].algID, alg);
    }
}