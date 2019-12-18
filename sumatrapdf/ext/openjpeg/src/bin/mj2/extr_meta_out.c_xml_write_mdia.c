#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int creation_time; int modification_time; int timescale; int duration; int track_type; int graphicsmode; int* opcolor; int balance; int maxPDUsize; int avgPDUsize; int maxbitrate; int avgbitrate; int slidingavgbitrate; int num_url; int num_urn; TYPE_2__* urn; TYPE_1__* url; scalar_t__ language; } ;
typedef  TYPE_3__ mj2_tk_t ;
struct TYPE_7__ {int /*<<< orphan*/ * location; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {int /*<<< orphan*/ * location; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ derived ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  int16_to_3packedchars (short,char*) ; 
 scalar_t__ notes ; 
 scalar_t__ raw ; 
 int /*<<< orphan*/  uint_to_chars (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_time_out (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xml_write_stbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,unsigned int) ; 

void xml_write_mdia(FILE* file, FILE* xmlout, mj2_tk_t *track,
                    unsigned int tnum)
{
    char buf[5];
    int i, k;
    buf[4] = '\0';

    fprintf(xmlout,    "      <Media BoxType=\"mdia\">\n");
    fprintf(xmlout,    "        <MediaHeader BoxType=\"mdhd\">\n");
    fprintf(xmlout,    "          <CreationTime>\n");
    if (raw) {
        fprintf(xmlout,  "            <InSeconds>%u</InSeconds>\n",
                track->creation_time);
    }
    if (notes) {
        fprintf(xmlout,
                "            <!-- Seconds since start of Jan. 1, 1904 UTC (Greenwich) -->\n");
    }
    /*  2082844800 = seconds between 1/1/04 and 1/1/70 */
    /* There's still a time zone offset problem not solved... but spec is ambiguous as to whether stored time
       should be local or UTC */
    if (derived) {
        fprintf(xmlout,  "            <AsLocalTime>");
        xml_time_out(xmlout, track->creation_time - 2082844800);
        fprintf(xmlout, "</AsLocalTime>\n");
    }
    fprintf(xmlout,    "          </CreationTime>\n");
    fprintf(xmlout,    "          <ModificationTime>\n");
    if (raw) {
        fprintf(xmlout,  "            <InSeconds>%u</InSeconds>\n",
                track->modification_time);
    }
    if (derived) {
        fprintf(xmlout,  "            <AsLocalTime>");
        xml_time_out(xmlout, track->modification_time - 2082844800);
        fprintf(xmlout, "</AsLocalTime>\n");
    }
    fprintf(xmlout,    "          </ModificationTime>\n");
    fprintf(xmlout,    "          <Timescale>%d</Timescale>\n", track->timescale);
    if (notes) {
        fprintf(xmlout,
                "          <!-- Timescale defines time units in one second -->\n");
    }
    fprintf(xmlout,    "          <Duration>\n");
    if (raw) {
        fprintf(xmlout,  "            <InTimeUnits>%u</InTimeUnits>\n",
                track->duration);
    }
    if (derived) {
        fprintf(xmlout,  "            <InSeconds>%12.3f</InSeconds>\n",
                (double)track->duration / (double)
                track->timescale);    // Make this double later to get fractional seconds
    }
    fprintf(xmlout,    "          </Duration>\n");
    int16_to_3packedchars((short int)track->language, buf);
    fprintf(xmlout,    "          <Language>%s</Language>\n", buf);    /* 3 chars */
    fprintf(xmlout,    "        </MediaHeader>\n");
    fprintf(xmlout,    "        <HandlerReference BoxType=\"hdlr\">\n");
    switch (track->track_type) {
    case 0:
        fprintf(xmlout,
                "          <HandlerType Code=\"vide\">video media track</HandlerType>\n");
        break;
    case 1:
        fprintf(xmlout,  "          <HandlerType Code=\"soun\">Sound</HandlerType>\n");
        break;
    case 2:
        fprintf(xmlout,  "          <HandlerType Code=\"hint\">Hint</HandlerType>\n");
        break;
    }
    if (notes) {
        fprintf(xmlout,
                "          <!-- String value shown is not actually read from file. -->\n");
        fprintf(xmlout,
                "          <!-- Shown value is one used for our encode. -->\n");
    }
    fprintf(xmlout,    "        </HandlerReference>\n");
    fprintf(xmlout,    "        <MediaInfoContainer BoxType=\"minf\">\n");
    switch (track->track_type) {
    case 0:
        fprintf(xmlout,  "          <VideoMediaHeader BoxType=\"vmhd\">\n");
        fprintf(xmlout,  "            <GraphicsMode>0x%02x</GraphicsMode>\n",
                track->graphicsmode);
        if (notes) {
            fprintf(xmlout, "            <!-- Enumerated values of graphics mode: -->\n");
            fprintf(xmlout, "            <!--  0x00 = copy (over existing image); -->\n");
            fprintf(xmlout,
                    "            <!--  0x24 = transparent; 'blue-screen' this image using opcolor; -->\n");
            fprintf(xmlout,
                    "            <!--  0x100 = alpha; alpha-blend this image -->\n");
            /*    fprintf(xmlout,"            <!--  0x101 = whitealpha; alpha-blend this image, which has been blended with white; -->\n"); This was evidently dropped upon amendment */
            fprintf(xmlout,
                    "            <!--  0x102 = pre-multiplied black alpha; image has been already been alpha-blended with black. -->\n");
            fprintf(xmlout,
                    "            <!--  0x110 = component alpha; blend alpha channel(s) and color channels individually. -->\n");
        }
        fprintf(xmlout,  "            <Opcolor>\n");
        fprintf(xmlout,  "              <Red>0x%02x</Red>\n", track->opcolor[0]);
        fprintf(xmlout,  "              <Green>0x%02x</Green>\n", track->opcolor[1]);
        fprintf(xmlout,  "              <Blue>0x%02x</Blue>\n", track->opcolor[2]);
        fprintf(xmlout,  "            </Opcolor>\n");
        fprintf(xmlout,  "          </VideoMediaHeader>\n");
        break;
    case 1:
        fprintf(xmlout,  "          <SoundMediaHeader BoxType=\"smhd\">\n");
#ifdef CURRENTSTRUCT
        track->balance = track->balance << 8;
#endif
        fprintf(xmlout,  "            <Balance>\n");
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Track audio balance fixes mono track in stereo space. -->\n");
            fprintf(xmlout,
                    "              <!-- Stored as fixed-point binary 8.8 value. Decimal value is approximation. -->\n");
            fprintf(xmlout,
                    "              <!-- 0.0 = center, -1.0 = full left, 1.0 = full right -->\n");
        }
        if (raw) {
            fprintf(xmlout, "              <AsHex>0x%04x</AsHex>\n", track->balance);
        }
        if (derived) {
            fprintf(xmlout, "              <AsDecimal>%6.3f</AsDecimal>\n",
                    (double)track->balance / (double)0x0100);
        }
        fprintf(xmlout,  "            </Balance>\n");
#ifdef CURRENTSTRUCT
        if (notes) {
            fprintf(xmlout,
                    "            <!-- Current m2j_to_metadata implementation always shows bits to right of decimal as zeroed. -->\n");
        }
        track->balance = track->balance >> 8;
#endif
        fprintf(xmlout,  "          </SoundMediaHeader>\n");
        break;
    case 2:
        fprintf(xmlout,  "          <HintMediaHeader BoxType=\"hmhd\">\n");
        fprintf(xmlout,  "            <MaxPDU_Size>%d</MaxPDU_Size>\n",
                track->maxPDUsize);
        if (notes) {
            fprintf(xmlout,
                    "            <!-- Size in bytes of largest PDU in this hint stream. -->\n");
        }
        fprintf(xmlout,  "            <AvgPDU_Size>%d</AvgPDU_Size>\n",
                track->avgPDUsize);
        if (notes) {
            fprintf(xmlout,
                    "            <!-- Average size in bytes of a PDU over the entire presentation. -->\n");
        }
        fprintf(xmlout,  "            <MaxBitRate>%d</MaxBitRate>\n",
                track->maxbitrate);
        if (notes) {
            fprintf(xmlout,
                    "            <!-- Maximum rate in bits per second over any window of 1 second. -->\n");
        }
        fprintf(xmlout,  "            <AvgBitRate>%d</AvgBitRate>\n",
                track->avgbitrate);
        if (notes) {
            fprintf(xmlout,
                    "            <!-- Averate rate in bits per second over the entire presentation. -->\n");
        }
        fprintf(xmlout,  "            <SlidingAvgBit>%d</SlidingAvgBitRate>\n",
                track->slidingavgbitrate);
        if (notes) {
            fprintf(xmlout,
                    "            <!-- Maximum rate in bits per second over any window of one minute. -->\n");
        }
        fprintf(xmlout,  "          </HintMediaHeader>\n");
        break;
    }
    fprintf(xmlout,    "          <DataInfo BoxType=\"dinf\">\n");
    fprintf(xmlout,
            "            <DataReference BoxType=\"dref\"  URL_Count=\"%d\" URN_Count=\"%d\">\n",
            track->num_url, track->num_urn); // table w. flags, URLs, URNs
    // Data structure does not distinguish between single URL, single URN, or DREF table or URLs & URNs.
    // We could infer those, but for now just present everything as a DREF table.
    if (notes) {
        fprintf(xmlout,
                "              <!-- No entries here mean that file is self-contained, as required by Simple Profile. -->\n");
    }
    for (k = 0; k < track->num_url; k++) {
        fprintf(xmlout,
                "            <DataEntryUrlBox BoxType=\"url[space]\">\n"); // table w. flags, URLs, URNs
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Only the first 16 bytes of URL location are recorded in mj2_to_metadata data structure. -->\n");
        }
        for (i = 0; i < 4; i++) {
            uint_to_chars(track->url[track->num_url].location[i], buf);
            fprintf(xmlout,  "              <Location>%s</Location>\n");
        }
        fprintf(xmlout,
                "            </DataEntryUrlBox>\n"); // table w. flags, URLs, URNs
    }
    for (k = 0; k < track->num_urn; k++) {
        fprintf(xmlout,
                "            <DataEntryUrnBox BoxType=\"urn[space]\">\n"); // table w. flags, URLs, URNs
        // Only the first 16 bytes are recorded in the data structure currently.
        if (notes) {
            fprintf(xmlout,
                    "              <!-- Only the first 16 bytes each of URN name and optional location are recorded in mj2_to_metadata data structure. -->\n");
        }
        fprintf(xmlout,  "              <Name>");
        for (i = 0; i < 4; i++) {
            uint_to_chars(track->urn[track->num_urn].name[i], buf);
            fprintf(xmlout, "%s", buf);
        }
        fprintf(xmlout,  "</Name>\n");
        fprintf(xmlout,  "              <Location>");
        for (i = 0; i < 4; i++) {
            uint_to_chars(track->urn[track->num_urn].location[i], buf);
            fprintf(xmlout, "%s");
        }
        fprintf(xmlout,  "</Location>\n");
        fprintf(xmlout,  "            </DataEntryUrnBox>\n");
    }
    fprintf(xmlout,    "            </DataReference>\n");
    fprintf(xmlout,    "          </DataInfo>\n");

    xml_write_stbl(file, xmlout, track, tnum); /* SampleTable */

    fprintf(xmlout,    "        </MediaInfoContainer>\n");
    fprintf(xmlout,    "      </Media>\n");
}