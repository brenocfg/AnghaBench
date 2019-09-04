#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n2 ;
typedef  int /*<<< orphan*/  n1 ;
typedef  int /*<<< orphan*/  attrs ;
typedef  char WCHAR ;
struct TYPE_13__ {int Length; } ;
struct TYPE_12__ {int Length; int MaximumLength; void* Buffer; } ;
struct TYPE_11__ {int Use; int Flags; int Entries; int DomainIndex; int /*<<< orphan*/  Sid; } ;
typedef  TYPE_1__* PLSA_TRANSLATED_SID2 ;
typedef  TYPE_1__* PLSA_REFERENCED_DOMAIN_LIST ;
typedef  int NTSTATUS ;
typedef  TYPE_3__ LSA_UNICODE_STRING ;
typedef  TYPE_4__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;
typedef  int LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSystemDefaultLCID () ; 
 int /*<<< orphan*/  GetThreadLocale () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  LANGIDFROMLCID (int /*<<< orphan*/ ) ; 
 scalar_t__ LANG_ENGLISH ; 
 int LsaClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaFreeMemory (TYPE_1__*) ; 
 int LsaLookupNames2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*,TYPE_1__**,TYPE_1__**) ; 
 int LsaOpenPolicy (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLICY_ALL_ACCESS ; 
 int /*<<< orphan*/  POLICY_LOOKUP_NAMES ; 
 scalar_t__ PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 int STATUS_ACCESS_DENIED ; 
 int STATUS_NONE_MAPPED ; 
 int STATUS_SOME_NOT_MAPPED ; 
 int STATUS_SUCCESS ; 
 int SidTypeUnknown ; 
 int SidTypeWellKnownGroup ; 
 int /*<<< orphan*/  get_sid_info (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmp (int,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_LsaLookupNames2(void)
{
    static const WCHAR n1[] = {'L','O','C','A','L',' ','S','E','R','V','I','C','E'};
    static const WCHAR n2[] = {'N','T',' ','A','U','T','H','O','R','I','T','Y','\\','L','o','c','a','l','S','e','r','v','i','c','e'};

    NTSTATUS status;
    LSA_HANDLE handle;
    LSA_OBJECT_ATTRIBUTES attrs;
    PLSA_REFERENCED_DOMAIN_LIST domains;
    PLSA_TRANSLATED_SID2 sids;
    LSA_UNICODE_STRING name[3];
    LPSTR account, sid_dom;

    if ((PRIMARYLANGID(LANGIDFROMLCID(GetSystemDefaultLCID())) != LANG_ENGLISH) ||
        (PRIMARYLANGID(LANGIDFROMLCID(GetThreadLocale())) != LANG_ENGLISH))
    {
        skip("Non-English locale (skipping LsaLookupNames2 tests)\n");
        return;
    }

    memset(&attrs, 0, sizeof(attrs));
    attrs.Length = sizeof(attrs);

    status = LsaOpenPolicy(NULL, &attrs, POLICY_ALL_ACCESS, &handle);
    ok(status == STATUS_SUCCESS || status == STATUS_ACCESS_DENIED,
       "LsaOpenPolicy(POLICY_ALL_ACCESS) returned 0x%08x\n", status);

    /* try a more restricted access mask if necessary */
    if (status == STATUS_ACCESS_DENIED)
    {
        trace("LsaOpenPolicy(POLICY_ALL_ACCESS) failed, trying POLICY_VIEW_LOCAL_INFORMATION\n");
        status = LsaOpenPolicy(NULL, &attrs, POLICY_LOOKUP_NAMES, &handle);
        ok(status == STATUS_SUCCESS, "LsaOpenPolicy(POLICY_VIEW_LOCAL_INFORMATION) returned 0x%08x\n", status);
    }
    if (status != STATUS_SUCCESS)
    {
        skip("Cannot acquire policy handle\n");
        return;
    }

    name[0].Buffer = HeapAlloc(GetProcessHeap(), 0, sizeof(n1));
    name[0].Length = name[0].MaximumLength = sizeof(n1);
    memcpy(name[0].Buffer, n1, sizeof(n1));

    name[1].Buffer = HeapAlloc(GetProcessHeap(), 0, sizeof(n1));
    name[1].Length = name[1].MaximumLength = sizeof(n1) - sizeof(WCHAR);
    memcpy(name[1].Buffer, n1, sizeof(n1) - sizeof(WCHAR));

    name[2].Buffer = HeapAlloc(GetProcessHeap(), 0, sizeof(n2));
    name[2].Length = name[2].MaximumLength = sizeof(n2);
    memcpy(name[2].Buffer, n2, sizeof(n2));

    /* account name only */
    sids = NULL;
    domains = NULL;
    status = LsaLookupNames2(handle, 0, 1, &name[0], &domains, &sids);
    ok(status == STATUS_SUCCESS, "expected STATUS_SUCCESS, got %x)\n", status);
    ok(sids[0].Use == SidTypeWellKnownGroup, "expected SidTypeWellKnownGroup, got %u\n", sids[0].Use);
    ok(sids[0].Flags == 0, "expected 0, got 0x%08x\n", sids[0].Flags);
    ok(domains->Entries == 1, "expected 1, got %u\n", domains->Entries);
    get_sid_info(sids[0].Sid, &account, &sid_dom);
    ok(!strcmp(account, "LOCAL SERVICE"), "expected \"LOCAL SERVICE\", got \"%s\"\n", account);
    ok(!strcmp(sid_dom, "NT AUTHORITY"), "expected \"NT AUTHORITY\", got \"%s\"\n", sid_dom);
    LsaFreeMemory(sids);
    LsaFreeMemory(domains);

    /* unknown account name */
    sids = NULL;
    domains = NULL;
    status = LsaLookupNames2(handle, 0, 1, &name[1], &domains, &sids);
    ok(status == STATUS_NONE_MAPPED, "expected STATUS_NONE_MAPPED, got %x)\n", status);
    ok(sids[0].Use == SidTypeUnknown, "expected SidTypeUnknown, got %u\n", sids[0].Use);
    ok(sids[0].Flags == 0, "expected 0, got 0x%08x\n", sids[0].Flags);
    ok(domains->Entries == 0, "expected 0, got %u\n", domains->Entries);
    LsaFreeMemory(sids);
    LsaFreeMemory(domains);

    /* account + domain */
    sids = NULL;
    domains = NULL;
    status = LsaLookupNames2(handle, 0, 1, &name[2], &domains, &sids);
    ok(status == STATUS_SUCCESS, "expected STATUS_SUCCESS, got %x)\n", status);
    ok(sids[0].Use == SidTypeWellKnownGroup, "expected SidTypeWellKnownGroup, got %u\n", sids[0].Use);
    ok(sids[0].Flags == 0, "expected 0, got 0x%08x\n", sids[0].Flags);
    ok(domains->Entries == 1, "expected 1, got %u\n", domains->Entries);
    get_sid_info(sids[0].Sid, &account, &sid_dom);
    ok(!strcmp(account, "LOCAL SERVICE"), "expected \"LOCAL SERVICE\", got \"%s\"\n", account);
    ok(!strcmp(sid_dom, "NT AUTHORITY"), "expected \"NT AUTHORITY\", got \"%s\"\n", sid_dom);
    LsaFreeMemory(sids);
    LsaFreeMemory(domains);

    /* all three */
    sids = NULL;
    domains = NULL;
    status = LsaLookupNames2(handle, 0, 3, name, &domains, &sids);
    ok(status == STATUS_SOME_NOT_MAPPED, "expected STATUS_SOME_NOT_MAPPED, got %x)\n", status);
    ok(sids[0].Use == SidTypeWellKnownGroup, "expected SidTypeWellKnownGroup, got %u\n", sids[0].Use);
    ok(sids[1].Use == SidTypeUnknown, "expected SidTypeUnknown, got %u\n", sids[1].Use);
    ok(sids[2].Use == SidTypeWellKnownGroup, "expected SidTypeWellKnownGroup, got %u\n", sids[2].Use);
    ok(sids[0].DomainIndex == 0, "expected 0, got %u\n", sids[0].DomainIndex);
    ok(domains->Entries == 1, "expected 1, got %u\n", domains->Entries);
    LsaFreeMemory(sids);
    LsaFreeMemory(domains);

    HeapFree(GetProcessHeap(), 0, name[0].Buffer);
    HeapFree(GetProcessHeap(), 0, name[1].Buffer);
    HeapFree(GetProcessHeap(), 0, name[2].Buffer);

    status = LsaClose(handle);
    ok(status == STATUS_SUCCESS, "LsaClose() failed, returned 0x%08x\n", status);
}