#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_21__ {void* p; TYPE_8__* psh; } ;
struct TYPE_15__ {int VirtualSize; } ;
struct TYPE_20__ {int VirtualAddress; int SizeOfRawData; TYPE_3__ Misc; } ;
struct TYPE_19__ {void* p; TYPE_6__* psh; } ;
struct TYPE_14__ {int VirtualSize; } ;
struct TYPE_18__ {int SizeOfRawData; TYPE_2__ Misc; } ;
struct TYPE_17__ {int SizeOfRawData; int PointerToRawData; } ;
struct TYPE_16__ {size_t FileAlignment; int SizeOfImage; scalar_t__ CheckSum; } ;
struct TYPE_13__ {scalar_t__ NumberOfSections; } ;
struct TYPE_12__ {void* FilePtr; int HeaderSize; size_t AllSections; void* DosHeader; int NewSectionHeaderSize; void* NewSectionHeaders; void* AlignBuf; TYPE_9__ xdata; TYPE_7__ pdata; TYPE_5__* SectionHeaders; scalar_t__* UseSection; TYPE_4__* OptionalHeader; scalar_t__ UsedSections; TYPE_1__* FileHeader; } ;
typedef  TYPE_10__* PFILE_INFO ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CalculateChecksum (scalar_t__,void*,int) ; 
 int ROUND_UP (int,size_t) ; 
 int fwrite (void*,int,int,int /*<<< orphan*/ *) ; 

void
WriteOutFile(FILE *handle, PFILE_INFO File)
{
    int ret, Size, Pos = 0;
    DWORD CheckSum;
    ULONG i, Alignment;

    Alignment = File->OptionalHeader->FileAlignment;

    /* Update section count */
    File->FileHeader->NumberOfSections = File->UsedSections + 2; // FIXME!!!

    /* Update SizeOfImage */
    Size = File->xdata.psh->VirtualAddress
           + File->xdata.psh->SizeOfRawData;
    File->OptionalHeader->SizeOfImage = Size;

    /* Recalculate checksum */
    CheckSum = CalculateChecksum(0, File->FilePtr, File->HeaderSize);
    for (i = 0; i < File->AllSections; i++)
    {
        if (File->UseSection[i])
        {
            Size = File->SectionHeaders[i].SizeOfRawData;
            if (Size)
            {
                void *p;
                p = File->FilePtr + File->SectionHeaders[i].PointerToRawData;
                CheckSum = CalculateChecksum(CheckSum, p, Size);
            }
        }
    }
    Size = File->pdata.psh->Misc.VirtualSize;
    CheckSum = CalculateChecksum(CheckSum, File->pdata.p, Size);
    Size = File->xdata.psh->Misc.VirtualSize;
    CheckSum = CalculateChecksum(CheckSum, File->xdata.p, Size);
    CheckSum += File->HeaderSize;
    CheckSum += File->pdata.psh->Misc.VirtualSize;
    CheckSum += File->xdata.psh->Misc.VirtualSize;
    File->OptionalHeader->CheckSum = CheckSum;

    /* Write file header */
    Size = File->HeaderSize;
    ret = fwrite(File->DosHeader, 1, Size, handle);
    Pos = Size;

    /* Write Section headers */
    Size = File->NewSectionHeaderSize;
    ret = fwrite(File->NewSectionHeaders, 1, Size, handle);
    Pos += Size;

    /* Fill up to next alignement */
    Size = ROUND_UP(Pos, Alignment) - Pos;
    ret = fwrite(File->AlignBuf, 1, Size, handle);
    Pos += Size;

    /* Write sections */
    for (i = 0; i < File->AllSections; i++)
    {
        if (File->UseSection[i])
        {
            void *p;
            Size = File->SectionHeaders[i].SizeOfRawData;
            if (Size)
            {
                p = File->FilePtr + File->SectionHeaders[i].PointerToRawData;
                ret = fwrite(p, 1, Size, handle);
                Pos += Size;
            }
        }
    }

    /* Write .pdata section */
    Size = File->pdata.psh->SizeOfRawData;
    ret = fwrite(File->pdata.p, 1, Size, handle);
    Pos += Size;

    /* Write .xdata section */
    Size = File->xdata.psh->SizeOfRawData;
    ret = fwrite(File->xdata.p, 1, Size, handle);
    Pos += Size;

}