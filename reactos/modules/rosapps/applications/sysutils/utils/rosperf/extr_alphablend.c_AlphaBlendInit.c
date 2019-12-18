#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  BitmapDc; int /*<<< orphan*/  Bitmap; } ;
struct TYPE_5__ {scalar_t__ WndWidth; scalar_t__ WndHeight; int /*<<< orphan*/  BackgroundDc; } ;
typedef  TYPE_1__* PPERF_INFO ;
typedef  TYPE_2__* PALPHABLEND_CONTEXT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  ALPHABLEND_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixel (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

unsigned
AlphaBlendInit(void **Context, PPERF_INFO PerfInfo, unsigned Reps)
{
  PALPHABLEND_CONTEXT ctx = HeapAlloc(GetProcessHeap(), 0, sizeof (ALPHABLEND_CONTEXT));
  INT x, y;

  ctx->BitmapDc = CreateCompatibleDC(PerfInfo->BackgroundDc);
  ctx->Bitmap = CreateCompatibleBitmap(PerfInfo->BackgroundDc, PerfInfo->WndWidth, PerfInfo->WndHeight);
  SelectObject(ctx->BitmapDc, ctx->Bitmap);

  for (y = 0; y < PerfInfo->WndHeight; y++)
    {
      for (x = 0; x < PerfInfo->WndWidth; x++)
        {
          SetPixel(ctx->BitmapDc, x, y, RGB(0xff, 0x00, 0x00));
        }
    }

  *Context = ctx;

  return Reps;
}