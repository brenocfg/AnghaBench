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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  AsnObjectIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SnmpUtilOidFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SnmpUtilOidToA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int pSnmpExtensionInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void testInit(void)
{
    BOOL ret;
    HANDLE event;
    AsnObjectIdentifier oid;

    if (!pSnmpExtensionInit)
    {
        win_skip("no SnmpExtensionInit\n");
        return;
    }

if (0) /* crashes on native */
{
    ret = pSnmpExtensionInit(0, NULL, NULL);
    ret = pSnmpExtensionInit(0, NULL, &oid);
    ret = pSnmpExtensionInit(0, &event, NULL);
}

    ret = pSnmpExtensionInit(0, &event, &oid);
    ok(ret, "SnmpExtensionInit failed: %d\n", GetLastError());
    ok(!strcmp("1.3.6.1.2.1.1", SnmpUtilOidToA(&oid)),
        "Expected 1.3.6.1.2.1.1, got %s\n", SnmpUtilOidToA(&oid));


if (0)
{
    /* Fails when called on win8, documentation suggests that
       extension itself is responsible for freeing this oid */
    SnmpUtilOidFree(&oid);
}
}