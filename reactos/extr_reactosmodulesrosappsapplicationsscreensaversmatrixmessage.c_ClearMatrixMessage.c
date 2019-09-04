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
struct TYPE_3__ {int width; int height; scalar_t__** message; } ;
typedef  TYPE_1__ MATRIX_MESSAGE ;

/* Variables and functions */

void ClearMatrixMessage(MATRIX_MESSAGE *msg)
{
	int x, y;

	for(x = 0; x < msg->width; x++)
		for(y = 0; y < msg->height; y++)
			msg->message[x][y] = 0;
}