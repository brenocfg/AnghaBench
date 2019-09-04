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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtSetValueKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int OBJ_CASE_INSENSITIVE ; 
 int OBJ_OPENIF ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void SetValueTest2(void)
{
  HANDLE hKey;
  OBJECT_ATTRIBUTES ObjectAttributes;
  UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\Software\\testkey");
  UNICODE_STRING ValueName = RTL_CONSTANT_STRING(L"TestValue");
  NTSTATUS Status;

  dprintf("Create key '\\Registry\\Machine\\Software\\testkey':\n");

  InitializeObjectAttributes(&ObjectAttributes,
			     &KeyName,
			     OBJ_CASE_INSENSITIVE | OBJ_OPENIF,
			     NULL,
			     NULL);
  dprintf("NtCreateKey:\n");
  Status = NtCreateKey(&hKey,
		       KEY_ALL_ACCESS,
		       &ObjectAttributes,
		       0,
		       NULL,
		       REG_OPTION_NON_VOLATILE,
		       NULL);
  dprintf("  Status = %lx\n",Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("NtSetValueKey:\n");
  Status = NtSetValueKey(hKey,
			 &ValueName,
			 0,
			 REG_DWORD,
			 (PVOID)"reac",
			 4);
  dprintf("  Status = %lx\n",Status);

  NtClose(hKey);
}