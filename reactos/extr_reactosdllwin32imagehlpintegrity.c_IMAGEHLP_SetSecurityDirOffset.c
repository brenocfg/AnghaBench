#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int Size; int VirtualAddress; } ;
struct TYPE_8__ {TYPE_5__* DataDirectory; } ;
struct TYPE_11__ {TYPE_1__ OptionalHeader; } ;
struct TYPE_9__ {TYPE_5__* DataDirectory; } ;
struct TYPE_10__ {TYPE_2__ OptionalHeader; } ;
typedef  TYPE_3__ IMAGE_NT_HEADERS64 ;
typedef  TYPE_4__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_5__ IMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int HDR_NT32 ; 
 int HDR_NT64 ; 
 int IMAGEHLP_GetNTHeaders (int /*<<< orphan*/ ,int*,TYPE_4__*,TYPE_3__*) ; 
 size_t IMAGE_FILE_SECURITY_DIRECTORY ; 
 int INVALID_SET_FILE_POINTER ; 
 int SetFilePointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,void*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL IMAGEHLP_SetSecurityDirOffset(HANDLE handle,
                                          DWORD dwOfs, DWORD dwSize)
{
    IMAGE_NT_HEADERS32 nt_hdr32;
    IMAGE_NT_HEADERS64 nt_hdr64;
    IMAGE_DATA_DIRECTORY *sd;
    int ret, nt_hdr_size = 0;
    DWORD pe_offset;
    void *nt_hdr;
    DWORD count;
    BOOL r;

    ret = IMAGEHLP_GetNTHeaders(handle, &pe_offset, &nt_hdr32, &nt_hdr64);

    if (ret == HDR_NT32)
    {
        sd = &nt_hdr32.OptionalHeader.DataDirectory[IMAGE_FILE_SECURITY_DIRECTORY];

        nt_hdr = &nt_hdr32;
        nt_hdr_size = sizeof(IMAGE_NT_HEADERS32);
    }
    else if (ret == HDR_NT64)
    {
        sd = &nt_hdr64.OptionalHeader.DataDirectory[IMAGE_FILE_SECURITY_DIRECTORY];

        nt_hdr = &nt_hdr64;
        nt_hdr_size = sizeof(IMAGE_NT_HEADERS64);
    }
    else
        return FALSE;

    sd->Size = dwSize;
    sd->VirtualAddress = dwOfs;

    TRACE("size = %x addr = %x\n", sd->Size, sd->VirtualAddress);

    /* write the header back again */
    count = SetFilePointer(handle, pe_offset, NULL, FILE_BEGIN);

    if (count == INVALID_SET_FILE_POINTER)
        return FALSE;

    count = 0;

    r = WriteFile(handle, nt_hdr, nt_hdr_size, &count, NULL);

    if (!r)
        return FALSE;

    if (count != nt_hdr_size)
        return FALSE;

    return TRUE;
}