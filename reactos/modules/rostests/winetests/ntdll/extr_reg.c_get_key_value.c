#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_6__ {scalar_t__ Data; } ;
struct TYPE_5__ {int Length; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; int /*<<< orphan*/ * ObjectName; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  RootDirectory; } ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_2__ KEY_VALUE_PARTIAL_INFORMATION ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KeyValuePartialInformation ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 scalar_t__ STATUS_OBJECT_NAME_NOT_FOUND ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateKey (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtQueryValueKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_str ; 

__attribute__((used)) static DWORD get_key_value( HANDLE root, const char *name, DWORD flags )
{
    char tmp[32];
    NTSTATUS status;
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING str;
    HANDLE key;
    KEY_VALUE_PARTIAL_INFORMATION *info = (KEY_VALUE_PARTIAL_INFORMATION *)tmp;
    DWORD dw, len = sizeof(tmp);

    attr.Length = sizeof(attr);
    attr.RootDirectory = root;
    attr.Attributes = OBJ_CASE_INSENSITIVE;
    attr.ObjectName = &str;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    pRtlCreateUnicodeStringFromAsciiz( &str, name );

    status = pNtCreateKey( &key, flags | KEY_ALL_ACCESS, &attr, 0, 0, 0, 0 );
    if (status == STATUS_OBJECT_NAME_NOT_FOUND) return 0;
    ok( status == STATUS_SUCCESS, "%08x: NtCreateKey failed: 0x%08x\n", flags, status );

    status = pNtQueryValueKey( key, &value_str, KeyValuePartialInformation, info, len, &len );
    if (status == STATUS_OBJECT_NAME_NOT_FOUND)
        dw = 0;
    else
    {
        ok( status == STATUS_SUCCESS, "%08x: NtQueryValueKey failed: 0x%08x\n", flags, status );
        dw = *(DWORD *)info->Data;
    }
    pNtClose( key );
    pRtlFreeUnicodeString( &str );
    return dw;
}