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
 int JPWL_EXPECTED_COMPONENTS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ opj_has_thread_support () ; 
 char* opj_version () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void decode_help_display(void)
{
    fprintf(stdout,
            "\nThis is the opj_decompress utility from the OpenJPEG project.\n"
            "It decompresses JPEG 2000 codestreams to various image formats.\n"
            "It has been compiled against openjp2 library v%s.\n\n", opj_version());

    fprintf(stdout, "Parameters:\n"
            "-----------\n"
            "\n"
            "  -ImgDir <directory> \n"
            "	Image file Directory path \n"
            "  -OutFor <PBM|PGM|PPM|PNM|PAM|PGX|PNG|BMP|TIF|RAW|RAWL|TGA>\n"
            "    REQUIRED only if -ImgDir is used\n"
            "	Output format for decompressed images.\n");
    fprintf(stdout, "  -i <compressed file>\n"
            "    REQUIRED only if an Input image directory is not specified\n"
            "    Currently accepts J2K-files, JP2-files and JPT-files. The file type\n"
            "    is identified based on its suffix.\n");
    fprintf(stdout, "  -o <decompressed file>\n"
            "    REQUIRED\n"
            "    Currently accepts formats specified above (see OutFor option)\n"
            "    Binary data is written to the file (not ascii). If a PGX\n"
            "    filename is given, there will be as many output files as there are\n"
            "    components: an indice starting from 0 will then be appended to the\n"
            "    output filename, just before the \"pgx\" extension. If a PGM filename\n"
            "    is given and there are more than one component, only the first component\n"
            "    will be written to the file.\n");
    fprintf(stdout, "  -r <reduce factor>\n"
            "    Set the number of highest resolution levels to be discarded. The\n"
            "    image resolution is effectively divided by 2 to the power of the\n"
            "    number of discarded levels. The reduce factor is limited by the\n"
            "    smallest total number of decomposition levels among tiles.\n"
            "  -l <number of quality layers to decode>\n"
            "    Set the maximum number of quality layers to decode. If there are\n"
            "    less quality layers than the specified number, all the quality layers\n"
            "    are decoded.\n");
    fprintf(stdout, "  -x  \n"
            "    Create an index file *.Idx (-x index_name.Idx) \n"
            "  -d <x0,y0,x1,y1>\n"
            "    OPTIONAL\n"
            "    Decoding area\n"
            "    By default all the image is decoded.\n"
            "  -t <tile_number>\n"
            "    OPTIONAL\n"
            "    Set the tile number of the decoded tile. Follow the JPEG2000 convention from left-up to bottom-up\n"
            "    By default all tiles are decoded.\n");
    fprintf(stdout, "  -p <comp 0 precision>[C|S][,<comp 1 precision>[C|S][,...]]\n"
            "    OPTIONAL\n"
            "    Force the precision (bit depth) of components.\n");
    fprintf(stdout,
            "    There shall be at least 1 value. Theres no limit on the number of values (comma separated, last values ignored if too much values).\n"
            "    If there are less values than components, the last value is used for remaining components.\n"
            "    If 'C' is specified (default), values are clipped.\n"
            "    If 'S' is specified, values are scaled.\n"
            "    A 0 value can be specified (meaning original bit depth).\n");
    fprintf(stdout, "  -c first_comp_index[,second_comp_index][,...]\n"
            "    OPTIONAL\n"
            "    To limit the number of components to decoded.\n"
            "    Component indices are numbered starting at 0.\n");
    fprintf(stdout, "  -force-rgb\n"
            "    Force output image colorspace to RGB\n"
            "  -upsample\n"
            "    Downsampled components will be upsampled to image size\n"
            "  -split-pnm\n"
            "    Split output components to different files when writing to PNM\n");
    if (opj_has_thread_support()) {
        fprintf(stdout, "  -threads <num_threads>\n"
                "    Number of threads to use for decoding.\n");
    }
    fprintf(stdout, "  -quiet\n"
            "    Disable output from the library and other output.\n");
    /* UniPG>> */
#ifdef USE_JPWL
    fprintf(stdout, "  -W <options>\n"
            "    Activates the JPWL correction capability, if the codestream complies.\n"
            "    Options can be a comma separated list of <param=val> tokens:\n"
            "    c, c=numcomps\n"
            "       numcomps is the number of expected components in the codestream\n"
            "       (search of first EPB rely upon this, default is %d)\n",
            JPWL_EXPECTED_COMPONENTS);
#endif /* USE_JPWL */
    /* <<UniPG */
    fprintf(stdout, "\n");
}