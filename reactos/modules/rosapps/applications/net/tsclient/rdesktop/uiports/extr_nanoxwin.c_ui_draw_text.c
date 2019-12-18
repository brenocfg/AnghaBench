#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_3__ {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  FONTGLYPH ;
typedef  TYPE_1__ DATABLOB ;
typedef  int /*<<< orphan*/  BRUSH ;

/* Variables and functions */
 int COLOR16TO32 (int) ; 
 int /*<<< orphan*/  DO_GLYPH (int*,int) ; 
 int /*<<< orphan*/  GR_MODE_COPY ; 
 int /*<<< orphan*/  GrFillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  GrSetGCForeground (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GrSetGCMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrSetGCUseBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MIX_OPAQUE ; 
 int TEXT2_IMPLICIT_X ; 
 int TEXT2_VERTICAL ; 
 TYPE_1__* cache_get_text (int) ; 
 int /*<<< orphan*/  cache_put_text (int,int*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int g_bpp ; 
 int /*<<< orphan*/  g_gc ; 
 int g_server_bpp ; 
 int g_width ; 
 int /*<<< orphan*/  g_wnd ; 

void ui_draw_text(uint8 font, uint8 flags, uint8 opcode, int mixmode,
                  int x, int y,
                  int clipx, int clipy, int clipcx, int clipcy,
                  int boxx, int boxy, int boxcx, int boxcy, BRUSH * brush,
                  int bgcolor, int fgcolor, uint8 * text, uint8 length)
{
  FONTGLYPH * glyph;
  int i, j, xyoffset, x1, y1;
  DATABLOB * entry;

  GrSetGCMode(g_gc, GR_MODE_COPY);
  GrSetGCUseBackground(g_gc, 0); /* this can be set when gc is created */
  if (g_server_bpp == 16 && g_bpp == 32)
  {
    fgcolor = COLOR16TO32(fgcolor);
    bgcolor = COLOR16TO32(bgcolor);
  }
  GrSetGCForeground(g_gc, bgcolor);
  if (boxx + boxcx > g_width)
  {
    boxcx = g_width - boxx;
  }
  if (boxcx > 1)
  {
    GrFillRect(g_wnd, g_gc, boxx, boxy, boxcx, boxcy);
  }
  else if (mixmode == MIX_OPAQUE)
  {
    GrFillRect(g_wnd, g_gc, clipx, clipy, clipcx, clipcy);
  }
  GrSetGCForeground(g_gc, fgcolor);
  /* Paint text, character by character */
  for (i = 0; i < length;)
  {
    switch (text[i])
    {
      case 0xff:
        if (i + 2 < length)
        {
          cache_put_text(text[i + 1], text, text[i + 2]);
        }
        else
        {
          error("this shouldn't be happening\n");
          exit(1);
        }
        /* this will move pointer from start to first character after */
        /* FF command */
        length -= i + 3;
        text = &(text[i + 3]);
        i = 0;
        break;
      case 0xfe:
        entry = cache_get_text(text[i + 1]);
        if (entry != NULL)
        {
          if ((((uint8 *) (entry->data))[1] == 0) &&
                                (!(flags & TEXT2_IMPLICIT_X)))
          {
            if (flags & TEXT2_VERTICAL)
            {
              y += text[i + 2];
            }
            else
            {
              x += text[i + 2];
            }
          }
          for (j = 0; j < entry->size; j++)
          {
            DO_GLYPH(((uint8 *) (entry->data)), j);
          }
        }
        if (i + 2 < length)
        {
          i += 3;
        }
        else
        {
          i += 2;
        }
        length -= i;
        /* this will move pointer from start to first character after */
        /* FE command */
        text = &(text[i]);
        i = 0;
        break;
      default:
        DO_GLYPH(text, i);
        i++;
        break;
    }
  }
}