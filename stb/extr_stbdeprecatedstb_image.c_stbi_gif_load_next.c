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
struct TYPE_6__ {int w; int h; int eflags; int line_size; int start_x; int start_y; int max_x; int max_y; int cur_x; int cur_y; int lflags; int step; int parse; int transparent; int flags; int** pal; int /*<<< orphan*/ * color_table; scalar_t__ lpal; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ stbi_gif ;
typedef  int /*<<< orphan*/  stbi__uint8 ;
typedef  int stbi__int32 ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int /*<<< orphan*/ * convert_format (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * epuc (char*,char*) ; 
 int get16le (int /*<<< orphan*/ *) ; 
 int get8 (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stbi_fill_gif_background (TYPE_1__*) ; 
 int /*<<< orphan*/  stbi_gif_header (int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbi_gif_parse_colortable (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/ * stbi_process_gif_raster (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static stbi__uint8 *stbi_gif_load_next(stbi *s, stbi_gif *g, int *comp, int req_comp)
{
   int i;
   stbi__uint8 *old_out = 0;

   if (g->out == 0) {
      if (!stbi_gif_header(s, g, comp,0))     return 0; // failure_reason set by stbi_gif_header
      g->out = (stbi__uint8 *) malloc(4 * g->w * g->h);
      if (g->out == 0)                      return epuc("outofmem", "Out of memory");
      stbi_fill_gif_background(g);
   } else {
      // animated-gif-only path
      if (((g->eflags & 0x1C) >> 2) == 3) {
         old_out = g->out;
         g->out = (stbi__uint8 *) malloc(4 * g->w * g->h);
         if (g->out == 0)                   return epuc("outofmem", "Out of memory");
         memcpy(g->out, old_out, g->w*g->h*4);
      }
   }
    
   for (;;) {
      switch (get8(s)) {
         case 0x2C: /* Image Descriptor */
         {
            stbi__int32 x, y, w, h;
            stbi__uint8 *o;

            x = get16le(s);
            y = get16le(s);
            w = get16le(s);
            h = get16le(s);
            if (((x + w) > (g->w)) || ((y + h) > (g->h)))
               return epuc("bad Image Descriptor", "Corrupt GIF");

            g->line_size = g->w * 4;
            g->start_x = x * 4;
            g->start_y = y * g->line_size;
            g->max_x   = g->start_x + w * 4;
            g->max_y   = g->start_y + h * g->line_size;
            g->cur_x   = g->start_x;
            g->cur_y   = g->start_y;

            g->lflags = get8(s);

            if (g->lflags & 0x40) {
               g->step = 8 * g->line_size; // first interlaced spacing
               g->parse = 3;
            } else {
               g->step = g->line_size;
               g->parse = 0;
            }

            if (g->lflags & 0x80) {
               stbi_gif_parse_colortable(s,g->lpal, 2 << (g->lflags & 7), g->eflags & 0x01 ? g->transparent : -1);
               g->color_table = (stbi__uint8 *) g->lpal;       
            } else if (g->flags & 0x80) {
               for (i=0; i < 256; ++i)  // @OPTIMIZE: reset only the previous transparent
                  g->pal[i][3] = 255; 
               if (g->transparent >= 0 && (g->eflags & 0x01))
                  g->pal[g->transparent][3] = 0;
               g->color_table = (stbi__uint8 *) g->pal;
            } else
               return epuc("missing color table", "Corrupt GIF");
   
            o = stbi_process_gif_raster(s, g);
            if (o == NULL) return NULL;

            if (req_comp && req_comp != 4)
               o = convert_format(o, 4, req_comp, g->w, g->h);
            return o;
         }

         case 0x21: // Comment Extension.
         {
            int len;
            if (get8(s) == 0xF9) { // Graphic Control Extension.
               len = get8(s);
               if (len == 4) {
                  g->eflags = get8(s);
                  get16le(s); // delay
                  g->transparent = get8(s);
               } else {
                  skip(s, len);
                  break;
               }
            }
            while ((len = get8(s)) != 0)
               skip(s, len);
            break;
         }

         case 0x3B: // gif stream termination code
            return (stbi__uint8 *) 1;

         default:
            return epuc("unknown code", "Corrupt GIF");
      }
   }
}