#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numcols; scalar_t__ message; int /*<<< orphan*/ * column; } ;
typedef  TYPE_1__ MATRIX ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DoMatrixMessage (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GLYPH_WIDTH ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RandomMatrixColumn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedrawMatrixColumn (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScrollMatrixColumn (int /*<<< orphan*/ *) ; 

void DecodeMatrix(HWND hwnd, MATRIX *matrix)
{
	int x;
	HDC hdc = GetDC(hwnd);

	for(x = 0; x < matrix->numcols; x++)
	{
		RandomMatrixColumn(&matrix->column[x]);
		ScrollMatrixColumn(&matrix->column[x]);
		RedrawMatrixColumn(&matrix->column[x], matrix, hdc, x * GLYPH_WIDTH);
	}

	if(matrix->message)
		DoMatrixMessage(hdc, matrix);

	ReleaseDC(hwnd, hdc);
}