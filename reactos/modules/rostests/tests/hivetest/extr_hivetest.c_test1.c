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
struct TYPE_4__ {int NameLength; scalar_t__* Name; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KeyInformation ;
typedef  TYPE_1__ KEY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeyBasicInformation ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 scalar_t__ NtClose (int /*<<< orphan*/ *) ; 
 scalar_t__ NtEnumerateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 scalar_t__ NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NtQueryKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test1(void)
{
 HANDLE hKey = NULL, hKey1;
 OBJECT_ATTRIBUTES ObjectAttributes;
 NTSTATUS Status;
 UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\Software");
 ULONG Index,Length,i;
 KEY_BASIC_INFORMATION KeyInformation[5];

#if 0
  dprintf("NtOpenKey \\Registry : ");
#endif
  dprintf("NtOpenKey \\Registry\\Machine\\Software : ");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  Status=NtOpenKey( &hKey1, MAXIMUM_ALLOWED, &ObjectAttributes);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  if(Status==0)
  {
    dprintf("NtQueryKey : ");
    Status=NtQueryKey(hKey1,KeyBasicInformation
		,&KeyInformation[0], sizeof(KeyInformation)
		,&Length);
    dprintf("\t\t\t\t\tStatus =%x\n",Status);
    if (Status == STATUS_SUCCESS)
    {
        dprintf("\tKey Name = ");
	  for (i=0;i<KeyInformation[0].NameLength/2;i++)
		dprintf("%C",KeyInformation[0].Name[i]);
        dprintf("\n");
    }
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
    dprintf("NtClose : ");
    Status = NtClose( hKey1 );
    dprintf("\t\t\t\t\tStatus =%x\n",Status);
  }
  NtClose(hKey);
}