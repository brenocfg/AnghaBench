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
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtDeleteKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeleteValueKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int OBJ_CASE_INSENSITIVE ; 
 int OBJ_OPENIF ; 
 int OBJ_OPENLINK ; 
 int REG_OPTION_OPEN_LINK ; 
 int REG_OPTION_VOLATILE ; 
 int /*<<< orphan*/  RtlRosInitUnicodeStringFromLiteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test7(void)
{
  HKEY hKey;
  OBJECT_ATTRIBUTES ObjectAttributes;
  UNICODE_STRING KeyName,ValueName;
  NTSTATUS Status;

  dprintf("Open link key\n");
  dprintf("  Key: \\Registry\\Machine\\SOFTWARE\\Test\n");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\SOFTWARE\\Test");
  InitializeObjectAttributes(&ObjectAttributes,
			     &KeyName,
			     OBJ_CASE_INSENSITIVE | OBJ_OPENIF | OBJ_OPENLINK,
			     NULL,
			     NULL);
  Status = NtCreateKey(&hKey,
		       KEY_ALL_ACCESS,
		       &ObjectAttributes,
		       0,
		       NULL,
		       REG_OPTION_VOLATILE | REG_OPTION_OPEN_LINK,
		       NULL);
  dprintf("  NtCreateKey() called (Status %lx)\n",Status);
  if (!NT_SUCCESS(Status))
    {
      dprintf("Could not open the link key. Please run the link create test first!\n");
      return;
    }

  dprintf("Delete link value\n");
  RtlRosInitUnicodeStringFromLiteral(&ValueName, L"SymbolicLinkValue");
  Status = NtDeleteValueKey(hKey,
			    &ValueName);
  dprintf("  NtDeleteValueKey() called (Status %lx)\n",Status);

  dprintf("Delete link key\n");
  Status=NtDeleteKey(hKey);
  dprintf("  NtDeleteKey() called (Status %lx)\n",Status);

  dprintf("Close link key\n");
  NtClose(hKey);
}