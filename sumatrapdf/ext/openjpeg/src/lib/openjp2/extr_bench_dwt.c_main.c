#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tcd_tile ;
typedef  int /*<<< orphan*/  tcd_image ;
typedef  int /*<<< orphan*/  tcd ;
typedef  int /*<<< orphan*/  opj_thread_pool_t ;
struct TYPE_13__ {int y1; int y0; int x1; int x0; int* data; int win_x0; int win_y0; int win_x1; int win_y1; int numcomps; int dx; int dy; int /*<<< orphan*/  numresolutions; struct TYPE_13__* comps; struct TYPE_13__* image; struct TYPE_13__* tiles; struct TYPE_13__* tcd_image; void* whole_tile_decoding; int /*<<< orphan*/ * thread_pool; } ;
typedef  TYPE_1__ opj_tcd_tilecomp_t ;
typedef  TYPE_1__ opj_tcd_tile_t ;
typedef  TYPE_1__ opj_tcd_t ;
typedef  TYPE_1__ opj_tcd_image_t ;
typedef  TYPE_1__ opj_image_t ;
typedef  TYPE_1__ opj_image_comp_t ;
typedef  int /*<<< orphan*/  image_comp ;
typedef  int /*<<< orphan*/  image ;
typedef  int OPJ_UINT32 ;
typedef  int OPJ_INT32 ;
typedef  double OPJ_FLOAT64 ;
typedef  void* OPJ_BOOL ;

/* Variables and functions */
 void* OPJ_FALSE ; 
 void* OPJ_TRUE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_tilec (TYPE_1__*) ; 
 scalar_t__ getValue (int) ; 
 int /*<<< orphan*/  init_tilec (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 double opj_clock () ; 
 int /*<<< orphan*/  opj_dwt_decode (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_dwt_encode (TYPE_1__*) ; 
 int /*<<< orphan*/ * opj_thread_pool_create (int) ; 
 int /*<<< orphan*/  opj_thread_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char** argv)
{
    int num_threads = 0;
    opj_tcd_t tcd;
    opj_tcd_image_t tcd_image;
    opj_tcd_tile_t tcd_tile;
    opj_tcd_tilecomp_t tilec;
    opj_image_t image;
    opj_image_comp_t image_comp;
    opj_thread_pool_t* tp;
    OPJ_INT32 i, j, k;
    OPJ_BOOL display = OPJ_FALSE;
    OPJ_BOOL check = OPJ_FALSE;
    OPJ_INT32 size = 16384 - 1;
    OPJ_FLOAT64 start, stop;
    OPJ_UINT32 offset_x = ((OPJ_UINT32)size + 1) / 2 - 1;
    OPJ_UINT32 offset_y = ((OPJ_UINT32)size + 1) / 2 - 1;
    OPJ_UINT32 num_resolutions = 6;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-display") == 0) {
            display = OPJ_TRUE;
            check = OPJ_TRUE;
        } else if (strcmp(argv[i], "-check") == 0) {
            check = OPJ_TRUE;
        } else if (strcmp(argv[i], "-size") == 0 && i + 1 < argc) {
            size = atoi(argv[i + 1]);
            i ++;
        } else if (strcmp(argv[i], "-num_threads") == 0 && i + 1 < argc) {
            num_threads = atoi(argv[i + 1]);
            i ++;
        } else if (strcmp(argv[i], "-num_resolutions") == 0 && i + 1 < argc) {
            num_resolutions = (OPJ_UINT32)atoi(argv[i + 1]);
            if (num_resolutions == 0 || num_resolutions > 32) {
                fprintf(stderr,
                        "Invalid value for num_resolutions. Should be >= 1 and <= 32\n");
                exit(1);
            }
            i ++;
        } else if (strcmp(argv[i], "-offset") == 0 && i + 2 < argc) {
            offset_x = (OPJ_UINT32)atoi(argv[i + 1]);
            offset_y = (OPJ_UINT32)atoi(argv[i + 2]);
            i += 2;
        } else {
            usage();
        }
    }

    tp = opj_thread_pool_create(num_threads);

    init_tilec(&tilec, (OPJ_INT32)offset_x, (OPJ_INT32)offset_y,
               (OPJ_INT32)offset_x + size, (OPJ_INT32)offset_y + size,
               num_resolutions);

    if (display) {
        printf("Before\n");
        k = 0;
        for (j = 0; j < tilec.y1 - tilec.y0; j++) {
            for (i = 0; i < tilec.x1 - tilec.x0; i++) {
                printf("%d ", tilec.data[k]);
                k ++;
            }
            printf("\n");
        }
    }

    memset(&tcd, 0, sizeof(tcd));
    tcd.thread_pool = tp;
    tcd.whole_tile_decoding = OPJ_TRUE;
    tcd.win_x0 = (OPJ_UINT32)tilec.x0;
    tcd.win_y0 = (OPJ_UINT32)tilec.y0;
    tcd.win_x1 = (OPJ_UINT32)tilec.x1;
    tcd.win_y1 = (OPJ_UINT32)tilec.y1;
    tcd.tcd_image = &tcd_image;
    memset(&tcd_image, 0, sizeof(tcd_image));
    tcd_image.tiles = &tcd_tile;
    memset(&tcd_tile, 0, sizeof(tcd_tile));
    tcd_tile.x0 = tilec.x0;
    tcd_tile.y0 = tilec.y0;
    tcd_tile.x1 = tilec.x1;
    tcd_tile.y1 = tilec.y1;
    tcd_tile.numcomps = 1;
    tcd_tile.comps = &tilec;
    tcd.image = &image;
    memset(&image, 0, sizeof(image));
    image.numcomps = 1;
    image.comps = &image_comp;
    memset(&image_comp, 0, sizeof(image_comp));
    image_comp.dx = 1;
    image_comp.dy = 1;

    start = opj_clock();
    opj_dwt_decode(&tcd, &tilec, tilec.numresolutions);
    stop = opj_clock();
    printf("time for dwt_decode: %.03f s\n", stop - start);

    if (display || check) {
        if (display) {
            printf("After IDWT\n");
            k = 0;
            for (j = 0; j < tilec.y1 - tilec.y0; j++) {
                for (i = 0; i < tilec.x1 - tilec.x0; i++) {
                    printf("%d ", tilec.data[k]);
                    k ++;
                }
                printf("\n");
            }
        }

        opj_dwt_encode(&tilec);
        if (display) {
            printf("After FDWT\n");
            k = 0;
            for (j = 0; j < tilec.y1 - tilec.y0; j++) {
                for (i = 0; i < tilec.x1 - tilec.x0; i++) {
                    printf("%d ", tilec.data[k]);
                    k ++;
                }
                printf("\n");
            }
        }

        if (check) {
            size_t idx;
            size_t nValues = (size_t)(tilec.x1 - tilec.x0) *
                             (size_t)(tilec.y1 - tilec.y0);
            for (idx = 0; i < (OPJ_INT32)nValues; i++) {
                if (tilec.data[idx] != getValue((OPJ_UINT32)idx)) {
                    printf("Difference found at idx = %u\n", (OPJ_UINT32)idx);
                    exit(1);
                }
            }
        }
    }

    free_tilec(&tilec);

    opj_thread_pool_destroy(tp);
    return 0;
}