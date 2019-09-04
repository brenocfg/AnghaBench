#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {scalar_t__ e_magic; long e_lfanew; scalar_t__ Magic; size_t ImageBase; } ;
typedef  TYPE_1__ IMAGE_OPTIONAL_HEADER ;
typedef  TYPE_1__ IMAGE_FILE_HEADER ;
typedef  TYPE_1__ IMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_MAGIC ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR32_MAGIC ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 size_t INVALID_BASE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
get_ImageBase(char *fname, size_t *ImageBase)
{
    IMAGE_DOS_HEADER PEDosHeader;
    IMAGE_FILE_HEADER PEFileHeader;
    IMAGE_OPTIONAL_HEADER PEOptHeader;

    FILE *fr;
    off_t readLen;
    int res;

    *ImageBase = INVALID_BASE;
    fr = fopen(fname, "rb");
    if (!fr)
    {
        l2l_dbg(3, "get_ImageBase, cannot open '%s' (%s)\n", fname, strerror(errno));
        return 1;
    }

    readLen = fread(&PEDosHeader, sizeof(IMAGE_DOS_HEADER), 1, fr);
    if (1 != readLen)
    {
        l2l_dbg(1, "get_ImageBase %s, read error IMAGE_DOS_HEADER (%s)\n", fname, strerror(errno));
        fclose(fr);
        return 2;
    }

    /* Check if MZ header exists */
    if (PEDosHeader.e_magic != IMAGE_DOS_MAGIC || PEDosHeader.e_lfanew == 0L)
    {
        l2l_dbg(2, "get_ImageBase %s, MZ header missing\n", fname);
        fclose(fr);
        return 3;
    }

    /* Locate PE file header */
    res = fseek(fr, PEDosHeader.e_lfanew + sizeof(ULONG), SEEK_SET);
    readLen = fread(&PEFileHeader, sizeof(IMAGE_FILE_HEADER), 1, fr);
    if (1 != readLen)
    {
        l2l_dbg(1, "get_ImageBase %s, read error IMAGE_FILE_HEADER (%s)\n", fname, strerror(errno));
        fclose(fr);
        return 4;
    }

    /* Locate optional header */
    readLen = fread(&PEOptHeader, sizeof(IMAGE_OPTIONAL_HEADER), 1, fr);
    if (1 != readLen)
    {
        l2l_dbg(1, "get_ImageBase %s, read error IMAGE_OPTIONAL_HEADER (%s)\n", fname, strerror(errno));
        fclose(fr);
        return 5;
    }

    /* Check if it's really an IMAGE_OPTIONAL_HEADER we are interested in */
    if (PEOptHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC &&
        PEOptHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        l2l_dbg(2, "get_ImageBase %s, not an IMAGE_NT_OPTIONAL_HDR 32/64 bit\n", fname);
        fclose(fr);
        return 6;
    }

    *ImageBase = PEOptHeader.ImageBase;
    fclose(fr);
    return 0;
}