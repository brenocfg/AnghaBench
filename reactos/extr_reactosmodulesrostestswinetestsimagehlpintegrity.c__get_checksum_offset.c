#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ e_magic; int e_lfanew; } ;
struct TYPE_8__ {scalar_t__ Magic; int CheckSum; } ;
struct TYPE_11__ {scalar_t__ Signature; TYPE_1__ OptionalHeader; } ;
struct TYPE_9__ {int CheckSum; } ;
struct TYPE_10__ {TYPE_2__ OptionalHeader; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_3__* PIMAGE_NT_HEADERS64 ;
typedef  TYPE_4__* PIMAGE_NT_HEADERS32 ;
typedef  scalar_t__ PIMAGE_NT_HEADERS ;
typedef  TYPE_3__ IMAGE_NT_HEADERS64 ;
typedef  TYPE_4__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_7__ IMAGE_DOS_HEADER ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_SIGNATURE ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR32_MAGIC ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 scalar_t__ IMAGE_NT_SIGNATURE ; 

__attribute__((used)) static DWORD _get_checksum_offset(PVOID base, PIMAGE_NT_HEADERS *nt_header, DWORD *checksum)
{
    IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)base;
    PIMAGE_NT_HEADERS32 Header32;
    PIMAGE_NT_HEADERS64 Header64;

    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return 0;

    Header32 = (IMAGE_NT_HEADERS32 *)((char *)dos + dos->e_lfanew);
    if (Header32->Signature != IMAGE_NT_SIGNATURE)
        return 0;

    *nt_header = (PIMAGE_NT_HEADERS)Header32;

    if (Header32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
    {
        *checksum = Header32->OptionalHeader.CheckSum;
        return (char *)&Header32->OptionalHeader.CheckSum - (char *)base;
    }
    else if (Header32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        Header64 = (IMAGE_NT_HEADERS64 *)Header32;
        *checksum = Header64->OptionalHeader.CheckSum;
        return (char *)&Header64->OptionalHeader.CheckSum - (char *)base;
    }

    return 0;
}