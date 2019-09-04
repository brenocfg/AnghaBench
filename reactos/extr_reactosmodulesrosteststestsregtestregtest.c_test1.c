#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_8__ {int NameLength; char** Name; } ;
struct TYPE_7__ {int DataOffset; int NameLength; char** Name; char* Type; int /*<<< orphan*/  DataLength; } ;
typedef  char* PWCHAR ;
typedef  int PCHAR ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  char* NTSTATUS ;
typedef  int /*<<< orphan*/  KeyValueInformation ;
typedef  int /*<<< orphan*/  KeyInformation ;
typedef  TYPE_1__ KEY_VALUE_FULL_INFORMATION ;
typedef  TYPE_2__ KEY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/ * HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KeyBasicInformation ; 
 int /*<<< orphan*/  KeyValueFullInformation ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 char* NtClose (int /*<<< orphan*/ *) ; 
 char* NtEnumerateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 char* NtEnumerateValueKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 char* NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* NtQueryKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 char* NtQueryValueKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  ROS_STRING_INITIALIZER (char*) ; 
 int /*<<< orphan*/  RtlRosInitUnicodeStringFromLiteral (int /*<<< orphan*/ *,char*) ; 
 char* STATUS_SUCCESS ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test1(void)
{
 HKEY hKey = NULL, hKey1;
 OBJECT_ATTRIBUTES ObjectAttributes;
 NTSTATUS Status;
 UNICODE_STRING KeyName = ROS_STRING_INITIALIZER(L"\\Registry");
 ULONG Index,Length,i;
 KEY_BASIC_INFORMATION KeyInformation[5];
 KEY_VALUE_FULL_INFORMATION KeyValueInformation[5];

  dprintf("NtOpenKey \\Registry : ");
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

  dprintf("NtOpenKey \\Registry\\Machine : ");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  Status=NtOpenKey( &hKey1, MAXIMUM_ALLOWED, &ObjectAttributes);
  dprintf("\t\t\tStatus =%x\n",Status);

  dprintf("NtOpenKey System\\Setup : ");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"System\\Setup");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, hKey1 , NULL);
  Status = NtOpenKey ( &hKey, KEY_READ , &ObjectAttributes);
  dprintf("\t\t\tStatus =%x\n",Status);
  if(Status==0)
  {
    dprintf("NtQueryValueKey : ");
    RtlRosInitUnicodeStringFromLiteral(&KeyName, L"CmdLine");
    Status=NtQueryValueKey(hKey,&KeyName,KeyValueFullInformation
		,&KeyValueInformation[0], sizeof(KeyValueInformation)
		,&Length);
    dprintf("\t\t\t\tStatus =%x\n",Status);
    if (Status == STATUS_SUCCESS)
    {
      dprintf("\tValue:DO=%d, DL=%d, NL=%d, Name = "
	      ,KeyValueInformation[0].DataOffset
	      ,KeyValueInformation[0].DataLength
	      ,KeyValueInformation[0].NameLength);
      for (i=0;i<10 && i<KeyValueInformation[0].NameLength/2;i++)
	dprintf("%C",KeyValueInformation[0].Name[i]);
      dprintf("\n");
      dprintf("\t\tType = %d\n",KeyValueInformation[0].Type);
      if (KeyValueInformation[0].Type == REG_SZ)
	dprintf("\t\tValue = %S\n",
		(PWCHAR)((PCHAR)&KeyValueInformation[0] + KeyValueInformation[0].DataOffset));
    }
    dprintf("NtEnumerateValueKey : \n");
    Index=0;
    while(Status == STATUS_SUCCESS)
    {
      Status=NtEnumerateValueKey(hKey,Index++,KeyValueFullInformation
		,&KeyValueInformation[0], sizeof(KeyValueInformation)
		,&Length);
      if(Status== STATUS_SUCCESS)
	{
        dprintf("\tValue:DO=%d, DL=%d, NL=%d, Name = "
		,KeyValueInformation[0].DataOffset
		,KeyValueInformation[0].DataLength
		,KeyValueInformation[0].NameLength);
	  for (i=0;i<KeyValueInformation[0].NameLength/2;i++)
		dprintf("%C",KeyValueInformation[0].Name[i]);
        dprintf(", Type = %d\n",KeyValueInformation[0].Type);
	  if (KeyValueInformation[0].Type == REG_SZ)
          dprintf("\t\tValue = %S\n",((char*)&KeyValueInformation[0]
    					+KeyValueInformation[0].DataOffset));
	}
    }
    dprintf("NtClose : ");
    Status = NtClose( hKey );
    dprintf("\t\t\t\t\tStatus =%x\n",Status);
  }
  NtClose( hKey1 );
}