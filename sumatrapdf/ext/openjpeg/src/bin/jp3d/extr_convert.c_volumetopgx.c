#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numcomps; int z1; int z0; int x1; int x0; int y1; int y0; TYPE_2__* comps; } ;
typedef  TYPE_1__ opj_volume_t ;
struct TYPE_5__ {int w; int h; int l; int prec; int* data; scalar_t__ bigendian; scalar_t__ sgnd; int /*<<< orphan*/ * factor; int /*<<< orphan*/  dz; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_2__ opj_volume_comp_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int int_ceildiv (int,int /*<<< orphan*/ ) ; 
 int int_ceildivpow2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

int volumetopgx(opj_volume_t * volume, char *outfile)
{
    int w, wr, wrr, h, hr, hrr, l, lr, lrr;
    int i, j, compno, offset, sliceno;
    FILE *fdest = NULL;

    for (compno = 0; compno < volume->numcomps; compno++) {
        opj_volume_comp_t *comp = &volume->comps[compno];
        char name[256];
        int nbytes = 0;
        char *tmp = outfile;
        while (*tmp) {
            tmp++;
        }
        while (*tmp != '.') {
            tmp--;
        }
        *tmp = '\0';
        for (sliceno = 0; sliceno < volume->z1 - volume->z0; sliceno++) {

            if (volume->numcomps > 1) {
                sprintf(name, "%s%d-%d.pgx", outfile, sliceno + 1, compno);
            } else if ((volume->z1 - volume->z0) > 1) {
                sprintf(name, "%s%d.pgx", outfile, sliceno + 1);
            } else {
                sprintf(name, "%s.pgx", outfile);
            }

            fdest = fopen(name, "wb");
            if (!fdest) {
                fprintf(stdout, "[ERROR] Failed to open %s for writing \n", name);
                return 1;
            }

            fprintf(stdout, "[INFO] Writing in %s (%s)\n", name,
                    volume->comps[0].bigendian ? "Bigendian" : "Little-endian");

            w = int_ceildiv(volume->x1 - volume->x0, volume->comps[compno].dx);
            wr = volume->comps[compno].w;
            wrr = int_ceildivpow2(volume->comps[compno].w, volume->comps[compno].factor[0]);

            h = int_ceildiv(volume->y1 - volume->y0, volume->comps[compno].dy);
            hr = volume->comps[compno].h;
            hrr = int_ceildivpow2(volume->comps[compno].h, volume->comps[compno].factor[1]);

            l = int_ceildiv(volume->z1 - volume->z0, volume->comps[compno].dz);
            lr = volume->comps[compno].l;
            lrr = int_ceildivpow2(volume->comps[compno].l, volume->comps[compno].factor[2]);

            fprintf(fdest, "PG %c%c %c%d %d %d\n", comp->bigendian ? 'M' : 'L',
                    comp->bigendian ? 'L' : 'M', comp->sgnd ? '-' : '+', comp->prec, wr, hr);
            if (comp->prec <= 8) {
                nbytes = 1;
            } else if (comp->prec <= 16) {
                nbytes = 2;
            } else {
                nbytes = 4;
            }

            offset = (sliceno / lrr * l) + (sliceno % lrr);
            offset = wrr * hrr * offset;
            /*fprintf(stdout,"%d %d %d %d\n",offset,wrr*hrr,wrr,w);*/
            for (i = 0; i < wrr * hrr; i++) {
                int v = volume->comps[0].data[(i / wrr * w) + (i % wrr) + offset];
                if (volume->comps[0].bigendian) {
                    for (j = nbytes - 1; j >= 0; j--) {
                        char byte = (char)((v >> (j * 8)) & 0xff);
                        fwrite(&byte, 1, 1, fdest);
                    }
                } else {
                    for (j = 0; j <= nbytes - 1; j++) {
                        char byte = (char)((v >> (j * 8)) & 0xff);
                        fwrite(&byte, 1, 1, fdest);
                    }
                }
            }

            fclose(fdest);
        }/*for sliceno*/
    }/*for compno*/

    return 0;
}