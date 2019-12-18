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
struct TYPE_3__ {int width; int height; int** message; } ;
typedef  TYPE_1__ MATRIX_MESSAGE ;
typedef  int /*<<< orphan*/  MATRIX ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DrawGlyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int GLYPH_HEIGHT ; 
 int GLYPH_WIDTH ; 
 int /*<<< orphan*/  MAX_INTENSITY ; 
 int /*<<< orphan*/  RandomGlyph (int /*<<< orphan*/ ) ; 

void DrawMatrixMessage(MATRIX *matrix, MATRIX_MESSAGE *msg, HDC hdc)
{
	int x, y;

	for(x = 0; x < msg->width; x++)
		for(y = 0; y < msg->height; y++)
			if((msg->message[x][y] & 0x8000) &&
			   (msg->message[x][y] & 0x00FF))
			{
				DrawGlyph(matrix, hdc, x * GLYPH_WIDTH, y * GLYPH_HEIGHT, RandomGlyph(MAX_INTENSITY));
			}
}