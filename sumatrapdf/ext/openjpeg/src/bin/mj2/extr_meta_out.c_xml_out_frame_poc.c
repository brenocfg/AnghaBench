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
struct TYPE_5__ {int POC; int numpocs; TYPE_2__* pocs; } ;
typedef  TYPE_1__ opj_tcp_t ;
struct TYPE_6__ {int compno0; int layno1; int resno1; int compno1; int prg; int /*<<< orphan*/  resno0; } ;
typedef  TYPE_2__ opj_poc_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 TYPE_1__* j2k_default_tcp ; 
 scalar_t__ notes ; 

void xml_out_frame_poc(FILE* xmlout,
                       opj_tcp_t *tcp)   /* Progression Order Change */
{
    /* Compare j2k_read_poc() */
    int i;
    opj_poc_t *poc;
    char spaces[13] = "            "; /* 12 spaces if tilepart*/
    char* s = spaces;
    if (tcp == j2k_default_tcp) {
        s++;
        s++; /* shorten s to 10 spaces if main */
    }

    if (tcp->POC != 1) {
        return;    /* Not present */
    }

    fprintf(xmlout,    "%s<ProgressionOrderChange Marker=\"POC\">\n",
            s); /* Optional in main header, at most 1 per component */
    /* j2k_read_poc seems to allow accumulation of default pocs from multiple POC segments, but does
    the spec really allow that? */
    /* 2 bytes, not retained; Lpoc */
    /* I probably didn't get this dump precisely right. */
    for (i = 0; i < tcp->numpocs; i++) {
        poc = &tcp->pocs[i];
        fprintf(xmlout,  "%s  <Progression Num=\"%d\">\n", s, i + 1);
        fprintf(xmlout,  "%S    <RSpoc>%d</RSpoc>\n", s,
                poc->resno0);  /* 1 byte, RSpoc_i */
        if (notes) {
            fprintf(xmlout,
                    "%s    <!-- Resolution level index (inclusive) for progression start. Range: 0 to 33 -->\n",
                    s);
        }
        fprintf(xmlout,  "%s    <CSpoc>%d</CSpoc>\n", s,
                poc->compno0);/* j2k_img->numcomps <= 256 ? 1 byte : 2 bytes; CSpoc_i */
        if (notes) {
            fprintf(xmlout,
                    "%s    <!-- Component index (inclusive) for progression start. -->\n", s);
        }
        fprintf(xmlout,  "%s    <LYEpoc>%d</LYEpoc>\n", s,
                poc->layno1); /* int_min(cio_read(2), tcp->numlayers);   /* 2 bytes; LYEpoc_i */
        if (notes) {
            fprintf(xmlout, "%s    <!-- Layer index (exclusive) for progression end. -->\n",
                    s);
        }
        fprintf(xmlout,  "%s    <REpoc>%d</REpoc>\n", s,
                poc->resno1); /*int_min(cio_read(1), tccp->numresolutions);    /* REpoc_i */
        if (notes) {
            fprintf(xmlout,
                    "%s    <!-- Resolution level index (exclusive) for progression end. Range: RSpoc to 33 -->\n",
                    s);
        }
        fprintf(xmlout,  "%s    <CEpoc>%d</CEpoc>\n", s,
                poc->compno1); /* int_min(cio_read(j2k_img->numcomps <= 256 ? 1 : 2), j2k_img->numcomps);  /* CEpoc_i */
        if (notes) {
            fprintf(xmlout,
                    "%s    <!-- Component index (exclusive) for progression end.  Minimum: CSpoc -->\n",
                    s);
        }
        fprintf(xmlout,  "%s    <Ppoc>%d</Ppoc>\n", s, poc->prg); /* 1 byte Ppoc_i */
        if (notes) {
            fprintf(xmlout, "%s    <!-- Defined Progression Order Values are: -->\n", s);
            fprintf(xmlout,
                    "%s    <!-- 0 = LRCP; 1 = RLCP; 2 = RPCL; 3 = PCRL; 4 = CPRL -->\n", s);
            fprintf(xmlout,
                    "%s    <!-- where L = \"layer\", R = \"resolution level\", C = \"component\", P = \"position\". -->\n",
                    s);
        }
        fprintf(xmlout,  "%s  </Progression>\n", s);
    }
    fprintf(xmlout,    "%s</ProgressionOrderChange\n", s);
}