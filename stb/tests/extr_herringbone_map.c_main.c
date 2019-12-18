#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int short_side_len; int num_h_tiles; int num_v_tiles; TYPE_2__** v_tiles; TYPE_1__** h_tiles; } ;
typedef  TYPE_3__ stbhw_tileset ;
struct TYPE_8__ {unsigned char* pixels; } ;
struct TYPE_7__ {unsigned char* pixels; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  stbhw_build_tileset_from_image (TYPE_3__*,unsigned char*,int,int,int) ; 
 int /*<<< orphan*/  stbhw_free_tileset (TYPE_3__*) ; 
 int /*<<< orphan*/  stbhw_generate_image (TYPE_3__*,int /*<<< orphan*/ *,unsigned char*,int,int,int) ; 
 char* stbhw_get_last_error () ; 
 unsigned char* stbi_load (char*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stbi_write_png (char*,int,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
   if (argc < 5) {
      fprintf(stderr, "Usage: herringbone_map {inputfile} {output-width} {output-height} {outputfile}\n");
      return 1;
   } else {
      char *filename = argv[1];
      int out_w = atoi(argv[2]);
      int out_h = atoi(argv[3]);
      char *outfile = argv[4];

      unsigned char *pixels, *out_pixels;
      stbhw_tileset ts;
      int w,h;

      pixels = stbi_load(filename, &w, &h, 0, 3);
      if (pixels == 0) {
         fprintf(stderr, "Couldn't open input file '%s'\n", filename);
			exit(1);
      }

      if (!stbhw_build_tileset_from_image(&ts, pixels, w*3, w, h)) {
         fprintf(stderr, "Error: %s\n", stbhw_get_last_error());
         return 1;
      }

      free(pixels);

      #ifdef DEBUG_OUTPUT
      {
         int i,j,k;
         // add blue borders to top-left edges of the tiles
         int hstride = (ts.short_side_len*2)*3;
         int vstride = (ts.short_side_len  )*3;
         for (i=0; i < ts.num_h_tiles; ++i) {
            unsigned char *pix = ts.h_tiles[i]->pixels;
            for (j=0; j < ts.short_side_len*2; ++j)
               for (k=0; k < 3; ++k)
                  pix[j*3+k] = (pix[j*3+k]*0.5+100+k*75)/1.5;
            for (j=1; j < ts.short_side_len; ++j)
               for (k=0; k < 3; ++k)
                  pix[j*hstride+k] = (pix[j*hstride+k]*0.5+100+k*75)/1.5;
         }
         for (i=0; i < ts.num_v_tiles; ++i) {
            unsigned char *pix = ts.v_tiles[i]->pixels;
            for (j=0; j < ts.short_side_len; ++j)
               for (k=0; k < 3; ++k)
                  pix[j*3+k] = (pix[j*3+k]*0.5+100+k*75)/1.5;
            for (j=1; j < ts.short_side_len*2; ++j)
               for (k=0; k < 3; ++k)
                  pix[j*vstride+k] = (pix[j*vstride+k]*0.5+100+k*75)/1.5;
         }
      }
      #endif

      out_pixels = malloc(out_w * out_h * 3);

      if (!stbhw_generate_image(&ts, NULL, out_pixels, out_w*3, out_w, out_h)) {
         fprintf(stderr, "Error: %s\n", stbhw_get_last_error());
         return 1;
      }

      stbi_write_png(argv[4], out_w, out_h, 3, out_pixels, out_w*3);
      free(out_pixels);

      stbhw_free_tileset(&ts);
      return 0;
   }
}