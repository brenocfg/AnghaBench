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
struct TYPE_6__ {int minversion; int num_cl; int /*<<< orphan*/ * cl; int /*<<< orphan*/  brand; } ;
typedef  TYPE_1__ opj_mj2_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  uint_to_chars (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_write_free_and_skip (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xml_write_moov (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_write_uuid (int /*<<< orphan*/ *,TYPE_1__*) ; 

int xml_write_overall_header(FILE *file, FILE *xmlout, opj_mj2_t * movie,
                             unsigned int sampleframe, opj_event_mgr_t *event_mgr)
{
    int i;
    char buf[5];
    buf[4] = '\0';

    fprintf(xmlout,
            "  <JP2 BoxType=\"jP[space][space]\" Signature=\"0x0d0a870a\" />\n");
    // Called after structure initialized by mj2_read_ftyp
    fprintf(xmlout,   "  <FileType BoxType=\"ftyp\">\n");
    uint_to_chars(movie->brand, buf);
    fprintf(xmlout,   "    <Brand>%s</Brand>\n",
            buf);    /* 4 character; BR              */
    fprintf(xmlout,   "    <MinorVersion>%u</MinorVersion>\n",
            movie->minversion);    /* 4 char; MinV            */
    fprintf(xmlout,   "    <CompatibilityList Count=\"%d\">\n", movie->num_cl);
    for (i = movie->num_cl - 1; i > -1;
            i--) { /* read routine stored in reverse order, so let's undo damage */
        uint_to_chars(movie->cl[i], buf);
        fprintf(xmlout, "      <CompatibleBrand>%s</CompatibleBrand>\n",
                buf);    /*4 characters, each CLi */
    }
    fprintf(xmlout,   "    </CompatibilityList>\n");
    fprintf(xmlout,   "  </FileType>\n");
    xml_write_moov(file, xmlout, movie, sampleframe, event_mgr);
    // To come?              <mdat>  // This is the container for media data that can also be accessed through track structures,
    // so is redundant, and simply not of interest as metadata
    //                       <moof>  // Allows incremental build up of movie.  Probably not in Simple Profile
    xml_write_free_and_skip(xmlout,
                            movie); /* NO OP so far */ /* May be a place where user squirrels metadata */
    xml_write_uuid(xmlout,
                   movie); /* NO OP so far */ /* May be a place where user squirrels metadata */
    return 0;
}