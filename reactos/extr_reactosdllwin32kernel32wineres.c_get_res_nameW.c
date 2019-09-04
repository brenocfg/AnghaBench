#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ NTSTATUS ;
typedef  char* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_INTRESOURCE (char*) ; 
 int /*<<< orphan*/  LOWORD (char*) ; 
 int /*<<< orphan*/  RtlCreateUnicodeString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 scalar_t__ RtlUnicodeStringToInteger (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlUpcaseUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_SUCCESS ; 
 void* ULongToPtr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS get_res_nameW( LPCWSTR name, UNICODE_STRING *str )
{
    if (IS_INTRESOURCE(name))
    {
        str->Buffer = ULongToPtr(LOWORD(name));
        return STATUS_SUCCESS;
    }
    if (name[0] == '#')
    {
        ULONG value;
        RtlInitUnicodeString( str, name + 1 );
        if (RtlUnicodeStringToInteger( str, 10, &value ) != STATUS_SUCCESS || HIWORD(value))
            return STATUS_INVALID_PARAMETER;
        str->Buffer = ULongToPtr(value);
        return STATUS_SUCCESS;
    }
    RtlCreateUnicodeString( str, name );
    RtlUpcaseUnicodeString( str, str, FALSE );
    return STATUS_SUCCESS;
}