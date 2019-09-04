#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct test_entry {int Type; int /*<<< orphan*/  OutputPath; int /*<<< orphan*/ * InputPath; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
struct TYPE_11__ {scalar_t__ StaticBuffer; int StaticSize; int Size; int ReservedForAllocatedSize; int /*<<< orphan*/  const* ReservedForIMalloc; int /*<<< orphan*/  const* Buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  const* Buffer; int /*<<< orphan*/  MaximumLength; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int MinimumStaticBufferForTerminalNul; TYPE_5__ ByteBuffer; TYPE_4__ String; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  StaticBuffer ;
typedef  TYPE_2__ RTL_UNICODE_STRING_BUFFER ;
typedef  scalar_t__ PUCHAR ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  RTL_SKIP_BUFFER_COPY ; 
 int /*<<< orphan*/  RtlEnsureBufferSize (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeBuffer (TYPE_5__*) ; 
 int /*<<< orphan*/  RtlInitBuffer (TYPE_5__*,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_hex_ (int,int) ; 
 int /*<<< orphan*/  ok_ptr_ (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_wstr_ (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int pRtlNtPathNameToDosPathName (int /*<<< orphan*/ ,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winetest_ok (int,char*) ; 

__attribute__((used)) static void test_table(struct test_entry* Entry)
{
    RTL_UNICODE_STRING_BUFFER Buffer = { { 0 } };
    WCHAR StaticBuffer[MAX_PATH];
    ULONG Type = 0x12345;

    RtlInitBuffer(&Buffer.ByteBuffer, (PUCHAR)StaticBuffer, sizeof(StaticBuffer));

    RtlInitUnicodeString(&Buffer.String, Entry->InputPath);
    RtlEnsureBufferSize(RTL_SKIP_BUFFER_COPY, &Buffer.ByteBuffer, Buffer.String.MaximumLength);
    memcpy(Buffer.ByteBuffer.Buffer, Buffer.String.Buffer, Buffer.String.MaximumLength);

    ok_hex_(pRtlNtPathNameToDosPathName(0, &Buffer, &Type, NULL), STATUS_SUCCESS);

    ok_hex_(Type, Entry->Type);
    ok_wstr_(Buffer.String.Buffer, Entry->OutputPath);
    /* If there is no change in the path, the pointer is unchanged */
    if (!wcscmp(Entry->InputPath, Entry->OutputPath))
    {
        ok_ptr_(Buffer.String.Buffer, Entry->InputPath);
    }
    else
    {
        /* If there is a change in the path, the 'ByteBuffer' is used */
        winetest_ok((PUCHAR)Buffer.String.Buffer >= Buffer.ByteBuffer.StaticBuffer &&
                    (PUCHAR)Buffer.String.Buffer <= (Buffer.ByteBuffer.StaticBuffer + Buffer.ByteBuffer.StaticSize),
                    "Expected Buffer to point inside StaticBuffer\n");
    }
    ok_wstr_((const WCHAR *)Buffer.ByteBuffer.Buffer, Entry->OutputPath);

    ok_hex_(Buffer.MinimumStaticBufferForTerminalNul, 0);

    /* For none of our tests should we exceed the StaticBuffer size! */
    ok_ptr_(Buffer.ByteBuffer.Buffer, Buffer.ByteBuffer.StaticBuffer);
    ok_hex_(Buffer.ByteBuffer.Size, Buffer.ByteBuffer.StaticSize);

    ok_hex_(Buffer.ByteBuffer.ReservedForAllocatedSize, 0);
    ok_ptr_(Buffer.ByteBuffer.ReservedForIMalloc, NULL);

    RtlFreeBuffer(&Buffer.ByteBuffer);
}