#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ObjectName; int /*<<< orphan*/ * RootDirectory; } ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  InitializeObjectAttributes (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_NOTIFY_CHANGE_NAME ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ *) ; 
 scalar_t__ pNtCreateKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtDeleteKey (int /*<<< orphan*/ *) ; 
 scalar_t__ pNtNotifyChangeKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtNotifyChangeMultipleKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ pNtWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winetestpath ; 

__attribute__((used)) static void test_notify(void)
{
    OBJECT_ATTRIBUTES attr;
    LARGE_INTEGER timeout;
    IO_STATUS_BLOCK iosb;
    UNICODE_STRING str;
    HANDLE key, events[2], subkey;
    NTSTATUS status;

    InitializeObjectAttributes(&attr, &winetestpath, 0, 0, 0);
    status = pNtOpenKey(&key, KEY_ALL_ACCESS, &attr);
    ok(status == STATUS_SUCCESS, "NtOpenKey Failed: 0x%08x\n", status);

    events[0] = CreateEventW(NULL, FALSE, TRUE, NULL);
    ok(events[0] != NULL, "CreateEvent failed: %u\n", GetLastError());
    events[1] = CreateEventW(NULL, FALSE, TRUE, NULL);
    ok(events[1] != NULL, "CreateEvent failed: %u\n", GetLastError());

    status = pNtNotifyChangeKey(key, events[0], NULL, NULL, &iosb, REG_NOTIFY_CHANGE_NAME, FALSE, NULL, 0, TRUE);
    ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);
    status = pNtNotifyChangeKey(key, events[1], NULL, NULL, &iosb, REG_NOTIFY_CHANGE_NAME, FALSE, NULL, 0, TRUE);
    ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);

    timeout.QuadPart = 0;
    status = pNtWaitForSingleObject(events[0], FALSE, &timeout);
    ok(status == STATUS_TIMEOUT, "NtWaitForSingleObject returned %x\n", status);
    status = pNtWaitForSingleObject(events[1], FALSE, &timeout);
    ok(status == STATUS_TIMEOUT, "NtWaitForSingleObject returned %x\n", status);

    attr.RootDirectory = key;
    attr.ObjectName = &str;

    pRtlCreateUnicodeStringFromAsciiz(&str, "test_subkey");
    status = pNtCreateKey(&subkey, GENERIC_ALL, &attr, 0, 0, 0, 0);
    ok(status == STATUS_SUCCESS, "NtCreateKey failed: 0x%08x\n", status);
    pRtlFreeUnicodeString(&str);

    status = pNtWaitForSingleObject(events[0], FALSE, &timeout);
    ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);
    status = pNtWaitForSingleObject(events[1], FALSE, &timeout);
    ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);

    status = pNtNotifyChangeKey(key, events[0], NULL, NULL, &iosb, 0, FALSE, NULL, 0, TRUE);
    ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);
    status = pNtNotifyChangeKey(key, events[1], NULL, NULL, &iosb, 0, FALSE, NULL, 0, TRUE);
    ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);

    status = pNtDeleteKey(subkey);
    ok(status == STATUS_SUCCESS, "NtDeleteSubkey failed: %x\n", status);

    status = pNtWaitForSingleObject(events[0], FALSE, &timeout);
    ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);
    status = pNtWaitForSingleObject(events[1], FALSE, &timeout);
    ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);

    pNtClose(subkey);

    status = pNtNotifyChangeKey(key, events[0], NULL, NULL, &iosb, 0, FALSE, NULL, 0, TRUE);
    ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);
    status = pNtNotifyChangeKey(key, events[1], NULL, NULL, &iosb, 0, FALSE, NULL, 0, TRUE);
    ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);

    pNtClose(key);

    status = pNtWaitForSingleObject(events[0], FALSE, &timeout);
    ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);
    status = pNtWaitForSingleObject(events[1], FALSE, &timeout);
    ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);

    if (pNtNotifyChangeMultipleKeys)
    {
        InitializeObjectAttributes(&attr, &winetestpath, 0, 0, 0);
        status = pNtOpenKey(&key, KEY_ALL_ACCESS, &attr);
        ok(status == STATUS_SUCCESS, "NtOpenKey Failed: 0x%08x\n", status);

        status = pNtNotifyChangeMultipleKeys(key, 0, NULL, events[0], NULL, NULL, &iosb, REG_NOTIFY_CHANGE_NAME, FALSE, NULL, 0, TRUE);
        ok(status == STATUS_PENDING, "NtNotifyChangeKey returned %x\n", status);

        timeout.QuadPart = 0;
        status = pNtWaitForSingleObject(events[0], FALSE, &timeout);
        ok(status == STATUS_TIMEOUT, "NtWaitForSingleObject returned %x\n", status);

        attr.RootDirectory = key;
        attr.ObjectName = &str;
        pRtlCreateUnicodeStringFromAsciiz(&str, "test_subkey");
        status = pNtCreateKey(&subkey, GENERIC_ALL, &attr, 0, 0, 0, 0);
        ok(status == STATUS_SUCCESS, "NtCreateKey failed: 0x%08x\n", status);
        pRtlFreeUnicodeString(&str);

        status = pNtWaitForSingleObject(events[0], FALSE, &timeout);
        ok(status == STATUS_SUCCESS, "NtWaitForSingleObject returned %x\n", status);

        status = pNtDeleteKey(subkey);
        ok(status == STATUS_SUCCESS, "NtDeleteSubkey failed: %x\n", status);
        pNtClose(subkey);
        pNtClose(key);
    }
    else
    {
        win_skip("NtNotifyChangeMultipleKeys not available\n");
    }

    pNtClose(events[0]);
    pNtClose(events[1]);
}