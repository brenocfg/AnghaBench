#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* tk; } ;
typedef  TYPE_1__ opj_mj2_t ;
struct TYPE_15__ {int /*<<< orphan*/  info_handler; int /*<<< orphan*/  warning_handler; int /*<<< orphan*/  error_handler; } ;
typedef  TYPE_2__ opj_event_mgr_t ;
struct TYPE_16__ {scalar_t__ mj2_handle; } ;
typedef  TYPE_3__ opj_dinfo_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
struct TYPE_17__ {scalar_t__ track_type; unsigned int num_samples; TYPE_5__* sample; } ;
typedef  TYPE_4__ mj2_tk_t ;
struct TYPE_18__ {scalar_t__ sample_size; scalar_t__ offset; } ;
typedef  TYPE_5__ mj2_sample_t ;
typedef  TYPE_2__ mj2_dparameters_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (unsigned char*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info_callback ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* mj2_create_decompress () ; 
 int /*<<< orphan*/  mj2_destroy_decompress (TYPE_1__*) ; 
 scalar_t__ mj2_read_struct (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mj2_setup_decoder (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  opj_set_event_mgr (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warning_callback ; 

int main(int argc, char *argv[])
{
    opj_dinfo_t* dinfo;
    opj_event_mgr_t event_mgr;      /* event manager */
    int tnum;
    unsigned int snum;
    opj_mj2_t *movie;
    mj2_tk_t *track;
    mj2_sample_t *sample;
    unsigned char* frame_codestream;
    FILE *file, *outfile;
    char outfilename[50];
    mj2_dparameters_t parameters;

    if (argc != 3) {
        printf("Usage: %s mj2filename output_location\n", argv[0]);
        printf("Example: %s foreman.mj2 output/foreman\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");

    if (!file) {
        fprintf(stderr, "failed to open %s for reading\n", argv[1]);
        return 1;
    }

    /*
    configure the event callbacks (not required)
    setting of each callback is optional
    */
    memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
    event_mgr.error_handler = error_callback;
    event_mgr.warning_handler = warning_callback;
    event_mgr.info_handler = info_callback;

    /* get a MJ2 decompressor handle */
    dinfo = mj2_create_decompress();

    /* catch events using our callbacks and give a local context */
    opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

    /* setup the decoder decoding parameters using user parameters */
    memset(&parameters, 0, sizeof(mj2_dparameters_t));
    movie = (opj_mj2_t*) dinfo->mj2_handle;
    mj2_setup_decoder(movie, &parameters);

    if (mj2_read_struct(file, movie)) { /* Creating the movie structure*/
        return 1;
    }

    /* Decode first video track */
    tnum = 0;
    while (movie->tk[tnum].track_type != 0) {
        tnum ++;
    }

    track = &movie->tk[tnum];

    fprintf(stdout, "Extracting %d frames from file...\n", track->num_samples);

    for (snum = 0; snum < track->num_samples; snum++) {
        sample = &track->sample[snum];
        frame_codestream = (unsigned char*) malloc(sample->sample_size -
                           8); /* Skipping JP2C marker*/
        fseek(file, sample->offset + 8, SEEK_SET);
        fread(frame_codestream, sample->sample_size - 8, 1,
              file); /* Assuming that jp and ftyp markers size do*/

        sprintf(outfilename, "%s_%05d.j2k", argv[2], snum);
        outfile = fopen(outfilename, "wb");
        if (!outfile) {
            fprintf(stderr, "failed to open %s for writing\n", outfilename);
            return 1;
        }
        fwrite(frame_codestream, sample->sample_size - 8, 1, outfile);
        fclose(outfile);
        free(frame_codestream);
    }
    fclose(file);
    fprintf(stdout, "%d frames correctly extracted\n", snum);

    /* free remaining structures */
    if (dinfo) {
        mj2_destroy_decompress((opj_mj2_t*)dinfo->mj2_handle);
    }

    return 0;
}