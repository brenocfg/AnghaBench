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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtFlushKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlRosInitUnicodeStringFromLiteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test5(void)
{
  HANDLE hKey;
  OBJECT_ATTRIBUTES ObjectAttributes;
  UNICODE_STRING KeyName;
  NTSTATUS Status;

  dprintf("NtOpenKey : \n");
  dprintf("  \\Registry\\Machine\\Software\\reactos : ");
  RtlRosInitUnicodeStringFromLiteral(&KeyName,L"\\Registry\\Machine\\Software\\reactos");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, NULL, NULL);
  Status=NtOpenKey( &hKey, KEY_ALL_ACCESS, &ObjectAttributes);
  dprintf("\t\tStatus=%x\n",Status);
  dprintf("NtFlushKey : \n");
  Status = NtFlushKey(hKey);
  dprintf("\t\tStatus=%x\n",Status);
  dprintf("NtCloseKey : \n");
  Status=NtClose(hKey);
  dprintf("\t\tStatus=%x\n",Status);
}