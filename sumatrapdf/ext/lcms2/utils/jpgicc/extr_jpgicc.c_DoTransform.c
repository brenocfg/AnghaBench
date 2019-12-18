#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
struct TYPE_11__ {int output_width; int num_components; scalar_t__ output_scanline; scalar_t__ output_height; int /*<<< orphan*/  Y_density; int /*<<< orphan*/  X_density; int /*<<< orphan*/  density_unit; } ;
struct TYPE_10__ {int image_width; int num_components; int /*<<< orphan*/  Y_density; int /*<<< orphan*/  X_density; int /*<<< orphan*/  density_unit; } ;
typedef  scalar_t__ JSAMPROW ;

/* Variables and functions */
 TYPE_1__ Compressor ; 
 TYPE_2__ Decompressor ; 
 int /*<<< orphan*/  DoEmbedProfile (scalar_t__) ; 
 scalar_t__ EmbedProfile ; 
 int PT_Lab ; 
 int /*<<< orphan*/  SetITUFax (TYPE_1__*) ; 
 int TRUE ; 
 scalar_t__ cOutProf ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  jpeg_finish_compress (TYPE_1__*) ; 
 int /*<<< orphan*/  jpeg_finish_decompress (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_read_scanlines (TYPE_2__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  jpeg_start_compress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jpeg_start_decompress (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_write_scanlines (TYPE_1__*,scalar_t__*,int) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static
int DoTransform(cmsHTRANSFORM hXForm, int OutputColorSpace)
{
    JSAMPROW ScanLineIn;
    JSAMPROW ScanLineOut;


       //Preserve resolution values from the original
       // (Thanks to Robert Bergs for finding out this bug)
       Compressor.density_unit = Decompressor.density_unit;
       Compressor.X_density    = Decompressor.X_density;
       Compressor.Y_density    = Decompressor.Y_density;

      //  Compressor.write_JFIF_header = 1;

       jpeg_start_decompress(&Decompressor);
       jpeg_start_compress(&Compressor, TRUE);

        if (OutputColorSpace == PT_Lab)
            SetITUFax(&Compressor);

       // Embed the profile if needed
       if (EmbedProfile && cOutProf)
           DoEmbedProfile(cOutProf);

       ScanLineIn  = (JSAMPROW) malloc(Decompressor.output_width * Decompressor.num_components);
       ScanLineOut = (JSAMPROW) malloc(Compressor.image_width * Compressor.num_components);

       while (Decompressor.output_scanline <
                            Decompressor.output_height) {

       jpeg_read_scanlines(&Decompressor, &ScanLineIn, 1);

       cmsDoTransform(NULL, hXForm, ScanLineIn, ScanLineOut, Decompressor.output_width);

       jpeg_write_scanlines(&Compressor, &ScanLineOut, 1);
       }

       free(ScanLineIn);
       free(ScanLineOut);

       jpeg_finish_decompress(&Decompressor);
       jpeg_finish_compress(&Compressor);

       return TRUE;
}