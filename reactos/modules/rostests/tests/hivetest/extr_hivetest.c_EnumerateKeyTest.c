#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_4__ {int NameLength; int /*<<< orphan*/ * Name; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KeyInformation ;
typedef  TYPE_1__ KEY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KeyBasicInformation ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtEnumerateKey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtQueryKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void EnumerateKeyTest(void)
{
  HANDLE hKey = NULL;
  OBJECT_ATTRIBUTES ObjectAttributes;
  NTSTATUS Status;
  UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\Software");
  ULONG Index;
  ULONG Length;
  ULONG i;
  KEY_BASIC_INFORMATION KeyInformation[5];

  dprintf("Enumerate key '\\Registry\\Machine\\Software':\n");

  InitializeObjectAttributes(&ObjectAttributes,
			     &KeyName,
			     OBJ_CASE_INSENSITIVE,
			     NULL,
			     NULL);
  dprintf("NtOpenKey:\n");
  Status = NtOpenKey(&hKey,
		     KEY_ALL_ACCESS,
		     &ObjectAttributes);
  dprintf("  Status = %lx\n", Status);
  if (!NT_SUCCESS(Status))
    return;

  dprintf("NtQueryKey:\n");
  Status = NtQueryKey(hKey,
		      KeyBasicInformation,
		      &KeyInformation[0],
		      sizeof(KeyInformation),
		      &Length);
  dprintf("  Status = %lx\n", Status);
  if (NT_SUCCESS(Status))
    {
      dprintf("\tKey Name = ");
      for (i = 0; i < KeyInformation[0].NameLength / 2; i++)
	dprintf("%C", KeyInformation[0].Name[i]);
      dprintf("\n");
    }

  dprintf("NtEnumerateKey:\n");
  Index=0;
  while(NT_SUCCESS(Status))
    {
      Status = NtEnumerateKey(hKey,
			      Index,
			      KeyBasicInformation,
			      &KeyInformation[0],
			      sizeof(KeyInformation),
			      &Length);
      if (NT_SUCCESS(Status))
	{
	  dprintf("\tSubKey Name = ");
	  for (i = 0; i < KeyInformation[0].NameLength / 2; i++)
	    dprintf("%C", KeyInformation[0].Name[i]);
	  dprintf("\n");
	}
      Index++;
    }

  dprintf("NtClose:\n");
  Status = NtClose(hKey);
  dprintf("  Status = %lx\n", Status);
}