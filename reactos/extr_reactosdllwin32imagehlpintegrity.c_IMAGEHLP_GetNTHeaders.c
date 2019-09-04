#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int Magic; } ;
struct TYPE_9__ {scalar_t__ e_magic; int e_lfanew; scalar_t__ Signature; TYPE_1__ OptionalHeader; } ;
typedef  TYPE_2__ IMAGE_NT_HEADERS64 ;
typedef  TYPE_2__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_2__ IMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BEGIN ; 
 int HDR_FAIL ; 
 int HDR_NT32 ; 
 int HDR_NT64 ; 
 scalar_t__ IMAGE_DOS_SIGNATURE ; 
#define  IMAGE_NT_OPTIONAL_HDR32_MAGIC 129 
#define  IMAGE_NT_OPTIONAL_HDR64_MAGIC 128 
 scalar_t__ IMAGE_NT_SIGNATURE ; 
 int INVALID_SET_FILE_POINTER ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,TYPE_2__*,int,int*,int /*<<< orphan*/ *) ; 
 int SetFilePointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int IMAGEHLP_GetNTHeaders(HANDLE handle, DWORD *pe_offset, IMAGE_NT_HEADERS32 *nt32, IMAGE_NT_HEADERS64 *nt64)
{
    IMAGE_DOS_HEADER dos_hdr;
    DWORD count;
    BOOL r;

    TRACE("handle %p\n", handle);

    if ((!nt32) || (!nt64))
        return HDR_FAIL;

    /* read the DOS header */
    count = SetFilePointer(handle, 0, NULL, FILE_BEGIN);

    if (count == INVALID_SET_FILE_POINTER)
        return HDR_FAIL;

    count = 0;

    r = ReadFile(handle, &dos_hdr, sizeof dos_hdr, &count, NULL);

    if (!r)
        return HDR_FAIL;

    if (count != sizeof dos_hdr)
        return HDR_FAIL;

    /* verify magic number of 'MZ' */
    if (dos_hdr.e_magic != IMAGE_DOS_SIGNATURE)
        return HDR_FAIL;

    if (pe_offset != NULL)
        *pe_offset = dos_hdr.e_lfanew;

    /* read the PE header */
    count = SetFilePointer(handle, dos_hdr.e_lfanew, NULL, FILE_BEGIN);

    if (count == INVALID_SET_FILE_POINTER)
        return HDR_FAIL;

    count = 0;

    r = ReadFile(handle, nt32, sizeof(IMAGE_NT_HEADERS32), &count, NULL);

    if (!r)
        return HDR_FAIL;

    if (count != sizeof(IMAGE_NT_HEADERS32))
        return HDR_FAIL;

    /* verify NT signature */
    if (nt32->Signature != IMAGE_NT_SIGNATURE)
        return HDR_FAIL;

    /* check if we have a 32-bit or 64-bit executable */
    switch (nt32->OptionalHeader.Magic)
    {
        case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
            return HDR_NT32;

        case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
            /* Re-read as 64-bit */

            count = SetFilePointer(handle, dos_hdr.e_lfanew, NULL, FILE_BEGIN);

            if (count == INVALID_SET_FILE_POINTER)
                return HDR_FAIL;

            count = 0;

            r = ReadFile(handle, nt64, sizeof(IMAGE_NT_HEADERS64), &count, NULL);

            if (!r)
                return HDR_FAIL;

            if (count != sizeof(IMAGE_NT_HEADERS64))
                return HDR_FAIL;

            /* verify NT signature */
            if (nt64->Signature != IMAGE_NT_SIGNATURE)
                return HDR_FAIL;

            return HDR_NT64;
    }

    return HDR_FAIL;
}