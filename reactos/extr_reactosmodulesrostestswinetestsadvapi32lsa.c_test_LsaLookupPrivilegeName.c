#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  attrs ;
struct TYPE_7__ {int Length; } ;
struct TYPE_6__ {int HighPart; void* LowPart; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ LUID ;
typedef  void LSA_UNICODE_STRING ;
typedef  TYPE_2__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  LsaFreeMemory (void*) ; 
 scalar_t__ LsaLookupPrivilegeName (int /*<<< orphan*/ ,TYPE_1__*,void**) ; 
 scalar_t__ LsaOpenPolicy (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLICY_LOOKUP_NAMES ; 
 void* SE_CREATE_TOKEN_PRIVILEGE ; 
 scalar_t__ STATUS_NO_SUCH_PRIVILEGE ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_LsaLookupPrivilegeName(void)
{
    LSA_OBJECT_ATTRIBUTES attrs;
    LSA_UNICODE_STRING *name;
    LSA_HANDLE policy;
    NTSTATUS status;
    LUID luid;

    memset(&attrs, 0, sizeof(attrs));
    attrs.Length = sizeof(attrs);

    status = LsaOpenPolicy(NULL, &attrs, POLICY_LOOKUP_NAMES, &policy);
    ok(status == STATUS_SUCCESS, "Failed to open policy, %#x.\n", status);

    name = (void *)0xdeadbeef;
    status = LsaLookupPrivilegeName(policy, NULL, &name);
    ok(status != STATUS_SUCCESS, "Unexpected status %#x.\n", status);
    ok(name == (void *)0xdeadbeef, "Unexpected name pointer.\n");

    name = (void *)0xdeadbeef;
    luid.HighPart = 1;
    luid.LowPart = SE_CREATE_TOKEN_PRIVILEGE;
    status = LsaLookupPrivilegeName(policy, &luid, &name);
    ok(status == STATUS_NO_SUCH_PRIVILEGE, "Unexpected status %#x.\n", status);
    ok(name == NULL, "Unexpected name pointer.\n");

    luid.HighPart = 0;
    luid.LowPart = SE_CREATE_TOKEN_PRIVILEGE;
    status = LsaLookupPrivilegeName(policy, &luid, &name);
    ok(status == 0, "got %#x.\n", status);
    LsaFreeMemory(name);
}