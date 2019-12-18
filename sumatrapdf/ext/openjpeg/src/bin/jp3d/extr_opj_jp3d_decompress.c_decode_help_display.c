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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

void decode_help_display()
{
    fprintf(stdout, "HELP\n----\n\n");
    fprintf(stdout, "- the -h option displays this help information on screen\n\n");

    fprintf(stdout, "List of parameters for the JPEG 2000 encoder:\n");
    fprintf(stdout, "\n");
    fprintf(stdout, " Required arguments \n");
    fprintf(stdout, " ---------------------------- \n");
    fprintf(stdout, "  -i <compressed file> ( *.jp3d, *.j3d )\n");
    fprintf(stdout,
            "    Currently accepts J3D-files. The file type is identified based on its suffix.\n");
    fprintf(stdout, "  -o <decompressed file> ( *.pgx, *.bin )\n");
    fprintf(stdout,
            "    Currently accepts PGX-files and BIN-files. Binary data is written to the file (not ascii). \n");
    fprintf(stdout,
            "    If a PGX filename is given, there will be as many output files as slices; \n");
    fprintf(stdout,
            "    an indice starting from 0 will then be appended to the output filename,\n");
    fprintf(stdout, "    just before the \"pgx\" extension.\n");
    fprintf(stdout, "  -m <characteristics file> ( *.img ) \n");
    fprintf(stdout,
            "    Required only for BIN-files. Ascii data of volume characteristics is written. \n");
    fprintf(stdout, "\n");
    fprintf(stdout, " Optional  \n");
    fprintf(stdout, " ---------------------------- \n");
    fprintf(stdout, "  -h \n ");
    fprintf(stdout, "    Display the help information\n");
    fprintf(stdout, "  -r <RFx,RFy,RFz>\n");
    fprintf(stdout,
            "    Set the number of highest resolution levels to be discarded on each dimension. \n");
    fprintf(stdout,
            "    The volume resolution is effectively divided by 2 to the power of the\n");
    fprintf(stdout,
            "    number of discarded levels. The reduce factor is limited by the\n");
    fprintf(stdout,
            "    smallest total number of decomposition levels among tiles.\n");
    fprintf(stdout, "  -l <number of quality layers to decode>\n");
    fprintf(stdout,
            "    Set the maximum number of quality layers to decode. If there are\n");
    fprintf(stdout,
            "    less quality layers than the specified number, all the quality layers\n");
    fprintf(stdout, "    are decoded. \n");
    fprintf(stdout, "  -O original-file \n");
    fprintf(stdout,
            "    This option offers the possibility to compute some quality results  \n");
    fprintf(stdout,
            "    for the decompressed volume, like the PSNR value achieved or the global SSIM value.  \n");
    fprintf(stdout,
            "    Needs the original file in order to compare with the new one.\n");
    fprintf(stdout,
            "    NOTE: Only valid when -r option is 0,0,0 (both original and decompressed volumes have same resolutions) \n");
    fprintf(stdout,
            "    NOTE: If original file is .BIN file, the volume characteristics file shall be defined with the -m option. \n");
    fprintf(stdout, "    (i.e. -O original-BIN-file -m original-IMG-file) \n");
    fprintf(stdout, "  -BE \n");
    fprintf(stdout,
            "    Define that the recovered volume data will be saved with big endian byte order.\n");
    fprintf(stdout, "    By default, little endian byte order is used.\n");
    fprintf(stdout, "\n");
}