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
struct TYPE_6__ {int BitsPerPixel; int ClearCode; int EOFCode; int RunningCode; int RunningBits; int MaxCode1; void** Prefix; scalar_t__ CrntShiftDWord; scalar_t__ CrntShiftState; void* LastCode; scalar_t__ StackPtr; scalar_t__* Buf; } ;
struct TYPE_5__ {TYPE_2__* Private; } ;
typedef  void* GifPrefixType ;
typedef  TYPE_1__ GifFileType ;
typedef  TYPE_2__ GifFilePrivateType ;
typedef  int GifByteType ;

/* Variables and functions */
 int GIF_OK ; 
 int LZ_MAX_CODE ; 
 void* NO_SUCH_CODE ; 
 int /*<<< orphan*/  READ (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int
DGifSetupDecompress(GifFileType * GifFile) {

    int i, BitsPerPixel;
    GifByteType CodeSize;
    GifPrefixType *Prefix;
    GifFilePrivateType *Private = GifFile->Private;

    READ(GifFile, &CodeSize, 1);    /* Read Code size from file. */
    BitsPerPixel = CodeSize;

    Private->Buf[0] = 0;    /* Input Buffer empty. */
    Private->BitsPerPixel = BitsPerPixel;
    Private->ClearCode = (1 << BitsPerPixel);
    Private->EOFCode = Private->ClearCode + 1;
    Private->RunningCode = Private->EOFCode + 1;
    Private->RunningBits = BitsPerPixel + 1;    /* Number of bits per code. */
    Private->MaxCode1 = 1 << Private->RunningBits;    /* Max. code + 1. */
    Private->StackPtr = 0;    /* No pixels on the pixel stack. */
    Private->LastCode = NO_SUCH_CODE;
    Private->CrntShiftState = 0;    /* No information in CrntShiftDWord. */
    Private->CrntShiftDWord = 0;

    Prefix = Private->Prefix;
    for (i = 0; i <= LZ_MAX_CODE; i++)
        Prefix[i] = NO_SUCH_CODE;

    return GIF_OK;
}