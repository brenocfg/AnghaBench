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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Compressor ; 
 size_t cmsfilelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (scalar_t__*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  write_icc_profile (int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 

__attribute__((used)) static
void DoEmbedProfile(const char* ProfileFile)
{
    FILE* f;
    size_t size, EmbedLen;
    cmsUInt8Number* EmbedBuffer;

        f = fopen(ProfileFile, "rb");
        if (f == NULL) return;

        size = cmsfilelength(f);
        EmbedBuffer = (cmsUInt8Number*) malloc(size + 1);
        EmbedLen = fread(EmbedBuffer, 1, size, f);
        fclose(f);
        EmbedBuffer[EmbedLen] = 0;

        write_icc_profile (&Compressor, EmbedBuffer, (unsigned int) EmbedLen);
        free(EmbedBuffer);
}