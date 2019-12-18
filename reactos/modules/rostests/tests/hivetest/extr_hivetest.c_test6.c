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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_3__ {scalar_t__ Type; int NameLength; int /*<<< orphan*/ * Name; int /*<<< orphan*/  DataLength; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KeyValueInformation ;
typedef  TYPE_1__ KEY_VALUE_FULL_INFORMATION ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int KEY_ALL_ACCESS ; 
 int KEY_CREATE_LINK ; 
 int /*<<< orphan*/  KeyValueFullInformation ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 scalar_t__ NtCreateKey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NtQueryValueKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 scalar_t__ NtSetValueKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int OBJ_CASE_INSENSITIVE ; 
 int OBJ_OPENIF ; 
 int OBJ_OPENLINK ; 
 scalar_t__ REG_LINK ; 
 int REG_OPTION_CREATE_LINK ; 
 int REG_OPTION_VOLATILE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RtlRosInitUnicodeStringFromLiteral (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test6(void)
{
  HANDLE hKey;
  OBJECT_ATTRIBUTES ObjectAttributes;
  UNICODE_STRING KeyName,ValueName;
  NTSTATUS Status;
  KEY_VALUE_FULL_INFORMATION KeyValueInformation[5];
  ULONG Length,i;

  dprintf("Create target key\n");
  dprintf("  Key: \\Registry\\Machine\\SOFTWARE\\Reactos\n");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\SOFTWARE\\Reactos");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, NULL, NULL);
  Status = NtCreateKey(&hKey, KEY_ALL_ACCESS , &ObjectAttributes
		,0,NULL, REG_OPTION_VOLATILE,NULL);
  dprintf("  NtCreateKey() called (Status %lx)\n",Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("Create target value\n");
  dprintf("  Value: TestValue = 'Test String'\n");
  RtlRosInitUnicodeStringFromLiteral(&ValueName, L"TestValue");
  Status=NtSetValueKey(hKey,&ValueName,0,REG_SZ,(PVOID)L"TestString",22);
  dprintf("  NtSetValueKey() called (Status %lx)\n",Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("Close target key\n");
  NtClose(hKey);


  dprintf("Create link key\n");
  dprintf("  Key: \\Registry\\Machine\\SOFTWARE\\Test\n");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\SOFTWARE\\Test");
  InitializeObjectAttributes(&ObjectAttributes,
			     &KeyName,
			     OBJ_CASE_INSENSITIVE | OBJ_OPENLINK,
			     NULL,
			     NULL);
  Status = NtCreateKey(&hKey,
		       KEY_ALL_ACCESS | KEY_CREATE_LINK,
		       &ObjectAttributes,
		       0,
		       NULL,
		       REG_OPTION_VOLATILE | REG_OPTION_CREATE_LINK,
		       NULL);
  dprintf("  NtCreateKey() called (Status %lx)\n",Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("Create link value\n");
  dprintf("  Value: SymbolicLinkValue = '\\Registry\\Machine\\SOFTWARE\\Reactos'\n");
  RtlRosInitUnicodeStringFromLiteral(&ValueName, L"SymbolicLinkValue");
  Status=NtSetValueKey(hKey,&ValueName,0,REG_LINK,(PVOID)L"\\Registry\\Machine\\SOFTWARE\\Reactos",68);
  dprintf("  NtSetValueKey() called (Status %lx)\n",Status);
  if (!NT_SUCCESS(Status))
    {
      dprintf("Creating link value failed! Test failed!\n");
      NtClose(hKey);
      return;
    }

  dprintf("Close link key\n");
  NtClose(hKey);

  dprintf("Open link key\n");
  dprintf("  Key: \\Registry\\Machine\\SOFTWARE\\Test\n");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\SOFTWARE\\Test");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE | OBJ_OPENIF
				, NULL, NULL);
  Status = NtCreateKey(&hKey, KEY_ALL_ACCESS , &ObjectAttributes
		,0,NULL, REG_OPTION_VOLATILE, NULL);
  dprintf("  NtCreateKey() called (Status %lx)\n",Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("Query value\n");
  dprintf("  Value: TestValue\n");
  RtlRosInitUnicodeStringFromLiteral(&ValueName, L"TestValue");
  Status=NtQueryValueKey(hKey,
			 &ValueName,
			 KeyValueFullInformation,
			 &KeyValueInformation[0],
			 sizeof(KeyValueInformation),
			 &Length);
  dprintf("  NtQueryValueKey() called (Status %lx)\n",Status);
  if (Status == STATUS_SUCCESS)
    {
      dprintf("  Value: Type %d  DataLength %d NameLength %d  Name '",
	      KeyValueInformation[0].Type,
	      KeyValueInformation[0].DataLength,
	      KeyValueInformation[0].NameLength);
      for (i=0; i < KeyValueInformation[0].NameLength / sizeof(WCHAR); i++)
	dprintf("%C",KeyValueInformation[0].Name[i]);
      dprintf("'\n");
      if (KeyValueInformation[0].Type == REG_SZ)
	dprintf("  Value '%S'\n",
		KeyValueInformation[0].Name+1
		+KeyValueInformation[0].NameLength/2);
    }

  dprintf("Close link key\n");
  NtClose(hKey);

  dprintf("Test successful!\n");
}