#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ opj_option_t ;
struct TYPE_8__ {scalar_t__* infile; scalar_t__* outfile; int m_verbose; int /*<<< orphan*/  decod_format; } ;
typedef  TYPE_2__ opj_dparameters_t ;
typedef  int /*<<< orphan*/  long_option ;
struct TYPE_9__ {scalar_t__ set_out_format; char* imgdirpath; int set_imgdir; int /*<<< orphan*/  flag; } ;
typedef  TYPE_3__ img_fol_t ;

/* Variables and functions */
#define  J2K_CFMT 130 
#define  JP2_CFMT 129 
#define  JPT_CFMT 128 
 int /*<<< orphan*/  REQ_ARG ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  decode_help_display () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  infile_format (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int opj_getopt_long (int,char**,char const*,TYPE_1__*,int) ; 
 char* opj_optarg ; 
 int /*<<< orphan*/  opj_strcpy_s (scalar_t__*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int parse_cmdline_decoder(int argc, char **argv,
                                 opj_dparameters_t *parameters, img_fol_t *img_fol)
{
    int totlen, c;
    opj_option_t long_option[] = {
        {"ImgDir", REQ_ARG, NULL, 'y'}
    };
    const char optlist[] = "i:o:f:hv";

    totlen = sizeof(long_option);
    img_fol->set_out_format = 0;
    do {
        c = opj_getopt_long(argc, argv, optlist, long_option, totlen);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 'i': {         /* input file */
            char *infile = opj_optarg;
            parameters->decod_format = infile_format(infile);
            switch (parameters->decod_format) {
            case J2K_CFMT:
                break;
            case JP2_CFMT:
                break;
            case JPT_CFMT:
                break;
            default:
                fprintf(stderr,
                        "[ERROR] Unknown input file format: %s \n"
                        "        Known file formats are *.j2k, *.jp2, *.jpc or *.jpt\n",
                        infile);
                return 1;
            }
            if (opj_strcpy_s(parameters->infile, sizeof(parameters->infile), infile) != 0) {
                fprintf(stderr, "[ERROR] Path is too long\n");
                return 1;
            }
        }
        break;

        /* ------------------------------------------------------ */

        case 'o': {   /* output file */
            if (opj_strcpy_s(parameters->outfile, sizeof(parameters->outfile),
                             opj_optarg) != 0) {
                fprintf(stderr, "[ERROR] Path is too long\n");
                return 1;
            }
        }
        break;

        /* ----------------------------------------------------- */
        case 'f':             /* flag */
            img_fol->flag = atoi(opj_optarg);
            break;
        /* ----------------------------------------------------- */

        case 'h':           /* display an help description */
            decode_help_display();
            return 1;

        /* ------------------------------------------------------ */

        case 'y': {         /* Image Directory path */
            img_fol->imgdirpath = (char*)malloc(strlen(opj_optarg) + 1);
            if (img_fol->imgdirpath == NULL) {
                return 1;
            }
            strcpy(img_fol->imgdirpath, opj_optarg);
            img_fol->set_imgdir = 1;
        }
        break;

        /* ----------------------------------------------------- */

        case 'v': {         /* Verbose mode */
            parameters->m_verbose = 1;
        }
        break;

        /* ----------------------------------------------------- */
        default:
            fprintf(stderr, "[WARNING] An invalid option has been ignored.\n");
            break;
        }
    } while (c != -1);

    /* check for possible errors */
    if (img_fol->set_imgdir == 1) {
        if (!(parameters->infile[0] == 0)) {
            fprintf(stderr, "[ERROR] options -ImgDir and -i cannot be used together.\n");
            return 1;
        }
        if (img_fol->set_out_format == 0) {
            fprintf(stderr,
                    "[ERROR] When -ImgDir is used, -OutFor <FORMAT> must be used.\n");
            fprintf(stderr, "Only one format allowed.\n"
                    "Valid format are PGM, PPM, PNM, PGX, BMP, TIF, RAW and TGA.\n");
            return 1;
        }
        if (!(parameters->outfile[0] == 0)) {
            fprintf(stderr, "[ERROR] options -ImgDir and -o cannot be used together\n");
            return 1;
        }
    } else {
        if (parameters->infile[0] == 0) {
            fprintf(stderr, "[ERROR] Required parameter is missing\n");
            fprintf(stderr, "Example: %s -i image.j2k\n", argv[0]);
            fprintf(stderr, "   Help: %s -h\n", argv[0]);
            return 1;
        }
    }

    return 0;
}