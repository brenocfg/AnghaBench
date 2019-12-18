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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  char* NTSTATUS ;
typedef  int /*<<< orphan*/  KeyValueInformation ;
typedef  TYPE_1__ KEY_VALUE_FULL_INFORMATION ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InputHandle ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KeyValueFullInformation ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ *) ; 
 char* NtCreateKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* NtDeleteKey (int /*<<< orphan*/ *) ; 
 char* NtEnumerateValueKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 char* NtOpenKey (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* NtSetValueKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 scalar_t__ REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  ReadConsoleA (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlRosInitUnicodeStringFromLiteral (int /*<<< orphan*/ *,char*) ; 
 char* STATUS_SUCCESS ; 
 int /*<<< orphan*/  do_enumeratekey (char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

void test3(void)
{
 HKEY hKey,hKey1;
 OBJECT_ATTRIBUTES ObjectAttributes;
 UNICODE_STRING KeyName,ValueName;
 NTSTATUS Status;
 KEY_VALUE_FULL_INFORMATION KeyValueInformation[5];
 ULONG Index,Length,i;
 char Buffer[10];
 DWORD Result;
  dprintf("NtCreateKey non volatile: \n");
  dprintf("  \\Registry\\Machine\\Software\\test3reactos: ");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, NULL, NULL);
  Status = NtCreateKey ( &hKey, KEY_ALL_ACCESS , &ObjectAttributes
		,0,NULL,REG_OPTION_NON_VOLATILE,NULL);
  dprintf("\t\tStatus=%x\n",Status);
  NtClose(hKey);
  do_enumeratekey(L"\\Registry\\Machine\\Software");
  dprintf("NtOpenKey: ");
  Status=NtOpenKey( &hKey, MAXIMUM_ALLOWED, &ObjectAttributes);
  dprintf("\t\tStatus=%x\n",Status);
  NtClose(hKey);
  dprintf("  ...\\test3 :");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos\\test3");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, NULL, NULL);
  Status = NtCreateKey ( &hKey, KEY_ALL_ACCESS , &ObjectAttributes
		,0,NULL,REG_OPTION_NON_VOLATILE,NULL);
  dprintf("\t\t\t\t\tStatus=%x\n",Status);
  dprintf("NtOpenKey: ");
  Status=NtOpenKey( &hKey1, MAXIMUM_ALLOWED, &ObjectAttributes);
  dprintf("\t\tStatus=%x\n",Status);
  NtClose(hKey);
  dprintf("  ...\\testNonVolatile :");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"TestNonVolatile");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, hKey1, NULL);
  Status = NtCreateKey ( &hKey, KEY_ALL_ACCESS , &ObjectAttributes
		,0,NULL,REG_OPTION_NON_VOLATILE,NULL);
  dprintf("\t\t\t\tStatus=%x\n",Status);
  NtClose(hKey1);
  RtlRosInitUnicodeStringFromLiteral(&ValueName, L"TestREG_SZ");
  dprintf("NtSetValueKey reg_sz: ");
  Status=NtSetValueKey(hKey,&ValueName,0,REG_SZ,(PVOID)L"Test Reg_sz",24);
  dprintf("\t\t\t\tStatus=%x\n",Status);
  RtlRosInitUnicodeStringFromLiteral(&ValueName, L"TestDWORD");
  dprintf("NtSetValueKey reg_dword: ");
  Status=NtSetValueKey(hKey,&ValueName,0,REG_DWORD,(PVOID)"reac",4);
  dprintf("\t\t\tStatus=%x\n",Status);
  NtClose(hKey);
  dprintf("NtOpenKey \\Registry\\Machine\\Software\\test3reactos\\test3\\testNonVolatile : ");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos\\test3\\testNonVolatile");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  Status=NtOpenKey( &hKey, MAXIMUM_ALLOWED, &ObjectAttributes);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  if(Status==0)
  {
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
  }
  NtClose(hKey);
  dprintf("delete \\Registry\\Machine\\software\\test3reactos ?");
  ReadConsoleA(InputHandle, Buffer, 3, &Result, NULL) ;
  if (Buffer[0] != 'y' && Buffer[0] != 'Y') return;
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos\\test3\\testNonvolatile");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  dprintf("NtOpenKey : ");
  Status=NtOpenKey( &hKey, KEY_ALL_ACCESS, &ObjectAttributes);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  dprintf("NtDeleteKey : ");
  Status=NtDeleteKey(hKey);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos\\test3");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  dprintf("NtOpenKey : ");
  Status=NtOpenKey( &hKey, KEY_ALL_ACCESS, &ObjectAttributes);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  dprintf("NtDeleteKey : ");
  Status=NtDeleteKey(hKey);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  NtClose(hKey);
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  dprintf("NtOpenKey : ");
  Status=NtOpenKey( &hKey, KEY_ALL_ACCESS, &ObjectAttributes);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  dprintf("NtDeleteKey : ");
  Status=NtDeleteKey(hKey);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  NtClose(hKey);
}