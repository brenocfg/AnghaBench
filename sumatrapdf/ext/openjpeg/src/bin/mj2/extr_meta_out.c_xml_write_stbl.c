#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int track_type; int w; int h; int horizresolution; int vertresolution; int depth; int num_br; unsigned int* br; int num_jp2x; int* jp2xdata; int hsub; int vsub; int hoff; int voff; int num_samples; int num_tts; int num_samplestochunk; int num_chunks; TYPE_4__* chunk; TYPE_3__* sample; scalar_t__ same_sample_size; TYPE_2__* sampletochunk; TYPE_1__* tts; scalar_t__ or_fieldorder; scalar_t__ or_fieldcount; scalar_t__ fieldorder; scalar_t__ fieldcount; int /*<<< orphan*/  jp2_struct; scalar_t__* compressorname; } ;
typedef  TYPE_5__ mj2_tk_t ;
struct TYPE_10__ {int offset; } ;
struct TYPE_9__ {int sample_size; } ;
struct TYPE_8__ {int first_chunk; int samples_per_chunk; int sample_descr_idx; } ;
struct TYPE_7__ {int sample_count; int sample_delta; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  derived ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ notes ; 
 int /*<<< orphan*/  raw ; 
 scalar_t__ sampletables ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  uint_to_chars (unsigned int,char*) ; 
 int /*<<< orphan*/  xml_out_frame_jp2h (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void xml_write_stbl(FILE* file, FILE* xmlout, mj2_tk_t *track,
                    unsigned int tnum)
{
    char buf[5], buf33[33];
    int i, len;
    buf[4] = '\0';

    fprintf(xmlout,      "          <SampleTable BoxType=\"stbl\">\n");
    if (notes) {
        fprintf(xmlout,
                "            <!-- What follows are specific instances of generic SampleDescription BoxType=\"stsd\" -->\n");
    }
    switch (track->track_type) {
    case 0:
        // There could be multiple instances of this, but "entry_count" is just a local at read-time.
        // And it's used wrong, too, as count of just visual type, when it's really all 3 types.
        // This is referred to as "smj2" within mj2.c
        fprintf(xmlout,    "            <VisualSampleEntry BoxType=\"mjp2\">\n");
        if (notes) {
            fprintf(xmlout,
                    "            <!-- If multiple instances of this box, only first is shown here. -->\n");
            fprintf(xmlout,
                    "            <!-- Width and Height are in pixels.  Unlike the Track Header, there is no fractional part. -->\n");
            fprintf(xmlout,
                    "            <!-- In mj2_to_metadata implementation, the values are not represented separately from Track Header's values. -->\n");
        }
        /* No shifting required.  If CURRENTSTRUCT gets changed, then may need to revisit treatment of these */
        fprintf(xmlout,    "              <WidthAsInteger>%d</WidthAsInteger>\n",
                track->w);
        fprintf(xmlout,    "              <HeightAsInteger>%d</HeightAsInteger>\n",
                track->h);
// Horizresolution and vertresolution don't require shifting, already stored right in CURRENTSTRUCT
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Resolutions are in pixels per inch, for the highest-resolution component (typically luminance). -->\n");
            fprintf(xmlout,
                    "              <!-- Both stored as fixed-point binary 16.16 values. Decimal values are approximations. -->\n");
            fprintf(xmlout,
                    "              <!-- Typical value for both resolutions is 0x00480000  (72.0) -->\n");
        }
        fprintf(xmlout,    "              <HorizontalRes>\n");
        if (raw) {
            fprintf(xmlout,  "                <AsHex>0x%08x</AsHex>\n",
                    track->horizresolution);
        }
        if (derived) {
            fprintf(xmlout,  "                <AsDecimal>%12.6f</AsDecimal>\n",
                    (double)track->horizresolution / (double)
                    0x00010000);    /* Rate to play presentation  (default = 0x00010000)          */
        }
        fprintf(xmlout,    "              </HorizontalRes>\n");
        fprintf(xmlout,    "              <VerticalRes>\n");
        if (raw) {
            fprintf(xmlout,  "                <AsHex>0x%08x</AsHex>\n",
                    track->vertresolution);
        }
        if (derived) {
            fprintf(xmlout,  "                <AsDecimal>%12.6f</AsDecimal>\n",
                    (double)track->vertresolution / (double)
                    0x00010000);    /* Rate to play presentation  (default = 0x00010000)          */
        }
        fprintf(xmlout,    "              </VerticalRes>\n");

        buf33[0] = '\0';
        for (i = 0; i < 8; i++) {
            uint_to_chars((unsigned int)track->compressorname[i], buf);
            strcat(buf33,
                   buf); /* This loads up (4 * 8) + 1 chars, but trailing ones are usually junk */
        }
        len = (int)
              buf33[0]; /* First byte has string length in bytes.  There may be garbage beyond it. */
        buf33[len + 1] = '\0'; /* Suppress it */
        fprintf(xmlout,    "              <CompressorName>%s</CompressorName>\n",
                buf33 + 1); /* Start beyond first byte */
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Compressor name for debugging.  Standard restricts max length to 31 bytes. -->\n");
            fprintf(xmlout,
                    "              <!-- Usually blank or \"Motion JPEG2000\" -->\n");
        }
        fprintf(xmlout,    "              <Depth>0x%02x</Depth>\n", track->depth);
        if (notes) {
            fprintf(xmlout,  "              <!-- Depth is: -->\n");
            fprintf(xmlout,
                    "              <!--   0x20: alpha channels present (color or grayscale) -->\n");
            fprintf(xmlout,  "              <!--   0x28: grayscale without alpha -->\n");
            fprintf(xmlout,  "              <!--   0x18: color without alpha -->\n");
        }

        xml_out_frame_jp2h(xmlout, &(track->jp2_struct));  /* JP2 Header */

        /* Following subboxes are optional */
        fprintf(xmlout,    "              <FieldCoding BoxType=\"fiel\">\n");
        fprintf(xmlout,    "                <FieldCount>%d</FieldCount>\n",
                (unsigned int)track->fieldcount); /* uchar as 1 byte uint */
        if (notes) {
            fprintf(xmlout,  "                <!-- Must be either 1 or 2 -->\n");
        }
        fprintf(xmlout,    "                <FieldOrder>%d</FieldOrder>\n",
                (unsigned int)track->fieldorder); /* uchar as 1 byte uint */
        if (notes) {
            fprintf(xmlout,
                    "                <!-- When FieldCount=2, FieldOrder means: -->\n");
            fprintf(xmlout,  "                <!--   0: Field coding unknown -->\n");
            fprintf(xmlout,
                    "                <!--   1: Field with topmost line is stored first in sample; fields are in temporal order -->\n");
            fprintf(xmlout,
                    "                <!--   6: Field with topmost line is stored second in sample; fields are in temporal order -->\n");
            fprintf(xmlout,
                    "                <!-- Defaults: FieldCount=1, FieldOrder=0 if FieldCoding box not present -->\n");
            fprintf(xmlout,
                    "                <!-- Current implementation doesn't retain whether box was actually present. -->\n");
        }
        fprintf(xmlout,    "              </FieldCoding>\n");

        fprintf(xmlout,
                "              <MJP2_Profile BoxType=\"jp2p\" Count=\"%d\">\n", track->num_br);
        for (i = 0; i < track->num_br;
                i++) { /* read routine stored in reverse order, so let's undo damage */
            uint_to_chars(track->br[i], buf);
            fprintf(xmlout,  "                <CompatibleBrand>%s</CompatibleBrand>\n",
                    buf);    /*4 characters, each CLi */
        }
        fprintf(xmlout,    "              </MJP2_Profile>\n");

        fprintf(xmlout,
                "              <MJP2_Prefix BoxType=\"jp2x\" Count=\"%d\">\n", track->num_jp2x);
        for (i = 0; i < track->num_jp2x; i++) {
            // We'll probably need better formatting than this
            fprintf(xmlout,  "                <Data>0x%02x</Data>\n",
                    track->jp2xdata[i]);    /* Each entry is single byte */
        }
        fprintf(xmlout,    "              </MJP2_Prefix>\n");

        fprintf(xmlout,
                "              <MJP2_SubSampling BoxType=\"jsub\">\n"); /* These values are all 1 byte */
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Typical subsample value is 2 for 4:2:0 -->\n");
        }
        fprintf(xmlout,    "                <HorizontalSub>%d</HorizontalSub>\n",
                track->hsub);
        fprintf(xmlout,    "                <VerticalSub>%d</VerticalSub>\n",
                track->vsub);
        fprintf(xmlout,    "                <HorizontalOffset>%d</HorizontalOffset>\n",
                track->hoff);
        fprintf(xmlout,    "                <VerticalOffset>%d</VerticalOffset>\n",
                track->voff);
        if (notes) {
            fprintf(xmlout,
                    "                <!-- Typical {horizontal, vertical} chroma offset values: -->\n");
            fprintf(xmlout,
                    "                <!-- 4:2:2 format (CCIR601, H.262, MPEG2, MPEG4, recom. Exif): {0, 0} -->\n");
            fprintf(xmlout,
                    "                <!-- 4:2:2 format (JFIF):                                      {1, 0} -->\n");
            fprintf(xmlout,
                    "                <!-- 4:2:0 format (H.262, MPEG2, MPEG4):                       {0, 1} -->\n");
            fprintf(xmlout,
                    "                <!-- 4:2:0 format (MPEG1, H.261, JFIF, recom. Exif):           {1, 1} -->\n");
        }
        fprintf(xmlout,
                "              </MJP2_SubSampling>\n"); /* These values are all 1 byte */

