#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numcomps; TYPE_2__* comps; scalar_t__ z1; scalar_t__ y1; scalar_t__ x1; scalar_t__ z0; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ opj_volume_t ;
struct TYPE_11__ {int prec; int* data; scalar_t__ bpp; int /*<<< orphan*/  sgnd; } ;
typedef  TYPE_2__ opj_volume_comp_t ;
struct TYPE_12__ {int prec; int bpp; int bigendian; int dx; int dy; int dz; int w; int h; int l; int /*<<< orphan*/  dcoffset; scalar_t__ sgnd; } ;
typedef  TYPE_3__ opj_volume_cmptparm_t ;
struct TYPE_13__ {int subsampling_dx; int subsampling_dy; int subsampling_dz; scalar_t__ volume_offset_z0; scalar_t__ volume_offset_y0; scalar_t__ volume_offset_x0; int /*<<< orphan*/  dcoffset; } ;
typedef  TYPE_4__ opj_cparameters_t ;
typedef  int OPJ_COLOR_SPACE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CLRSPC_GRAY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ int_floorlog2 (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* opj_volume_create (int,TYPE_3__*,int) ; 
 int readuchar (int /*<<< orphan*/ *) ; 
 int readuint (int /*<<< orphan*/ *,int) ; 
 int readushort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strncmp (char*,char*,int) ; 

opj_volume_t* bintovolume(char *filename, char *fileimg,
                          opj_cparameters_t *parameters)
{
    int subsampling_dx =  parameters->subsampling_dx;
    int subsampling_dy =  parameters->subsampling_dy;
    int subsampling_dz =  parameters->subsampling_dz;

    int i, compno, w, h, l, numcomps = 1;
    int prec, max = 0;

    /*  char temp[32];*/
    char line[100];
    int bigendian;

    FILE *f = NULL;
    FILE *fimg = NULL;
    OPJ_COLOR_SPACE color_space;
    opj_volume_cmptparm_t cmptparm; /* maximum of 1 component */
    opj_volume_t * volume = NULL;
    opj_volume_comp_t *comp = NULL;

    bigendian = 0;
    color_space = CLRSPC_GRAY;

    fimg = fopen(fileimg, "r");
    if (!fimg) {
        fprintf(stdout, "[ERROR] Failed to open %s for reading !!\n", fileimg);
        return 0;
    }

    fseek(fimg, 0, SEEK_SET);
    while (!feof(fimg)) {
        fgets(line, 100, fimg);
        /*fprintf(stdout,"%s %d \n",line,feof(fimg));*/
        if (strncmp(line, "Bpp", 3) == 0) {
            sscanf(line, "%*s%*[ \t]%d", &prec);
        } else if (strncmp(line, "Color", 5) == 0) {
            sscanf(line, "%*s%*[ \t]%d", &color_space);
        } else if (strncmp(line, "Dim", 3) == 0) {
            sscanf(line, "%*s%*[ \t]%d%*[ \t]%d%*[ \t]%d", &w, &h, &l);
        }
    }
    /*fscanf(fimg, "Bpp%[ \t]%d%[ \t\n]",temp,&prec,temp);*/
    /*fscanf(fimg, "Color Map%[ \t]%d%[ \n\t]Dimensions%[ \t]%d%[ \t]%d%[ \t]%d%[ \n\t]",temp,&color_space,temp,temp,&w,temp,&h,temp,&l,temp);*/
    /*fscanf(fimg, "Resolution(mm)%[ \t]%d%[ \t]%d%[ \t]%d%[ \n\t]",temp,&subsampling_dx,temp,&subsampling_dy,temp,&subsampling_dz,temp);*/

#ifdef VERBOSE
    fprintf(stdout, "[INFO] %d \t %d %d %d \t %3.2f %2.2f %2.2f \t %d \n",
            color_space, w, h, l, subsampling_dx, subsampling_dy, subsampling_dz, prec);
#endif
    fclose(fimg);

    /* initialize volume components */
    memset(&cmptparm, 0, sizeof(opj_volume_cmptparm_t));

    cmptparm.prec = prec;
    cmptparm.bpp = prec;
    cmptparm.sgnd = 0;
    cmptparm.bigendian = bigendian;
    cmptparm.dcoffset = parameters->dcoffset;
    cmptparm.dx = subsampling_dx;
    cmptparm.dy = subsampling_dy;
    cmptparm.dz = subsampling_dz;
    cmptparm.w = w;
    cmptparm.h = h;
    cmptparm.l = l;

    /* create the volume */
    volume = opj_volume_create(numcomps, &cmptparm, color_space);
    if (!volume) {
        fprintf(stdout, "[ERROR] Unable to create volume");
        fclose(f);
        return NULL;
    }

    /* set volume offset and reference grid */
    volume->x0 = parameters->volume_offset_x0;
    volume->y0 = parameters->volume_offset_y0;
    volume->z0 = parameters->volume_offset_z0;
    volume->x1 = parameters->volume_offset_x0 + (w - 1) *   subsampling_dx + 1;
    volume->y1 = parameters->volume_offset_y0 + (h - 1) *   subsampling_dy + 1;
    volume->z1 = parameters->volume_offset_z0 + (l - 1) *   subsampling_dz + 1;

    /* set volume data */
    f = fopen(filename, "rb");
    if (!f) {
        fprintf(stdout, "[ERROR] Failed to open %s for reading !!\n", filename);
        return 0;
    }

    /* BINARY */
    for (compno = 0; compno < volume->numcomps; compno++) {
        int whl = w * h * l;
        /* set volume data */
        comp = &volume->comps[compno];

        /*if (comp->prec <= 8) {
            if (!comp->sgnd) {
                unsigned char *data = (unsigned char *) malloc(whl * sizeof(unsigned char));
                fread(data, 1, whl, f);
                for (i = 0; i < whl; i++) {
                    comp->data[i] = data[i];
                    if (comp->data[i] > max)
                        max = comp->data[i];
                }
                free(data);
            } else {
                char *data = (char *) malloc(whl);
                fread(data, 1, whl, f);
                for (i = 0; i < whl; i++) {
                    comp->data[i] = data[i];
                    if (comp->data[i] > max)
                        max = comp->data[i];
                }
                free(data);
            }
        } else if (comp->prec <= 16) {
            if (!comp->sgnd) {
                unsigned short *data = (unsigned short *) malloc(whl * sizeof(unsigned short));
                int leido = fread(data, 2, whl, f);
                if (!leido) {
                    free(data); fclose(f);
                    return NULL;
                }

                for (i = 0; i < whl; i++) {
                    if (bigendian)  //(c1 << 8) + c2;
                        comp->data[i] = data[i];
                    else{           //(c2 << 8) + c1;
                        comp->data[i] = ShortSwap(data[i]);
                    }
                    if (comp->data[i] > max)
                        max = comp->data[i];
                }
                free(data);
            } else {
                short *data = (short *) malloc(whl);
                int leido = fread(data, 2, whl, f);
                if (!leido) {
                    free(data); fclose(f);
                    return NULL;
                }
                for (i = 0; i < whl; i++) {
                    if (bigendian){ //(c1 << 8) + c2;
                        comp->data[i] = data[i];
                    }else{          //(c2 << 8) + c1;
                        comp->data[i] = (short) ShortSwap((unsigned short) data[i]);
                    }
                    if (comp->data[i] > max)
                        max = comp->data[i];
                }
                free(data);
            }
        } else {
            if (!comp->sgnd) {
                unsigned int *data = (unsigned int *) malloc(whl * sizeof(unsigned int));
                int leido = fread(data, 4, whl, f);
                if (!leido) {
                    free(data); fclose(f);
                    return NULL;
                }               for (i = 0; i < whl; i++) {
                    if (!bigendian)
                        comp->data[i] = LongSwap(data[i]);
                    else
                        comp->data[i] = data[i];
                    if (comp->data[i] > max)
                        max = comp->data[i];
                }
                free(data);
            } else {
                int leido = fread(comp->data, 4, whl, f);
                if (!leido) {
                    fclose(f);
                    return NULL;
                }
                for (i = 0; i < whl; i++) {
                    if (!bigendian)
                        comp->data[i] = (int) LongSwap((unsigned int) comp->data[i]);
                    if (comp->data[i] > max)
                        max = comp->data[i];
                }
            }
        }*/

        for (i = 0; i < whl; i++) {
            int v;
            if (comp->prec <= 8) {
                if (!comp->sgnd) {
                    v = readuchar(f);
                } else {
                    v = (char) readuchar(f);
                }
            } else if (comp->prec <= 16) {
                if (!comp->sgnd) {
                    v = readushort(f, bigendian);
                } else {
                    v = (short) readushort(f, bigendian);
                }
            } else {
                if (!comp->sgnd) {
                    v = readuint(f, bigendian);
                } else {
                    v = (int) readuint(f, bigendian);
                }
            }
            if (v > max) {
                max = v;
            }
            comp->data[i] = v;
        }
        comp->bpp = int_floorlog2(max) + 1;
    }
    fclose(f);
    return volume;
}