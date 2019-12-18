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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/  colour; } ;
typedef  TYPE_1__ PEN ;

/* Variables and functions */
 int /*<<< orphan*/  rfbDrawLine (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server ; 

void
ui_line(uint8 opcode,
	/* dest */ int startx, int starty, int endx, int endy,
	/* pen */ PEN * pen)
{
	//vncSetRect(server,startx,starty,1+endx-startx,endy-starty,pen->colour);
	//unimpl("drawline: pen colour=%d\n",pen->colour);
	/* TODO: implement opcodes */
	rfbDrawLine(server, startx, starty, endx, endy, pen->colour);
}