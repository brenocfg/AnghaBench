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
struct TYPE_3__ {int algID; int oid; int altOid; } ;
typedef  int /*<<< orphan*/ * LPCSTR ;

/* Variables and functions */
 int ALG_CLASS_SIGNATURE ; 
 int ALG_TYPE_ANY ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ * CertAlgIdToOID (int) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 TYPE_1__* algIDToOID ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void testAlgIDToOID(void)
{
    int i;
    LPCSTR oid;

    /* Test with a bogus one */
    SetLastError(0xdeadbeef);
    oid = CertAlgIdToOID(ALG_CLASS_SIGNATURE | ALG_TYPE_ANY | 80);
    ok(!oid && GetLastError() == 0xdeadbeef,
     "Didn't expect last error (%08x) to be set\n", GetLastError());
    for (i = 0; i < ARRAY_SIZE(algIDToOID); i++)
    {
        oid = CertAlgIdToOID(algIDToOID[i].algID);
        /* Allow failure, not every version of Windows supports every algo */
        ok(oid != NULL || broken(!oid), "CertAlgIdToOID failed, expected %s\n", algIDToOID[i].oid);
        if (oid)
        {
            if (strcmp(oid, algIDToOID[i].oid))
            {
                if (algIDToOID[i].altOid)
                    ok(!strcmp(oid, algIDToOID[i].altOid),
                     "Expected %s or %s, got %s\n", algIDToOID[i].oid,
                     algIDToOID[i].altOid, oid);
                else
                {
                    /* No need to rerun the test, we already know it failed. */
                    ok(0, "Expected %s, got %s\n", algIDToOID[i].oid, oid);
                }
            }
            else
            {
                /* No need to rerun the test, we already know it succeeded. */
                ok(1, "Expected %s, got %s\n", algIDToOID[i].oid, oid);
            }
        }
    }
}