#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {long PixelCount; } ;
struct TYPE_18__ {int Interlace; scalar_t__ Height; scalar_t__ Width; TYPE_11__* ColorMap; scalar_t__ Top; scalar_t__ Left; } ;
struct TYPE_20__ {int ImageCount; TYPE_2__ Image; TYPE_3__* SavedImages; TYPE_5__* Private; } ;
struct TYPE_17__ {int /*<<< orphan*/ * ExtensionBlocks; scalar_t__ ExtensionBlockCount; } ;
struct TYPE_19__ {TYPE_1__ Extensions; int /*<<< orphan*/ * RasterBits; TYPE_2__ ImageDesc; } ;
struct TYPE_16__ {int SortFlag; int ColorCount; TYPE_10__* Colors; } ;
struct TYPE_15__ {int Red; int Green; int Blue; } ;
typedef  TYPE_3__ SavedImage ;
typedef  TYPE_4__ GifFileType ;
typedef  TYPE_5__ GifFilePrivateType ;
typedef  int GifByteType ;

/* Variables and functions */
 scalar_t__ DGifGetWord (TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  DGifSetupDecompress (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeMapObject (TYPE_11__*) ; 
 scalar_t__ GIF_ERROR ; 
 int GIF_OK ; 
 void* MakeMapObject (int,TYPE_10__*) ; 
 int READ (TYPE_4__*,int*,int) ; 
 TYPE_3__* ungif_alloc (int) ; 
 TYPE_3__* ungif_realloc (TYPE_3__*,int) ; 

__attribute__((used)) static int
DGifGetImageDesc(GifFileType * GifFile) {

    int i, BitsPerPixel, SortFlag;
    GifByteType Buf[3];
    GifFilePrivateType *Private = GifFile->Private;
    SavedImage *sp;

    if (DGifGetWord(GifFile, &GifFile->Image.Left) == GIF_ERROR ||
        DGifGetWord(GifFile, &GifFile->Image.Top) == GIF_ERROR ||
        DGifGetWord(GifFile, &GifFile->Image.Width) == GIF_ERROR ||
        DGifGetWord(GifFile, &GifFile->Image.Height) == GIF_ERROR)
        return GIF_ERROR;
    if (READ(GifFile, Buf, 1) != 1) {
        return GIF_ERROR;
    }
    BitsPerPixel = (Buf[0] & 0x07) + 1;
    SortFlag = (Buf[0] & 0x20) != 0;
    GifFile->Image.Interlace = (Buf[0] & 0x40);
    if (Buf[0] & 0x80) {    /* Does this image have local color map? */

        FreeMapObject(GifFile->Image.ColorMap);

        GifFile->Image.ColorMap = MakeMapObject(1 << BitsPerPixel, NULL);
        if (GifFile->Image.ColorMap == NULL) {
            return GIF_ERROR;
        }

        /* Get the image local color map: */
        GifFile->Image.ColorMap->SortFlag = SortFlag;
        for (i = 0; i < GifFile->Image.ColorMap->ColorCount; i++) {
            if (READ(GifFile, Buf, 3) != 3) {
                FreeMapObject(GifFile->Image.ColorMap);
                GifFile->Image.ColorMap = NULL;
                return GIF_ERROR;
            }
            GifFile->Image.ColorMap->Colors[i].Red = Buf[0];
            GifFile->Image.ColorMap->Colors[i].Green = Buf[1];
            GifFile->Image.ColorMap->Colors[i].Blue = Buf[2];
        }
    } else if (GifFile->Image.ColorMap) {
        FreeMapObject(GifFile->Image.ColorMap);
        GifFile->Image.ColorMap = NULL;
    }

    if (GifFile->SavedImages) {
        if ((GifFile->SavedImages = ungif_realloc(GifFile->SavedImages,
                                      sizeof(SavedImage) *
                                      (GifFile->ImageCount + 1))) == NULL) {
            return GIF_ERROR;
        }
    } else {
        if ((GifFile->SavedImages = ungif_alloc(sizeof(SavedImage))) == NULL) {
            return GIF_ERROR;
        }
    }

    sp = &GifFile->SavedImages[GifFile->ImageCount];
    sp->ImageDesc = GifFile->Image;
    if (GifFile->Image.ColorMap != NULL) {
        sp->ImageDesc.ColorMap = MakeMapObject(
                                 GifFile->Image.ColorMap->ColorCount,
                                 GifFile->Image.ColorMap->Colors);
        if (sp->ImageDesc.ColorMap == NULL) {
            return GIF_ERROR;
        }
        sp->ImageDesc.ColorMap->SortFlag = GifFile->Image.ColorMap->SortFlag;
    }
    sp->RasterBits = NULL;
    sp->Extensions.ExtensionBlockCount = 0;
    sp->Extensions.ExtensionBlocks = NULL;

    GifFile->ImageCount++;

    Private->PixelCount = (long)GifFile->Image.Width *
       (long)GifFile->Image.Height;

    DGifSetupDecompress(GifFile);  /* Reset decompress algorithm parameters. */

    return GIF_OK;
}