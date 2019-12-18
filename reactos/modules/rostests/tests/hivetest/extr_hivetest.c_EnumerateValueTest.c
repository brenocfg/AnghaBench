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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_3__ {int DataOffset; int NameLength; char** Name; char* Type; int /*<<< orphan*/  DataLength; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  char* NTSTATUS ;
typedef  int /*<<< orphan*/  KeyValueInformation ;
typedef  TYPE_1__ KEY_VALUE_FULL_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeyValueFullInformation ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  NT_SUCCESS (char*) ; 
 char* NtClose (int /*<<< orphan*/ *) ; 
 char* NtEnumerateValueKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 char* NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 char* STATUS_SUCCESS ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void EnumerateValueTest(void)
{
  KEY_VALUE_FULL_INFORMATION KeyValueInformation[5];
  OBJECT_ATTRIBUTES ObjectAttributes;
  UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\Software\\testkey");
  ULONG Index,Length,i;
  HANDLE hKey = NULL;
  NTSTATUS Status;

  dprintf("Open key '\\Registry\\Machine\\Software\\testkey':\n");

  InitializeObjectAttributes(&ObjectAttributes,
			     &KeyName,
			     OBJ_CASE_INSENSITIVE,
			     NULL,
			     NULL);
  Status=NtOpenKey(&hKey,
		   MAXIMUM_ALLOWED,
		   &ObjectAttributes);
  dprintf("  Status = %lx\n", Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("Enumerate values:\n");
  Index = 0;
  while (Status == STATUS_SUCCESS)
    {
      Status = NtEnumerateValueKey(hKey,
				   Index++,
				   KeyValueFullInformation,
				   &KeyValueInformation[0],
				   sizeof(KeyValueInformation),
				   &Length);
      if (Status == STATUS_SUCCESS)
	{
	  dprintf("    Value:DO=%d, DL=%d, NL=%d, Name = ",
		  KeyValueInformation[0].DataOffset,
		  KeyValueInformation[0].DataLength,
		  KeyValueInformation[0].NameLength);
	  for (i = 0; i < KeyValueInformation[0].NameLength / 2; i++)
	    dprintf("%C", KeyValueInformation[0].Name[i]);
	  dprintf(", Type = %d\n", KeyValueInformation[0].Type);

	  if (KeyValueInformation[0].Type == REG_SZ)
	    dprintf("    Value = %S\n",
		    ((char*)&KeyValueInformation[0]+KeyValueInformation[0].DataOffset));

	  if (KeyValueInformation[0].Type == REG_DWORD)
	    dprintf("    Value = %X\n",
		    *((DWORD*)((char*)&KeyValueInformation[0]+KeyValueInformation[0].DataOffset)));
	}
    }

  dprintf("NtClose:\n");
  Status = NtClose(hKey);
  dprintf("  Status = %lx\n", Status);
}