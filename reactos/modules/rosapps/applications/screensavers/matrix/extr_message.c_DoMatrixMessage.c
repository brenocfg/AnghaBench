#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* message; } ;
struct TYPE_9__ {int counter; int msgindex; } ;
typedef  TYPE_1__ MATRIX_MESSAGE ;
typedef  TYPE_2__ MATRIX ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ClearMatrixMessage (TYPE_1__*) ; 
 int /*<<< orphan*/  DrawMatrixMessage (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MSGSPEED_MAX ; 
 int MSGSPEED_MIN ; 
 int MessageSpeed () ; 
 int /*<<< orphan*/  RevealMatrixMessage (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SetMatrixMessage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crc_rand () ; 
 scalar_t__ g_fRandomizeMessages ; 
 int g_nMessageSpeed ; 
 int g_nNumMessages ; 
 int /*<<< orphan*/ * g_szMessages ; 

void DoMatrixMessage(HDC hdc, MATRIX *matrix)
{
	MATRIX_MESSAGE *msg = matrix->message;

	int RealSpeed = MessageSpeed();

	if(g_nNumMessages > 0)
	{
		// nothing to do yet..
		if(msg->counter++ < 0)
			return;

		// has counter reached limit..clear the message
		if(msg->counter++ == RealSpeed / 2 + (RealSpeed/4))
			ClearMatrixMessage(msg);

		// reset counter + display a new message
		if(msg->counter >= RealSpeed)
		{
			// mark all message-cells as being "invisible" so the
			// message gets cleared by the matrix decoding naturally

			if(g_fRandomizeMessages)
				msg->msgindex = crc_rand() % g_nNumMessages;
			else
				msg->msgindex = (msg->msgindex + 1) % g_nNumMessages;

			// make a new message..initially invisible
			SetMatrixMessage(msg, 0, g_szMessages[msg->msgindex]);

			msg->counter = -(int)(crc_rand() % MSGSPEED_MAX);
		}
		// reveal the next part of the message
		else if(msg->counter < RealSpeed / 2)
		{
			int w = (g_nMessageSpeed - MSGSPEED_MIN);
			w = (1 << 16) + ((w<<16) / MSGSPEED_MAX);
			w = (w * 3 * g_nMessageSpeed) >> 16;

			RevealMatrixMessage(msg, w + 100);
		}

		//
		// draw whatever part of the message is visible at this time
		//
		DrawMatrixMessage(matrix, msg, hdc);
	}
}