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
typedef  char WCHAR ;
struct TYPE_5__ {char* Buffer; int Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_6__ {scalar_t__ RootDirectory; size_t Attributes; TYPE_1__* ObjectName; } ;
typedef  scalar_t__* PHANDLE ;
typedef  TYPE_2__ OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ HANDLE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  ACCESS_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 scalar_t__ NtCreateKey (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_OBJECT_NAME_NOT_FOUND ; 

__attribute__((used)) static NTSTATUS create_key( HKEY *retkey, ACCESS_MASK access, OBJECT_ATTRIBUTES *attr )
{
    NTSTATUS status = NtCreateKey( (HANDLE *)retkey, access, attr, 0, NULL, 0, NULL );

    if (status == STATUS_OBJECT_NAME_NOT_FOUND)
    {
        HANDLE subkey, root = attr->RootDirectory;
        WCHAR *buffer = attr->ObjectName->Buffer;
        DWORD attrs, pos = 0, i = 0, len = attr->ObjectName->Length / sizeof(WCHAR);
        UNICODE_STRING str;

        while (i < len && buffer[i] != '\\') i++;
        if (i == len) return status;

        attrs = attr->Attributes;
        attr->ObjectName = &str;

        while (i < len)
        {
            str.Buffer = buffer + pos;
            str.Length = (i - pos) * sizeof(WCHAR);
            status = NtCreateKey( &subkey, access, attr, 0, NULL, 0, NULL );
            if (attr->RootDirectory != root) NtClose( attr->RootDirectory );
            if (status) return status;
            attr->RootDirectory = subkey;
            while (i < len && buffer[i] == '\\') i++;
            pos = i;
            while (i < len && buffer[i] != '\\') i++;
        }
        str.Buffer = buffer + pos;
        str.Length = (i - pos) * sizeof(WCHAR);
        attr->Attributes = attrs;
        status = NtCreateKey( (PHANDLE)retkey, access, attr, 0, NULL, 0, NULL );
        if (attr->RootDirectory != root) NtClose( attr->RootDirectory );
    }
    return status;
}