#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* tccps; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_5__ {int roishift; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 TYPE_2__* j2k_default_tcp ; 
 scalar_t__ notes ; 

void xml_out_frame_rgn(FILE* xmlout, opj_tcp_t *tcp, int numcomps)
{
    int compno, SPrgn;
    /* MJ2 files can have regions of interest if hybridized with JPX Part II */
    char spaces[13] = "            "; /* 12 spaces if tilepart*/
    char* s = spaces;
    if (tcp == j2k_default_tcp) {
        s++;
        s++; /* shorten s to 10 spaces if main */
    }

    for (compno = 0; compno < numcomps; compno++) {
        SPrgn = tcp->tccps[compno].roishift;    /* 1 byte; SPrgn */
        if (SPrgn == 0) {
            continue;    /* Yet another kludge */
        }

        fprintf(xmlout,    "%s<RegionOfInterest Marker=\"RGN\">\n",
                s); /* Optional in main header, at most 1 per component */
        if (notes) {
            fprintf(xmlout,  "%s<!-- See Crgn below for zero-based component number. -->\n",
                    s);
        }
        /* Not retained or of interest: Lrgd */
        fprintf(xmlout,    "%s  <Srgn>0</Srgn>\n", s); /* 1 byte */
        if (notes) {
            fprintf(xmlout,
                    "%s  <!-- Srgn is ROI style.  Only style=0 defined: Implicit ROI (max. shift) -->\n",
                    s);
        }
        fprintf(xmlout,    "%s  <Crgn>%d</Crgn>\n", s, compno); /* 1 or 2 bytes */
        fprintf(xmlout,    "%s  <SPrgn>%d</SPrgn>\n", s, SPrgn); /* 1 byte */
        if (notes) {
            fprintf(xmlout,
                    "%s  <!-- SPrgn is implicit ROI shift, i.e., binary shifting of ROI coefficients above background. -->\n",
                    s);
        }
        fprintf(xmlout,    "</RegionOfInterest\n",
                s); /* Optional in main header, at most 1 per component */
    }
}