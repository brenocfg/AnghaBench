#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  attrs ;
struct TYPE_21__ {int Length; } ;
struct TYPE_20__ {int Entries; TYPE_3__* Domains; } ;
struct TYPE_16__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_19__ {TYPE_1__ User; } ;
struct TYPE_17__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  Length; int /*<<< orphan*/  MaximumLength; } ;
struct TYPE_18__ {TYPE_2__ Name; scalar_t__ Sid; } ;
typedef  TYPE_4__ TOKEN_USER ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int NTSTATUS ;
typedef  TYPE_5__ LSA_TRANSLATED_NAME ;
typedef  TYPE_5__ LSA_REFERENCED_DOMAIN_LIST ;
typedef  TYPE_7__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int ConvertStringSidToSidA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int LsaClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaFreeMemory (TYPE_5__*) ; 
 int LsaLookupSids (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_5__**,TYPE_5__**) ; 
 int LsaOpenPolicy (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLICY_LOOKUP_NAMES ; 
 int STATUS_SUCCESS ; 
 int TRUE ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_LsaLookupSids(void)
{
    LSA_REFERENCED_DOMAIN_LIST *list;
    LSA_OBJECT_ATTRIBUTES attrs;
    LSA_TRANSLATED_NAME *names;
    LSA_HANDLE policy;
    TOKEN_USER *user;
    NTSTATUS status;
    HANDLE token;
    DWORD size;
    BOOL ret;
    PSID sid;

    memset(&attrs, 0, sizeof(attrs));
    attrs.Length = sizeof(attrs);

    status = LsaOpenPolicy(NULL, &attrs, POLICY_LOOKUP_NAMES, &policy);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);

    ret = OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &token);
    ok(ret, "got %d\n", ret);

    ret = GetTokenInformation(token, TokenUser, NULL, 0, &size);
    ok(!ret, "got %d\n", ret);

    user = HeapAlloc(GetProcessHeap(), 0, size);
    ret = GetTokenInformation(token, TokenUser, user, size, &size);
    ok(ret, "got %d\n", ret);

    status = LsaLookupSids(policy, 1, &user->User.Sid, &list, &names);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);

    ok(list->Entries > 0, "got %d\n", list->Entries);
    if (list->Entries)
    {
       ok((char*)list->Domains - (char*)list > 0, "%p, %p\n", list, list->Domains);
       ok((char*)list->Domains[0].Sid - (char*)list->Domains > 0, "%p, %p\n", list->Domains, list->Domains[0].Sid);
       ok(list->Domains[0].Name.MaximumLength > list->Domains[0].Name.Length, "got %d, %d\n", list->Domains[0].Name.MaximumLength,
           list->Domains[0].Name.Length);
    }

    LsaFreeMemory(names);
    LsaFreeMemory(list);

    HeapFree(GetProcessHeap(), 0, user);

    CloseHandle(token);

    ret = ConvertStringSidToSidA("S-1-1-0", &sid);
    ok(ret == TRUE, "ConvertStringSidToSidA returned false\n");

    status = LsaLookupSids(policy, 1, &sid, &list, &names);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);

    ok(list->Entries > 0, "got %d\n", list->Entries);

    if (list->Entries)
    {
       ok((char*)list->Domains - (char*)list > 0, "%p, %p\n", list, list->Domains);
       ok((char*)list->Domains[0].Sid - (char*)list->Domains > 0, "%p, %p\n", list->Domains, list->Domains[0].Sid);
       ok(list->Domains[0].Name.MaximumLength > list->Domains[0].Name.Length, "got %d, %d\n", list->Domains[0].Name.MaximumLength,
           list->Domains[0].Name.Length);
       ok(list->Domains[0].Name.Buffer != NULL, "domain[0] name buffer is null\n");
    }

    LsaFreeMemory(names);
    LsaFreeMemory(list);

    FreeSid(sid);

    status = LsaClose(policy);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);
}