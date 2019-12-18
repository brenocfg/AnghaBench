#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_6__ {scalar_t__ track_type; unsigned int num_samples; int /*<<< orphan*/ * sample; } ;
typedef  TYPE_1__ mj2_tk_t ;
typedef  int /*<<< orphan*/  mj2_sample_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ xml_out_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_write_mdia (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  xml_write_tkhd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  xml_write_udta (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 

void xml_write_trak(FILE* file, FILE* xmlout, mj2_tk_t *track,
                    unsigned int tnum, unsigned int sampleframe, opj_event_mgr_t *event_mgr)
{
    fprintf(xmlout,    "    <Track BoxType=\"trak\" Instance=\"%d\">\n", tnum);
    xml_write_tkhd(file, xmlout, track, tnum);
    // TO DO: TrackReferenceContainer 'tref'  just used in hint track
    // TO DO: EditListContainer 'edts', contains EditList 'elst' with media-time, segment-duration, media-rate
    xml_write_mdia(file, xmlout, track, tnum);
    xml_write_udta(file, xmlout, track,
                   tnum); // NO-OP so far.  Optional UserData 'udta', can contain multiple Copyright 'cprt'

    if (track->track_type == 0) { /* Only do for visual track */
        /* sampleframe is from user option -f.  1 = first frame */
        /* sampleframe of 0 is a user requests: no jp2 header */
        /* Treat out-of-bounds values in the same way */
        if (sampleframe > 0 && sampleframe <= track->num_samples) {
            mj2_sample_t *sample;
            unsigned int snum;

            snum = sampleframe - 1;
            // Someday maybe do a smart range scan... for (snum=0; snum < track->num_samples; snum++){
            //  fprintf(stdout,"Frame %d: ",snum+1);
            sample = &track->sample[snum];
            if (xml_out_frame(file, xmlout, sample, snum, event_mgr)) {
                return;    /* Not great error handling here */
            }
        }
    }
    fprintf(xmlout,    "    </Track>\n");
}