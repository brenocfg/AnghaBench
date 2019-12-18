#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GR_MODE_COPY ; 
 int /*<<< orphan*/  GrFillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  GrSetGCForeground (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GrSetGCMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gc ; 
 int /*<<< orphan*/ * g_ops ; 
 int /*<<< orphan*/  g_wnd ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void ui_destblt(uint8 opcode, int x, int y, int cx, int cy)
{
  uint32 op;

  if (opcode == 0) /* black */
  {
    GrSetGCForeground(g_gc, 0);
    opcode = 12;
  }
  else if (opcode == 5) /* invert */
  {
    GrSetGCForeground(g_gc, 0xffffffff);
    opcode = 6;
  }
  else if (opcode == 15) /* white */
  {
    GrSetGCForeground(g_gc, 0xffffffff);
    opcode = 12;
  }
  if (opcode == 12 || opcode == 6)
  {
    op = g_ops[opcode];
    GrSetGCMode(g_gc, op);
    GrFillRect(g_wnd, g_gc, x, y, cx, cy);
    GrSetGCMode(g_gc, GR_MODE_COPY);
  }
  else
  {
    unimpl("opcode %d in ui_destblt\n", opcode);
  }
}