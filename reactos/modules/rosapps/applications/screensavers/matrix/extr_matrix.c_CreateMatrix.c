#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numcols; int numrows; int width; int height; scalar_t__ message; int /*<<< orphan*/  hbmBitmap; int /*<<< orphan*/  hdcBitmap; TYPE_1__* column; } ;
struct TYPE_4__ {int length; int countdown; int state; int runlen; scalar_t__* glyph; int /*<<< orphan*/  started; } ;
typedef  int /*<<< orphan*/  MATRIX_COLUMN ;
typedef  TYPE_2__ MATRIX ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GLYPH ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GLYPH_HEIGHT ; 
 int GLYPH_WIDTH ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDB_BITMAP1 ; 
 scalar_t__ InitMatrixMessage (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LoadBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crc_rand () ; 
 void* malloc (int) ; 

MATRIX *CreateMatrix(HWND hwnd, int width, int height)
{
	MATRIX *matrix;
	HDC hdc;
	int x, y;

	int rows = height / GLYPH_HEIGHT + 1;
	int cols = width  / GLYPH_WIDTH  + 1;

	// allocate matrix!
	if((matrix = malloc(sizeof(MATRIX) + sizeof(MATRIX_COLUMN) * cols)) == 0)
		return 0;

	matrix->numcols = cols;
	matrix->numrows = rows;
	matrix->width   = width;
	matrix->height  = height;

	for(x = 0; x < cols; x++)
	{
		matrix->column[x].length       = rows;
		matrix->column[x].started      = FALSE;
		matrix->column[x].countdown    = crc_rand() % 100;
		matrix->column[x].state        = crc_rand() % 2;
		matrix->column[x].runlen       = crc_rand() % 20 + 3;

		matrix->column[x].glyph  = malloc(sizeof(GLYPH) * (rows+16));

		for(y = 0; y < rows; y++)
			matrix->column[x].glyph[y] = 0;//;
	}

	// Load bitmap!!
	hdc = GetDC(NULL);
	matrix->hbmBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
	matrix->hdcBitmap = CreateCompatibleDC(hdc);
	SelectObject(matrix->hdcBitmap, matrix->hbmBitmap);
	ReleaseDC(NULL, hdc);

	// Create a message for this window...only if we are
	// screen-saving (not if in preview mode)
	if(GetParent(hwnd) == 0)
		matrix->message = InitMatrixMessage(hwnd, matrix->numcols, matrix->numrows);
	else
		matrix->message = 0;

	return matrix;
}