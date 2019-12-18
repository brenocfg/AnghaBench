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
typedef  int /*<<< orphan*/  info ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_3__ {int EventType; scalar_t__ EventState; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ EVENT_BASIC_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  EventBasicInformation ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtCreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtOpenEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtPulseEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtQueryEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlInitUnicodeString (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_event(void)
{
    HANDLE Event;
    HANDLE Event2;
    NTSTATUS status;
    UNICODE_STRING str;
    OBJECT_ATTRIBUTES attr;
    EVENT_BASIC_INFORMATION info;
    static const WCHAR eventName[] = {'\\','B','a','s','e','N','a','m','e','d','O','b','j','e','c','t','s','\\','t','e','s','t','E','v','e','n','t',0};

    pRtlInitUnicodeString(&str, eventName);
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);

    status = pNtCreateEvent(&Event, GENERIC_ALL, &attr, 1, 0);
    ok( status == STATUS_SUCCESS, "NtCreateEvent failed %08x\n", status );

    status = pNtPulseEvent(Event, NULL);
    ok( status == STATUS_SUCCESS, "NtPulseEvent failed %08x\n", status );

    status = pNtQueryEvent(Event, EventBasicInformation, &info, sizeof(info), NULL);
    ok( status == STATUS_SUCCESS, "NtQueryEvent failed %08x\n", status );
    ok( info.EventType == 1 && info.EventState == 0,
        "NtQueryEvent failed, expected 1 0, got %d %d\n", info.EventType, info.EventState );

    status = pNtOpenEvent(&Event2, GENERIC_ALL, &attr);
    ok( status == STATUS_SUCCESS, "NtOpenEvent failed %08x\n", status );

    pNtClose(Event);

    status = pNtQueryEvent(Event2, EventBasicInformation, &info, sizeof(info), NULL);
    ok( status == STATUS_SUCCESS, "NtQueryEvent failed %08x\n", status );
    ok( info.EventType == 1 && info.EventState == 0,
        "NtQueryEvent failed, expected 1 0, got %d %d\n", info.EventType, info.EventState );

    pNtClose(Event2);
}