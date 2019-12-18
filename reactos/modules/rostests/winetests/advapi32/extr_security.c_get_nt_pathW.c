#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ANSI_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pRtlAnsiStringToUnicodeString (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlDosPathNameToNtPathName_U (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  pRtlInitAnsiString (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void get_nt_pathW(const char *name, UNICODE_STRING *nameW)
{
    UNICODE_STRING strW;
    ANSI_STRING str;
    NTSTATUS status;
    BOOLEAN ret;

    pRtlInitAnsiString(&str, name);

    status = pRtlAnsiStringToUnicodeString(&strW, &str, TRUE);
    ok(!status, "RtlAnsiStringToUnicodeString failed with %08x\n", status);

    ret = pRtlDosPathNameToNtPathName_U(strW.Buffer, nameW, NULL, NULL);
    ok(ret, "RtlDosPathNameToNtPathName_U failed\n");

    pRtlFreeUnicodeString(&strW);
}