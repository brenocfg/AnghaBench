#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int hs; int vs; int ystep; int w_lores; scalar_t__ ypos; int* (* resample ) (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  line1; int /*<<< orphan*/  line0; } ;
typedef  TYPE_3__ stbi_resample ;
typedef  int stbi__uint8 ;
struct TYPE_11__ {int img_h_max; int img_v_max; TYPE_2__* s; TYPE_1__* img_comp; } ;
typedef  TYPE_4__ jpeg ;
struct TYPE_9__ {int img_n; int img_x; int img_y; } ;
struct TYPE_8__ {int* linebuf; int h; int v; scalar_t__ y; scalar_t__ w2; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  YCbCr_to_RGB_row (int*,int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  cleanup_jpeg (TYPE_4__*) ; 
 int /*<<< orphan*/  decode_jpeg_image (TYPE_4__*) ; 
 int* epuc (char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int* resample_row_1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int* resample_row_generic (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int* resample_row_h_2 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int* resample_row_hv_2 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int* resample_row_v_2 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stbi_YCbCr_installed (int*,int*,int*,int*,int,int) ; 
 int* stub1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static stbi__uint8 *load_jpeg_image(jpeg *z, int *out_x, int *out_y, int *comp, int req_comp)
{
   int n, decode_n;
   // validate req_comp
   if (req_comp < 0 || req_comp > 4) return epuc("bad req_comp", "Internal error");
   z->s->img_n = 0;

   // load a jpeg image from whichever source
   if (!decode_jpeg_image(z)) { cleanup_jpeg(z); return NULL; }

   // determine actual number of components to generate
   n = req_comp ? req_comp : z->s->img_n;

   if (z->s->img_n == 3 && n < 3)
      decode_n = 1;
   else
      decode_n = z->s->img_n;

   // resample and color-convert
   {
      int k;
      unsigned int i,j;
      stbi__uint8 *output;
      stbi__uint8 *coutput[4];

      stbi_resample res_comp[4];

      for (k=0; k < decode_n; ++k) {
         stbi_resample *r = &res_comp[k];

         // allocate line buffer big enough for upsampling off the edges
         // with upsample factor of 4
         z->img_comp[k].linebuf = (stbi__uint8 *) malloc(z->s->img_x + 3);
         if (!z->img_comp[k].linebuf) { cleanup_jpeg(z); return epuc("outofmem", "Out of memory"); }

         r->hs      = z->img_h_max / z->img_comp[k].h;
         r->vs      = z->img_v_max / z->img_comp[k].v;
         r->ystep   = r->vs >> 1;
         r->w_lores = (z->s->img_x + r->hs-1) / r->hs;
         r->ypos    = 0;
         r->line0   = r->line1 = z->img_comp[k].data;

         if      (r->hs == 1 && r->vs == 1) r->resample = resample_row_1;
         else if (r->hs == 1 && r->vs == 2) r->resample = resample_row_v_2;
         else if (r->hs == 2 && r->vs == 1) r->resample = resample_row_h_2;
         else if (r->hs == 2 && r->vs == 2) r->resample = resample_row_hv_2;
         else                               r->resample = resample_row_generic;
      }

      // can't error after this so, this is safe
      output = (stbi__uint8 *) malloc(n * z->s->img_x * z->s->img_y + 1);
      if (!output) { cleanup_jpeg(z); return epuc("outofmem", "Out of memory"); }

      // now go ahead and resample
      for (j=0; j < z->s->img_y; ++j) {
         stbi__uint8 *out = output + n * z->s->img_x * j;
         for (k=0; k < decode_n; ++k) {
            stbi_resample *r = &res_comp[k];
            int y_bot = r->ystep >= (r->vs >> 1);
            coutput[k] = r->resample(z->img_comp[k].linebuf,
                                     y_bot ? r->line1 : r->line0,
                                     y_bot ? r->line0 : r->line1,
                                     r->w_lores, r->hs);
            if (++r->ystep >= r->vs) {
               r->ystep = 0;
               r->line0 = r->line1;
               if (++r->ypos < z->img_comp[k].y)
                  r->line1 += z->img_comp[k].w2;
            }
         }
         if (n >= 3) {
            stbi__uint8 *y = coutput[0];
            if (z->s->img_n == 3) {
               #ifdef STBI_SIMD
               stbi_YCbCr_installed(out, y, coutput[1], coutput[2], z->s->img_x, n);
               #else
               YCbCr_to_RGB_row(out, y, coutput[1], coutput[2], z->s->img_x, n);
               #endif
            } else
               for (i=0; i < z->s->img_x; ++i) {
                  out[0] = out[1] = out[2] = y[i];
                  out[3] = 255; // not used if n==3
                  out += n;
               }
         } else {
            stbi__uint8 *y = coutput[0];
            if (n == 1)
               for (i=0; i < z->s->img_x; ++i) out[i] = y[i];
            else
               for (i=0; i < z->s->img_x; ++i) *out++ = y[i], *out++ = 255;
         }
      }
      cleanup_jpeg(z);
      *out_x = z->s->img_x;
      *out_y = z->s->img_y;
      if (comp) *comp  = z->s->img_n; // report original components, not output
      return output;
   }
}