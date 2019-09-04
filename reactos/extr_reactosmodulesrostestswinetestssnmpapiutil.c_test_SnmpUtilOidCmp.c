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
typedef  int UINT ;
struct TYPE_4__ {int member_0; int* member_1; } ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ AsnObjectIdentifier ;

/* Variables and functions */
 scalar_t__ SnmpUtilOidCmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_SnmpUtilOidCmp(void)
{
    INT ret;
    static UINT ids1[] = { 1, 2, 3 };
    static UINT ids2[] = { 1, 2, 3, 4 };
    static AsnObjectIdentifier oid1 = { 3, ids1 };
    static AsnObjectIdentifier oid2 = { 4, ids2 };

    if (0) { /* these crash on XP */
    ret = SnmpUtilOidCmp(NULL, NULL);
    ok(!ret, "SnmpUtilOidCmp succeeded\n");

    ret = SnmpUtilOidCmp(&oid1, NULL);
    ok(!ret, "SnmpUtilOidCmp succeeded\n");

    ret = SnmpUtilOidCmp(NULL, &oid2);
    ok(!ret, "SnmpUtilOidCmp succeeded\n");
    }

    ret = SnmpUtilOidCmp(&oid2, &oid1);
    ok(ret > 0, "SnmpUtilOidCmp failed\n");

    ret = SnmpUtilOidCmp(&oid1, &oid2);
    ok(ret < 0, "SnmpUtilOidCmp failed\n");
}