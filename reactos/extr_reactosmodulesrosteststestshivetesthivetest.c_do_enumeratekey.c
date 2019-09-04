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
struct TYPE_3__ {int NameLength; int /*<<< orphan*/ * Name; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KeyInformation ;
typedef  TYPE_1__ KEY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeyBasicInformation ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 scalar_t__ NtEnumerateKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 scalar_t__ NtOpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void do_enumeratekey(PWSTR Name)
{
 ULONG Index,Length,i;
 KEY_BASIC_INFORMATION KeyInformation[5];
 NTSTATUS Status;
 OBJECT_ATTRIBUTES ObjectAttributes;
 HANDLE hKey1;
 UNICODE_STRING KeyName;

  RtlInitUnicodeString(&KeyName, Name);
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, NULL, NULL);
  Status=NtOpenKey( &hKey1, MAXIMUM_ALLOWED, &ObjectAttributes);
    dprintf("NtEnumerateKey : \n");
    Index=0;
    while(Status == STATUS_SUCCESS)
    {
      Status=NtEnumerateKey(hKey1,Index++,KeyBasicInformation
		,&KeyInformation[0], sizeof(KeyInformation)
		,&Length);
      if(Status== STATUS_SUCCESS)
	{
        dprintf("\tSubKey Name = ");
	  for (i=0;i<KeyInformation[0].NameLength/2;i++)
		dprintf("%C",KeyInformation[0].Name[i]);
        dprintf("\n");
	}
    }
  NtClose(hKey1);
}