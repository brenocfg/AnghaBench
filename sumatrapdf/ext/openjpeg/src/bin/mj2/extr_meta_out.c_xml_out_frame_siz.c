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
struct TYPE_6__ {int x1; int y1; int x0; int y0; int numcomps; TYPE_2__* comps; } ;
typedef  TYPE_1__ opj_image_t ;
struct TYPE_7__ {int sgnd; int prec; int dx; int dy; int w; int h; } ;
typedef  TYPE_2__ opj_image_comp_t ;
struct TYPE_8__ {int tdx; int tdy; int tx0; int ty0; } ;
typedef  TYPE_3__ opj_cp_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ derived ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ notes ; 
 scalar_t__ raw ; 

void xml_out_frame_siz(FILE* xmlout, opj_image_t *img, opj_cp_t *cp)
{
    opj_image_comp_t *comp;
    int i;

    fprintf(xmlout,    "          <ImageAndFileSize Marker=\"SIZ\">\n");
    // This is similar to j2k.c's j2k_dump_image.
    // Not of interest: Lsiz, Rsiz
    fprintf(xmlout,    "            <Xsiz>%d</Xsiz>\n", img->x1);
    fprintf(xmlout,    "            <Ysiz>%d</Ysiz>\n", img->y1);
    if (notes) {
        fprintf(xmlout,
                "            <!-- Xsiz, Ysiz is the size of the reference grid. -->\n");
    }
    fprintf(xmlout,    "            <XOsiz>%d</XOsiz>\n", img->x0);
    fprintf(xmlout,    "            <YOsiz>%d</YOsiz>\n", img->y0);
    if (notes) {
        fprintf(xmlout,
                "            <!-- XOsiz, YOsiz are offsets from grid origin to image origin. -->\n");
    }
    fprintf(xmlout,    "            <XTsiz>%d</XTsiz>\n", cp->tdx);
    fprintf(xmlout,    "            <YTsiz>%d</YTsiz>\n", cp->tdy);
    if (notes) {
        fprintf(xmlout,
                "            <!-- XTsiz, YTsiz is the size of one tile with respect to the grid. -->\n");
    }
    fprintf(xmlout,    "            <XTOsiz>%d</XTOsiz>\n", cp->tx0);
    fprintf(xmlout,    "            <YTOsiz>%d</YTOsiz>\n", cp->ty0);
    if (notes) {
        fprintf(xmlout,
                "            <!-- XTOsiz, YTOsiz are offsets from grid origin to first tile origin. -->\n");
    }
    fprintf(xmlout,    "            <Csiz>%d</Csiz>\n", img->numcomps);
    if (notes) {
        fprintf(xmlout,
                "            <!-- Csiz is the number of components in the image. -->\n");
        fprintf(xmlout,  "            <!-- For image components next: -->\n");
        fprintf(xmlout,
                "            <!--   XRsiz, YRsiz denote pixel-sample-spacing on the grid, per Part I Annex B. -->\n");
        //fprintf(xmlout,"            <!--   XO, YO is offset of the component compared to the whole image. -->\n");
        fprintf(xmlout,
                "            <!--   Bits per pixel (bpp) is the pixel depth. -->\n");
        fprintf(xmlout,
                "            <!--   WidthOfData and HeightOfData are calculated values, e.g.: w = roundup((Xsiz - XOsiz)/ XRsiz) -->\n");
    }

    for (i = 0; i < img->numcomps; i++) {/* image-components */
        comp = &(img->comps[i]);
        fprintf(xmlout,  "            <Component Num=\"%d\">\n", i + 1);
        fprintf(xmlout,  "              <Ssiz>\n");
        if (raw) {
            fprintf(xmlout, "                <AsHex>0x%02x</AsHex>\n",
                    (comp->sgnd << 7) & (comp->prec - 1));
        }
        if (derived) {
            fprintf(xmlout, "                <Signed>%d</Signed>\n", comp->sgnd);
            fprintf(xmlout, "                <PrecisionInBits>%d</PrecisionInBits>\n",
                    comp->prec);
        }
        fprintf(xmlout,  "              </Ssiz>\n");
        fprintf(xmlout,  "              <XRsiz>%d</XRsiz>\n", comp->dx);
        fprintf(xmlout,  "              <YRsiz>%d</YRsiz>\n", comp->dy);
        fprintf(xmlout,  "              <WidthOfData>%d</WidthOfData>\n", comp->w);
        fprintf(xmlout,  "              <HeightOfData>%d</HeightOfData>\n", comp->h);
        /* Rest of these aren't calculated when SIZ is read:
        fprintf(xmlout,  "              <XO>%d</XO>\n", comp->x0);
        fprintf(xmlout,  "              <YO>%d</YO>\n", comp->y0);
        if(notes)
          fprintf(xmlout,"              <!--  XO, YO is offset of the component compared to the whole image. -->\n");
        fprintf(xmlout,  "              <BitsPerPixel>%d</BitsPerPixel>\n", comp->bpp);
        fprintf(xmlout,  "              <NumberOfDecodedResolution>%d</NumberOfDecodedResolution>\n", comp->resno_decoded); */
        // SUPPRESS: n/a to mj2_to_metadata.  fprintf(xmlout,"        <Factor>%d</Factor\n", comp->factor);
        /* factor = number of division by 2 of the out image  compare to the original size of image */
        // TO DO comp->data:  int *data;            /* image-component data      */

        fprintf(xmlout,  "            </Component>\n");
    }
    fprintf(xmlout,    "          </ImageAndFileSize>\n");
}