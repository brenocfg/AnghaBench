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

__attribute__((used)) static void help_display()
{
    fprintf(stdout, "HELP for frames_to_mj2\n----\n\n");
    fprintf(stdout, "- the -h option displays this help information on screen\n\n");


    fprintf(stdout, "List of parameters for the MJ2 encoder:\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "REMARKS:\n");
    fprintf(stdout, "---------\n");
    fprintf(stdout, "\n");
    fprintf
    (stdout, "The markers written to the main_header are : SOC SIZ COD QCD COM.\n");
    fprintf
    (stdout, "COD and QCD never appear in the tile_header.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "By default:\n");
    fprintf(stdout, "------------\n");
    fprintf(stdout, "\n");
    fprintf(stdout, " * Lossless\n");
    fprintf(stdout, " * 1 tile\n");
    fprintf(stdout, " * Size of precinct : 2^15 x 2^15 (means 1 precinct)\n");
    fprintf(stdout, " * Size of code-block : 64 x 64\n");
    fprintf(stdout, " * Number of resolutions: 6\n");
    fprintf(stdout, " * No SOP marker in the codestream\n");
    fprintf(stdout, " * No EPH marker in the codestream\n");
    fprintf(stdout, " * No sub-sampling in x or y direction\n");
    fprintf(stdout, " * No mode switch activated\n");
    fprintf(stdout, " * Progression order: LRCP\n");
    fprintf(stdout, " * No index file\n");
    fprintf(stdout, " * No ROI upshifted\n");
    fprintf(stdout, " * No offset of the origin of the image\n");
    fprintf(stdout, " * No offset of the origin of the tiles\n");
    fprintf(stdout, " * Reversible DWT 5-3\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Parameters:\n");
    fprintf(stdout, "------------\n");
    fprintf(stdout, "\n");
    fprintf
    (stdout, "Required Parameters (except with -h):\n");
    fprintf
    (stdout, "-i : source file      (-i source.yuv) \n");
    fprintf
    (stdout, "-o : destination file (-o dest.mj2) \n");
    fprintf
    (stdout, "Optional Parameters:\n");
    fprintf(stdout, "-h : display the help information \n");
    fprintf(stdout,
            "-r : different compression ratios for successive layers (-r 20,10,5)\n");
    fprintf(stdout,
            "     - The rate specified for each quality level is the desired \n");
    fprintf(stdout, "       compression factor.\n");
    fprintf(stdout, "       Example: -r 20,10,1 means quality 1: compress 20x, \n");
    fprintf(stdout,
            "       quality 2: compress 10x and quality 3: compress lossless\n");
    fprintf(stdout, "       (options -r and -q cannot be used together)\n");

    fprintf(stdout, "-q : different psnr for successive layers (-q 30,40,50) \n");
    fprintf(stdout, "        (options -r and -q cannot be used together)\n");

    fprintf(stdout, "-n : number of resolutions (-n 3) \n");
    fprintf(stdout, "-b : size of code block (-b 32,32) \n");
    fprintf(stdout, "-c : size of precinct (-c 128,128) \n");
    fprintf(stdout, "-t : size of tile (-t 512,512) \n");
    fprintf
    (stdout, "-p : progression order (-p LRCP) [LRCP, RLCP, RPCL, PCRL, CPRL] \n");
    fprintf
    (stdout, "-s : subsampling factor (-s 2,2) [-s X,Y] \n");
    fprintf(stdout, "     Remark: subsampling bigger than 2 can produce error\n");
    fprintf
    (stdout, "-S : write SOP marker before each packet \n");
    fprintf
    (stdout, "-E : write EPH marker after each header packet \n");
    fprintf
    (stdout, "-M : mode switch (-M 3) [1=BYPASS(LAZY) 2=RESET 4=RESTART(TERMALL)\n");
    fprintf
    (stdout, "             8=VSC 16=ERTERM(SEGTERM) 32=SEGMARK(SEGSYM)] \n");
    fprintf
    (stdout, "             Indicate multiple modes by adding their values. \n");
    fprintf
    (stdout, "             Example: RESTART(4) + RESET(2) + SEGMARK(32) = -M 38\n");
    fprintf
    (stdout, "-R : c=%%d,U=%%d : quantization indices upshifted \n");
    fprintf
    (stdout, "             for component c=%%d [%%d = 0,1,2]\n");
    fprintf
    (stdout, "             with a value of U=%%d [0 <= %%d <= 37] (i.e. -ROI:c=0,U=25) \n");
    fprintf
    (stdout, "-d : offset of the origin of the image (-d 150,300) \n");
    fprintf
    (stdout, "-T : offset of the origin of the tiles (-T 100,75) \n");
    fprintf(stdout, "-I : use the irreversible DWT 9-7 (-I) \n");
    fprintf(stdout, "-W : image width, height and the dx and dy subsampling \n");
    fprintf(stdout, "        of the Cb and Cr components for YUV files \n");
    fprintf(stdout,
            "        (default is '352,288,2,2' for CIF format's 352x288 and 4:2:0)\n");
    fprintf(stdout, "-F : video frame rate (set to 25 by default)\n");
    fprintf(stdout, "-D : depth, precision in bits [8 .. 16]; default:8\n");
    fprintf(stdout, "-C : comment\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "IMPORTANT:\n");
    fprintf(stdout, "-----------\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "The index file has the structure below:\n");
    fprintf(stdout, "---------------------------------------\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Image_height Image_width\n");
    fprintf(stdout, "progression order\n");
    fprintf(stdout, "Tiles_size_X Tiles_size_Y\n");
    fprintf(stdout, "Components_nb\n");
    fprintf(stdout, "Layers_nb\n");
    fprintf(stdout, "decomposition_levels\n");
    fprintf(stdout, "[Precincts_size_X_res_Nr Precincts_size_Y_res_Nr]...\n");
    fprintf(stdout, "   [Precincts_size_X_res_0 Precincts_size_Y_res_0]\n");
    fprintf(stdout, "Main_header_end_position\n");
    fprintf(stdout, "Codestream_size\n");
    fprintf(stdout,
            "Tile_0 start_pos end_Theader end_pos TotalDisto NumPix MaxMSE\n");
    fprintf(stdout,
            "Tile_1   ''           ''        ''        ''       ''    ''\n");
    fprintf(stdout, "...\n");
    fprintf(stdout,
            "Tile_Nt   ''           ''        ''        ''       ''    ''\n");
    fprintf(stdout,
            "Tpacket_0 Tile layer res. comp. prec. start_pos end_pos disto\n");
    fprintf(stdout, "...\n");
    fprintf(stdout,
            "Tpacket_Np ''   ''    ''   ''    ''       ''       ''     ''\n");

    fprintf(stdout, "MaxDisto\n");

    fprintf(stdout, "TotalDisto\n\n");
}