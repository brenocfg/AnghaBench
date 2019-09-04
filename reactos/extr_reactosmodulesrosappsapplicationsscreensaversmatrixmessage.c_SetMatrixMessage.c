#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int width; int height; int** message; } ;
struct TYPE_8__ {int right; int left; int bottom; int top; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ MATRIX_MESSAGE ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int DT_CALCRECT ; 
 int DT_CENTER ; 
 int DT_VCENTER ; 
 int DT_WORDBREAK ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetPixel (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXMSG_HEIGHT ; 
 int /*<<< orphan*/  MAXMSG_WIDTH ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  g_hFont ; 

void SetMatrixMessage(MATRIX_MESSAGE *msg, HFONT hFont, TCHAR *text)
{
	HDC		hdc;
	RECT	rect;
	int		x, y;

	HDC		hdcMessage;
	HBITMAP hbmMessage;

	HANDLE	hOldFont, hOldBmp;

	//
	// Create a monochrome off-screen buffer
	//
	hdc = GetDC(NULL);

	hdcMessage = CreateCompatibleDC(hdc);
	hbmMessage = CreateBitmap(MAXMSG_WIDTH, MAXMSG_HEIGHT, 1, 1, 0);
	hOldBmp    = SelectObject(hdcMessage, hbmMessage);

	ReleaseDC(NULL, hdc);

	//
	// Draw text into bitmap
	//
	SetRect(&rect, 0, 0, msg->width, MAXMSG_HEIGHT);
	FillRect(hdcMessage, &rect, GetStockObject(WHITE_BRUSH));

	hOldFont = SelectObject(hdcMessage, g_hFont);
	DrawText(hdcMessage, text, -1, &rect, DT_CENTER|DT_VCENTER|DT_WORDBREAK|DT_CALCRECT);

	OffsetRect(&rect, (msg->width-(rect.right-rect.left))/2, (msg->height-(rect.bottom-rect.top))/2);
	DrawText(hdcMessage, text, -1, &rect, DT_CENTER|DT_VCENTER|DT_WORDBREAK);

	//
	// Convert bitmap into an array of cells for easy drawing
	//
	for(y = 0; y < msg->height; y++)
	{
		for(x = 0; x < msg->width; x++)
		{
			msg->message[x][y] = GetPixel(hdcMessage, x, y) ? 0 : 1;
		}
	}

	//
	//	Cleanup
	//
	SelectObject(hdcMessage, hOldFont);
	SelectObject(hdcMessage, hOldBmp);

	DeleteDC(hdcMessage);
	DeleteObject(hbmMessage);
}