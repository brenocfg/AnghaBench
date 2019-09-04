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
typedef  int uint32 ;
struct TYPE_3__ {int colour; } ;
typedef  TYPE_1__ PEN ;

/* Variables and functions */
 int COLOR16TO32 (int) ; 
 int GR_MODE_COPY ; 
 int /*<<< orphan*/  GrLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  GrSetGCForeground (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GrSetGCMode (int /*<<< orphan*/ ,int) ; 
 int g_bpp ; 
 int /*<<< orphan*/  g_gc ; 
 int* g_ops ; 
 int g_server_bpp ; 
 int /*<<< orphan*/  g_wnd ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void ui_line(uint8 opcode, int startx, int starty, int endx, int endy,
             PEN * pen)
{
  uint32 op;
  uint32 color;

  color = pen->colour;
  if (opcode == 5) /* GR_MODE_INVERT, not supported so convert it */
  {                /* i think x ^ -1 = ~x */
    color = 0xffffffff;
    opcode = 6; /* GR_MODE_XOR */
  }
  if (opcode == 12 || opcode == 6) /* nanox only supports these 2 opcode */
  {
    op = g_ops[opcode];
    GrSetGCMode(g_gc, op);
    if (g_server_bpp == 16 && g_bpp == 32)
    {
      color = COLOR16TO32(color);
    }
    GrSetGCForeground(g_gc, color);
    GrLine(g_wnd, g_gc, startx, starty, endx, endy);
    GrSetGCMode(g_gc, GR_MODE_COPY);
  }
  else
  {
    unimpl("opcode %d in ui_line\n", opcode);
  }
}