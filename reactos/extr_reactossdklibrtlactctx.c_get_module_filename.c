#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ USHORT ;
struct TYPE_7__ {scalar_t__ MaximumLength; scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_6__ {scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_8__ {TYPE_1__ FullDllName; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_3__ LDR_DATA_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 scalar_t__ LdrFindEntryForAddress (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  LdrLockLoaderLock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LdrUnlockLoaderLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 scalar_t__ STATUS_NO_MEMORY ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static NTSTATUS get_module_filename( HMODULE module, UNICODE_STRING *str, USHORT extra_len )
{
    NTSTATUS status;
    ULONG_PTR magic;
    LDR_DATA_TABLE_ENTRY *pldr;

    LdrLockLoaderLock(0, NULL, &magic);
    status = LdrFindEntryForAddress( module, &pldr );
    if (status == STATUS_SUCCESS)
    {
        if ((str->Buffer = RtlAllocateHeap( RtlGetProcessHeap(), 0,
                                            pldr->FullDllName.Length + extra_len + sizeof(WCHAR) )))
        {
            memcpy( str->Buffer, pldr->FullDllName.Buffer, pldr->FullDllName.Length + sizeof(WCHAR) );
            str->Length = pldr->FullDllName.Length;
            str->MaximumLength = pldr->FullDllName.Length + extra_len + sizeof(WCHAR);
        }
        else status = STATUS_NO_MEMORY;
    }
    LdrUnlockLoaderLock(0, magic);
    return status;
}