        fprintf(xmlout,
                "              <MJP2_OriginalFormat BoxType=\"orfo\">\n"); /* Part III Appx. 2 */
        fprintf(xmlout,
                "                <OriginalFieldCount>%u</OriginalFieldCount>\n",
                (unsigned int)track->or_fieldcount); /* uchar as 1-byte uint */
        if (notes) {
            fprintf(xmlout,
                    "                <!-- In original material before encoding.  Must be either 1 or 2 -->\n");
        }
        fprintf(xmlout,
                "                <OriginalFieldOrder>%u</OriginalFieldOrder>\n",
                (unsigned int)track->or_fieldorder); /* uchar as 1-byte uint */
        if (notes) {
            fprintf(xmlout,
                    "                <!-- When FieldCount=2, FieldOrder means: -->\n");
            fprintf(xmlout,  "                <!--   0: Field coding unknown -->\n");
            fprintf(xmlout,
                    "                <!--   11: Topmost line came from the earlier field; -->\n");
            fprintf(xmlout,
                    "                <!--   16:  Topmost line came form the later field. -->\n");
            fprintf(xmlout,
                    "                <!-- Defaults: FieldCount=1, FieldOrder=0 if FieldCoding box not present -->\n");
            fprintf(xmlout,
                    "                <!-- Current implementation doesn't retain whether box was actually present. -->\n");
        }
        fprintf(xmlout,    "              </MJP2_OriginalFormat>\n");
        fprintf(xmlout,    "            </VisualSampleEntry>\n");
        break;
    case 1:
    case 2:
        if (notes) {
            fprintf(xmlout,
                    "            <!-- mj2_to_metadata's data structure doesn't record this currently. -->\n");
        }
        break;
    }
    fprintf(xmlout,      "            <TimeToSample BoxType=\"stts\">\n");
    fprintf(xmlout,      "              <SampleStatistics>\n");
    fprintf(xmlout,      "                <TotalSamples>%d</TotalSamples>\n",
            track->num_samples);
    if (notes) {
        fprintf(xmlout,
                "                <!-- For video, gives the total frames in the track, by summing all entries in the Sample Table -->\n");
    }
    fprintf(xmlout,      "              </SampleStatistics>\n");
    fprintf(xmlout,      "              <SampleEntries EntryCount=\"%d\">\n",
            track->num_tts);
    for (i = 0; i < track->num_tts; i++) {
        fprintf(xmlout,
                "                <Table Entry=\"%u\" SampleCount=\"%d\" SampleDelta=\"%u\" />\n",
                i + 1, track->tts[i].sample_count, track->tts[i].sample_delta);
    }
    fprintf(xmlout,      "              </SampleEntries>\n");
    fprintf(xmlout,      "            </TimeToSample>\n");

    fprintf(xmlout,
            "            <SampleToChunk BoxType=\"stsc\" Count=\"%d\">\n",
            track->num_samplestochunk);
    for (i = 0; i < track->num_samplestochunk; i++) {
        fprintf(xmlout,    "              <FirstChunk>%u</FirstChunk>\n",
                track->sampletochunk[i].first_chunk); /* 4 bytes */
        fprintf(xmlout,    "              <SamplesPerChunk>%u</SamplesPerChunk>\n",
                track->sampletochunk[i].samples_per_chunk); /* 4 bytes */
        fprintf(xmlout,    "              <SampleDescrIndex>%u</SampleDescrIndex>\n",
                track->sampletochunk[i].sample_descr_idx); /* 4 bytes */
    }
    fprintf(xmlout,      "            </SampleToChunk>\n");
    // After reading this info in, track->num_chunks is calculated and a decompressed table established internally.

    fprintf(xmlout,      "            <SampleSize BoxType=\"stsz\">\n");
    if (track->same_sample_size) {
        // all values in track->sample[i].sample_size are equal.  Grab the first one.
        fprintf(xmlout,    "              <Sample_Size>%u</Sample_Size>\n",
                track->sample[0].sample_size);
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Non-zero value means all samples have that size. -->\n");
            fprintf(xmlout,
                    "              <!-- So <Sample_Count> (aka Entry_Count in std.) has no meaning, is suppressed from this output, and no table follows. -->\n");
        }
    } else {
        fprintf(xmlout,    "              <Sample_Size>0</Sample_Size>\n");
        if (notes)
            if (sampletables) {
                fprintf(xmlout,
                        "              <!-- Zero value means samples have different sizes, given in table next of length Sample_Count (aka Entry_Count in std). -->\n");
            } else {
                fprintf(xmlout,
                        "              <!-- Zero value means samples have different sizes, given in table (not shown) of length Sample_Count (aka Entry_Count in std). -->\n");
            }
        fprintf(xmlout,    "              <Sample_Count>%u</Sample_Count>\n",
                track->num_samples);
        if (sampletables)
            for (i = 0; i < (int)track->num_samples; i++) {
                fprintf(xmlout,  "              <EntrySize Num=\"%u\">%u</EntrySize>\n", i + 1,
                        track->sample[i].sample_size);
            }
    }
    fprintf(xmlout,      "            </SampleSize>\n");

    fprintf(xmlout,      "            <ChunkOffset BoxType=\"stco\">\n");
    // Structure not yet - Variant ChunkLargeOffset 'co64'
    fprintf(xmlout,      "              <EntryCount>%u</EntryCount>\n",
            track->num_chunks);
    if (notes) {
        fprintf(xmlout,
                "              <!-- For this implementation, EntryCount shown is one calculated during file read of <SampleToChunk> data. -->\n");
        fprintf(xmlout,
                "              <!-- Implementation will report failure during file read of <ChunkOffset> data if read entry-count disagrees. -->\n");
    }
    if (sampletables)
        for (i = 0; i < (int)track->num_chunks; i++) {
            fprintf(xmlout,  "              <Chunk_Offset Num=\"%d\">%u</Chunk_Offset>\n",
                    i + 1, track->chunk[i].offset);
        }
    fprintf(xmlout,      "            </ChunkOffset>\n");

    fprintf(xmlout,      "          </SampleTable>\n");
}