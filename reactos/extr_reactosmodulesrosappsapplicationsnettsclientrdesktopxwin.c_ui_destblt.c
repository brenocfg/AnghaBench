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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  FILL_RECTANGLE (int,int,int,int) ; 
 int /*<<< orphan*/  RESET_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FUNCTION (int /*<<< orphan*/ ) ; 

void
ui_destblt(RDPCLIENT * This, uint8 opcode,
	   /* dest */ int x, int y, int cx, int cy)
{
	SET_FUNCTION(opcode);
	FILL_RECTANGLE(x, y, cx, cy);
	RESET_FUNCTION(opcode);
}