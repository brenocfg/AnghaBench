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
typedef  int /*<<< orphan*/  stbi__uint8 ;
struct TYPE_8__ {int img_y; int img_x; int img_n; } ;
typedef  TYPE_2__ stbi ;
struct TYPE_9__ {int img_h_max; int img_v_max; int img_mcu_w; int img_mcu_h; int img_mcu_x; int img_mcu_y; TYPE_1__* img_comp; TYPE_2__* s; } ;
typedef  TYPE_3__ jpeg ;
struct TYPE_7__ {int id; int h; int v; int tq; int x; int y; int w2; int h2; int /*<<< orphan*/ * linebuf; int /*<<< orphan*/ * raw_data; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int SCAN_load ; 
 int e (char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* get16 (TYPE_2__*) ; 
 void* get8 (TYPE_2__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static int process_frame_header(jpeg *z, int scan)
{
   stbi *s = z->s;
   int Lf,p,i,q, h_max=1,v_max=1,c;
   Lf = get16(s);         if (Lf < 11) return e("bad SOF len","Corrupt JPEG"); // JPEG
   p  = get8(s);          if (p != 8) return e("only 8-bit","JPEG format not supported: 8-bit only"); // JPEG baseline
   s->img_y = get16(s);   if (s->img_y == 0) return e("no header height", "JPEG format not supported: delayed height"); // Legal, but we don't handle it--but neither does IJG
   s->img_x = get16(s);   if (s->img_x == 0) return e("0 width","Corrupt JPEG"); // JPEG requires
   c = get8(s);
   if (c != 3 && c != 1) return e("bad component count","Corrupt JPEG");    // JFIF requires
   s->img_n = c;
   for (i=0; i < c; ++i) {
      z->img_comp[i].data = NULL;
      z->img_comp[i].linebuf = NULL;
   }

   if (Lf != 8+3*s->img_n) return e("bad SOF len","Corrupt JPEG");

   for (i=0; i < s->img_n; ++i) {
      z->img_comp[i].id = get8(s);
      if (z->img_comp[i].id != i+1)   // JFIF requires
         if (z->img_comp[i].id != i)  // some version of jpegtran outputs non-JFIF-compliant files!
            return e("bad component ID","Corrupt JPEG");
      q = get8(s);
      z->img_comp[i].h = (q >> 4);  if (!z->img_comp[i].h || z->img_comp[i].h > 4) return e("bad H","Corrupt JPEG");
      z->img_comp[i].v = q & 15;    if (!z->img_comp[i].v || z->img_comp[i].v > 4) return e("bad V","Corrupt JPEG");
      z->img_comp[i].tq = get8(s);  if (z->img_comp[i].tq > 3) return e("bad TQ","Corrupt JPEG");
   }

   if (scan != SCAN_load) return 1;

   if ((1 << 30) / s->img_x / s->img_n < s->img_y) return e("too large", "Image too large to decode");

   for (i=0; i < s->img_n; ++i) {
      if (z->img_comp[i].h > h_max) h_max = z->img_comp[i].h;
      if (z->img_comp[i].v > v_max) v_max = z->img_comp[i].v;
   }

   // compute interleaved mcu info
   z->img_h_max = h_max;
   z->img_v_max = v_max;
   z->img_mcu_w = h_max * 8;
   z->img_mcu_h = v_max * 8;
   z->img_mcu_x = (s->img_x + z->img_mcu_w-1) / z->img_mcu_w;
   z->img_mcu_y = (s->img_y + z->img_mcu_h-1) / z->img_mcu_h;

   for (i=0; i < s->img_n; ++i) {
      // number of effective pixels (e.g. for non-interleaved MCU)
      z->img_comp[i].x = (s->img_x * z->img_comp[i].h + h_max-1) / h_max;
      z->img_comp[i].y = (s->img_y * z->img_comp[i].v + v_max-1) / v_max;
      // to simplify generation, we'll allocate enough memory to decode
      // the bogus oversized data from using interleaved MCUs and their
      // big blocks (e.g. a 16x16 iMCU on an image of width 33); we won't
      // discard the extra data until colorspace conversion
      z->img_comp[i].w2 = z->img_mcu_x * z->img_comp[i].h * 8;
      z->img_comp[i].h2 = z->img_mcu_y * z->img_comp[i].v * 8;
      z->img_comp[i].raw_data = malloc(z->img_comp[i].w2 * z->img_comp[i].h2+15);
      if (z->img_comp[i].raw_data == NULL) {
         for(--i; i >= 0; --i) {
            free(z->img_comp[i].raw_data);
            z->img_comp[i].data = NULL;
         }
         return e("outofmem", "Out of memory");
      }
      // align blocks for installable-idct using mmx/sse
      z->img_comp[i].data = (stbi__uint8*) (((size_t) z->img_comp[i].raw_data + 15) & ~15);
      z->img_comp[i].linebuf = NULL;
   }

   return 1;
}