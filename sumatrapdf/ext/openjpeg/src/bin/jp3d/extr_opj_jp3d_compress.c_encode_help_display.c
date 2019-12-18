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

void encode_help_display()
{
    fprintf(stdout, "List of parameters for the JPEG2000 Part 10 encoder:\n");
    fprintf(stdout, "------------\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Required Parameters (except with -h):\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-i           : source file  (-i source.bin or source*.pgx) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-m           : source characteristics file (-m imgfile.img) \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-o           : destination file (-o dest.jp3d) \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Optional Parameters:\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-h           : display the help information \n ");
    fprintf(stdout, "\n");
    fprintf(stdout, "-n           : number of resolutions (-n 3,3,3) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-I           : use the irreversible transforms: ICT + DWT 9-7 (-I) \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-C           : coding algorithm (-C 2EB) [2EB, 3EB] \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-r           : different compression ratios for successive layers (-r 20,10,5)\n ");
    fprintf(stdout,
            "	         - The rate specified for each quality level is the desired compression factor.\n");
    fprintf(stdout, "	         - Rate 1 means lossless compression\n");
    fprintf(stdout,
            "               (options -r and -q cannot be used together)\n ");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-q           : different psnr for successive layers (-q 30,40,50) \n ");
    fprintf(stdout,
            "               (options -r and -q cannot be used together)\n ");
    fprintf(stdout, "\n");
    fprintf(stdout, "-b           : size of code block (-b 32,32,32) \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-c           : size of precinct (-c 128,128,128) \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-t           : size of tile (-t 512,512,512) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-p           : progression order (-p LRCP) [LRCP, RLCP, RPCL, PCRL, CPRL] \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-s           : subsampling factor (-s 2,2,2) [-s X,Y,Z] \n");
    fprintf(stdout, "			  - Remark: subsampling bigger than 2 can produce error\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-SOP         : write SOP marker before each packet \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-EPH         : write EPH marker after each header packet \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-M           : code-block style (-M 0) [1=BYPASS(LAZY) 2=RESET 4=RESTART(TERMALL)\n");
    fprintf(stdout, "                 8=VSC 16=PTERM 32=SEGSYM 64=3DCTXT] \n");
    fprintf(stdout,
            "                 Indicate multiple modes by adding their values. \n");
    fprintf(stdout,
            "                 ex: RESTART(4) + RESET(2) + SEGMARK(32) = -M 38\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "-D           : define DC offset (-D 12) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-x           : create an index file *.Idx (-x index_name.Idx) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-ROI         : c=%%d,U=%%d : quantization indices upshifted \n");
    fprintf(stdout, "               for component c=%%d [%%d = 0,1,2]\n");
    fprintf(stdout,
            "               with a value of U=%%d [0 <= %%d <= 37] (i.e. -ROI:c=0,U=25) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-d           : offset of the origin of the volume (-d 150,300,100) \n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "-l           : offset of the origin of the tiles (-l 100,75,25) \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "DEFAULT CODING:\n");
    fprintf(stdout, "------------\n");
    fprintf(stdout, "\n");
    fprintf(stdout, " * Lossless\n");
    fprintf(stdout, " * 1 tile\n");
    fprintf(stdout,
            " * Size of precinct : 2^15 x 2^15 x 2^15 (means 1 precinct)\n");
    fprintf(stdout, " * Size of code-block : 64 x 64 x 64\n");
    fprintf(stdout, " * Number of resolutions in x, y and z axis: 3\n");
    fprintf(stdout, " * No SOP marker in the codestream\n");
    fprintf(stdout, " * No EPH marker in the codestream\n");
    fprintf(stdout, " * No sub-sampling in x, y or z direction\n");
    fprintf(stdout, " * No mode switch activated\n");
    fprintf(stdout, " * Progression order: LRCP\n");
    fprintf(stdout, " * No index file\n");
    fprintf(stdout, " * No ROI upshifted\n");
    fprintf(stdout, " * No offset of the origin of the volume\n");
    fprintf(stdout, " * No offset of the origin of the tiles\n");
    fprintf(stdout, " * Reversible DWT 5-3 on each 2D slice\n");
    fprintf(stdout, " * Coding algorithm: 2D-EBCOT \n");
    fprintf(stdout, "\n");
    fprintf(stdout, "REMARKS:\n");
    fprintf(stdout, "---------\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "- The markers written to the main_header are : SOC SIZ COD QCD COM.\n");
    fprintf(stdout,
            "- COD and QCD markers will never appear in the tile_header.\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "- You need enough disk space memory (twice the original) to encode \n");
    fprintf(stdout,
            "the volume,i.e. for a 1.5 GB volume you need a minimum of 3GB of disk memory)\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "- When loading *.pgx files, a relative path to directory is needed for input argument \n");
    fprintf(stdout,
            " followed by the common prefix of the slices and a '*' character representing sequential numeration.\n");
    fprintf(stdout, "( -i relativepath/slices*.pgx )\n");
    fprintf(stdout, "\n");
    fprintf(stdout, " - The index file has the structure below:\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "\t	Image_height Image_width Image_depth\n");
    fprintf(stdout, "\t	Progression order: 0 (LRCP)\n");
    fprintf(stdout, "\t	Tiles_size_X Tiles_size_Y Tiles_size_Z\n");
    fprintf(stdout, "\t	Components_nb\n");
    fprintf(stdout, "\t	Layers_nb\n");
    fprintf(stdout, "\t	Decomposition_levels\n");
    fprintf(stdout,
            "\t	[Precincts_size_X_res_Nr Precincts_size_Y_res_Nr Precincts_size_Z_res_Nr]\n\t  ...\n");
    fprintf(stdout,
            "\t	[Precincts_size_X_res_0 Precincts_size_Y_res_0 Precincts_size_Z_res_0]\n");
    fprintf(stdout, "\t	Main_header_end_position\n");
    fprintf(stdout, "\t	Codestream_size\n");
    fprintf(stdout,
            "\t	Tile_0 [start_pos end_header end_pos TotalDisto NumPix MaxMSE]\n");
    fprintf(stdout, "\t	...\n");
    fprintf(stdout,
            "\t	Tile_Nt [  ''         ''        ''        ''       ''    ''  ]\n");
    fprintf(stdout,
            "\t  Tpacket_0 [Tile layer res. comp. prec. start_pos end_pos disto]\n");
    fprintf(stdout, "\t  ...\n");
    fprintf(stdout,
            "\t  Tpacket_Np [''   ''    ''   ''    ''       ''       ''     '' ]\n");
    fprintf(stdout, "\t  MaxDisto\n");
    fprintf(stdout, "\t  TotalDisto\n\n");
    fprintf(stdout, "\n");

}