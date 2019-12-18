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
typedef  scalar_t__ WORD ;
struct TYPE_6__ {int counter; scalar_t__ random_reg1; void* height; void* width; scalar_t__ msgindex; } ;
typedef  TYPE_1__ MATRIX_MESSAGE ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ClearMatrixMessage (TYPE_1__*) ; 
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  MAXMSG_HEIGHT ; 
 int /*<<< orphan*/  MAXMSG_WIDTH ; 
 int MSGSPEED_MIN ; 
 int /*<<< orphan*/  SetMatrixMessage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMessageFont (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crc_rand () ; 
 int /*<<< orphan*/  g_fFontBold ; 
 int /*<<< orphan*/  g_nFontSize ; 
 int /*<<< orphan*/  g_szFontName ; 
 int /*<<< orphan*/ * g_szMessages ; 
 TYPE_1__* malloc (int) ; 
 void* min (int,int /*<<< orphan*/ ) ; 

MATRIX_MESSAGE *InitMatrixMessage(HWND hwnd, int width, int height)
{
	MATRIX_MESSAGE *msg;

	if((msg = malloc(sizeof(MATRIX_MESSAGE))) == 0)
		return 0;

	ClearMatrixMessage(msg);

	msg->msgindex = 0;
	msg->width    = min(width, MAXMSG_WIDTH);
	msg->height   = min(height, MAXMSG_HEIGHT);
	msg->counter  = -(int)(crc_rand() % MSGSPEED_MIN + MSGSPEED_MIN);

	msg->random_reg1 = (WORD)GetTickCount();

	SetMessageFont(hwnd, g_szFontName, g_nFontSize, g_fFontBold);

	SetMatrixMessage(msg, 0, g_szMessages[0]);

	return msg;
}