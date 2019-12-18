#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsInt32Number ;
typedef  int /*<<< orphan*/  TIFF ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FatalError (char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  OutOfMem (scalar_t__) ; 
 int /*<<< orphan*/  TIFFSetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  TIFFTAG_ICCPROFILE ; 
 scalar_t__ cmsfilelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (scalar_t__*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (scalar_t__) ; 

__attribute__((used)) static
void DoEmbedProfile(TIFF* Out, const char* ProfileFile)
{
    FILE* f;
    cmsInt32Number size;
    cmsUInt32Number EmbedLen;
    cmsUInt8Number* EmbedBuffer;

    f = fopen(ProfileFile, "rb");
    if (f == NULL) return;

    size = cmsfilelength(f);
    if (size < 0) return;

    EmbedBuffer = (cmsUInt8Number*) malloc(size + 1);
    if (EmbedBuffer == NULL) {
        OutOfMem(size+1);
        return;
    }

    EmbedLen = (cmsUInt32Number) fread(EmbedBuffer, 1, (size_t) size, f);

    if (EmbedLen != size)
        FatalError("Cannot read %ld bytes to %s", size, ProfileFile);

    fclose(f);
    EmbedBuffer[EmbedLen] = 0;

    TIFFSetField(Out, TIFFTAG_ICCPROFILE, EmbedLen, EmbedBuffer);
    free(EmbedBuffer);
}