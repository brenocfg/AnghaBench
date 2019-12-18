#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int x1; int x0; int y1; int y0; int z1; int z0; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_volume_t ;
struct TYPE_26__ {int /*<<< orphan*/  info_handler; int /*<<< orphan*/  warning_handler; int /*<<< orphan*/  error_handler; } ;
typedef  TYPE_3__ opj_event_mgr_t ;
struct TYPE_27__ {char* cp_comment; scalar_t__ cod_format; int decod_format; char* outfile; char* cp_matrice; int /*<<< orphan*/  index; int /*<<< orphan*/  infile; int /*<<< orphan*/  imgfile; } ;
typedef  TYPE_4__ opj_cparameters_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
struct TYPE_28__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_5__ opj_cio_t ;
typedef  int /*<<< orphan*/  opj_cinfo_t ;
struct TYPE_24__ {int prec; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  BIN_DFMT 130 
 int /*<<< orphan*/  CODEC_J2K ; 
 int /*<<< orphan*/  CODEC_J3D ; 
#define  IMG_DFMT 129 
 scalar_t__ J2K_CFMT ; 
 scalar_t__ J3D_CFMT ; 
#define  PGX_DFMT 128 
 TYPE_2__* bintovolume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int cio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* imgtovolume (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  info_callback ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_cio_close (TYPE_5__*) ; 
 TYPE_5__* opj_cio_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opj_create_compress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_destroy_compress (int /*<<< orphan*/ *) ; 
 int opj_encode (int /*<<< orphan*/ *,TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_set_default_encoder_parameters (TYPE_4__*) ; 
 int /*<<< orphan*/  opj_set_event_mgr (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_setup_encoder (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  opj_volume_destroy (TYPE_2__*) ; 
 int parse_cmdline_encoder (int,char**,TYPE_4__*) ; 
 TYPE_2__* pgxtovolume (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warning_callback ; 

int main(int argc, char **argv)
{
    bool bSuccess;
    bool delete_comment = true;
    opj_cparameters_t parameters;   /* compression parameters */
    opj_event_mgr_t event_mgr;      /* event manager */
    opj_volume_t *volume = NULL;

    /*
    configure the event callbacks (not required)
    setting of each callback is optional
    */
    memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
    event_mgr.error_handler = error_callback;
    event_mgr.warning_handler = warning_callback;
    event_mgr.info_handler = info_callback;

    /* set encoding parameters to default values */
    opj_set_default_encoder_parameters(&parameters);

    /* parse input and get user encoding parameters */
    if (parse_cmdline_encoder(argc, argv, &parameters) == 1) {
        return 0;
    }

    if (parameters.cp_comment == NULL) {
        parameters.cp_comment = "Created by OpenJPEG version JP3D";
        /* no need to delete parameters.cp_comment on exit */
        delete_comment = false;
    }

    /* encode the destination volume */
    /* ---------------------------- */
    if (parameters.cod_format == J3D_CFMT || parameters.cod_format == J2K_CFMT) {
        int codestream_length, pixels, bitsin;
        opj_cio_t *cio = NULL;
        FILE *f = NULL;
        opj_cinfo_t* cinfo = NULL;

        /* decode the source volume */
        /* ----------------------- */
        switch (parameters.decod_format) {
        case PGX_DFMT:
            fprintf(stdout, "[INFO] Loading pgx file(s)\n");
            volume = pgxtovolume(parameters.infile, &parameters);
            if (!volume) {
                fprintf(stdout, "[ERROR] Unable to load pgx files\n");
                return 1;
            }
            break;

        case BIN_DFMT:
            fprintf(stdout, "[INFO] Loading bin file\n");
            volume = bintovolume(parameters.infile, parameters.imgfile, &parameters);
            if (!volume) {
                fprintf(stdout, "[ERROR] Unable to load bin file\n");
                return 1;
            }
            break;

        case IMG_DFMT:
            fprintf(stdout, "[INFO] Loading img file\n");
            volume = imgtovolume(parameters.infile, &parameters);
            if (!volume) {
                fprintf(stderr, "[ERROR] Unable to load img file\n");
                return 1;
            }
            break;
        }

        /* get a JP3D or J2K compressor handle */
        if (parameters.cod_format == J3D_CFMT) {
            cinfo = opj_create_compress(CODEC_J3D);
        } else if (parameters.cod_format == J2K_CFMT) {
            cinfo = opj_create_compress(CODEC_J2K);
        }

        /* catch events using our callbacks and give a local context */
        opj_set_event_mgr((opj_common_ptr)cinfo, &event_mgr, stdout);

        /* setup the encoder parameters using the current volume and using user parameters */
        opj_setup_encoder(cinfo, &parameters, volume);

        /* open a byte stream for writing */
        /* allocate memory for all tiles */
        cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0);

        /* encode the volume */
        /*fprintf(stdout, "[INFO] Encode the volume\n");*/
        bSuccess = opj_encode(cinfo, cio, volume, parameters.index);
        if (!bSuccess) {
            opj_cio_close(cio);
            fprintf(stdout, "[ERROR] Failed to encode volume\n");
            return 1;
        }
        codestream_length = cio_tell(cio);
        pixels = (volume->x1 - volume->x0) * (volume->y1 - volume->y0) *
                 (volume->z1 - volume->z0);
        bitsin = pixels * volume->comps[0].prec;
        fprintf(stdout,
                "[RESULT] Volume: %d x %d x %d (x %d bpv)\n Codestream: %d B,  Ratio: %5.3f bpv,  (%5.3f : 1) \n",
                (volume->x1 - volume->x0), (volume->y1 - volume->y0), (volume->z1 - volume->z0),
                volume->comps[0].prec,
                codestream_length, ((double)codestream_length * 8.0 / (double)pixels),
                ((double)bitsin / (8.0 * (double)codestream_length)));

        /* write the buffer to disk */
        f = fopen(parameters.outfile, "wb");
        if (!f) {
            fprintf(stdout, "[ERROR] Failed to open %s for writing\n", parameters.outfile);
            return 1;
        }
        fwrite(cio->buffer, 1, codestream_length, f);
        fclose(f);

        /* close and free the byte stream */
        opj_cio_close(cio);

        /* free remaining compression structures */
        opj_destroy_compress(cinfo);
    } else {
        fprintf(stdout, "[ERROR] Cod_format != JP3d !!! \n");
        return 1;
    }

    /* free user parameters structure */
    if (delete_comment) {
        if (parameters.cp_comment) {
            free(parameters.cp_comment);
        }
    }
    if (parameters.cp_matrice) {
        free(parameters.cp_matrice);
    }

    /* free volume data */
    opj_volume_destroy(volume);

    return 0;
}