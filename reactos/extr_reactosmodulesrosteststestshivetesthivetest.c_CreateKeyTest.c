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
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void CreateKeyTest(void)
{
  HANDLE hKey;
  OBJECT_ATTRIBUTES ObjectAttributes;
  NTSTATUS Status;
  UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\Software\\testkey");

  dprintf("Create key '\\Registry\\Machine\\Software\\testkey':\n");

  InitializeObjectAttributes(&ObjectAttributes,
			     &KeyName,
			     OBJ_CASE_INSENSITIVE,
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
  if (NT_SUCCESS(Status))
    {
      NtClose(hKey);
    }
}