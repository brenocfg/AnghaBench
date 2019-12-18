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
struct TYPE_5__ {int biSize; int biPlanes; int biBitCount; int /*<<< orphan*/  biSizeImage; int /*<<< orphan*/  biCompression; void* biHeight; void* biWidth; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  void* LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_bmi(BITMAPINFO *bmi, LONG width, LONG height, DWORD size)
{
    memset(bmi, 0, sizeof(*bmi));
    bmi->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi->bmiHeader.biWidth       = width;
    bmi->bmiHeader.biHeight      = height;
    bmi->bmiHeader.biPlanes      = 1;
    bmi->bmiHeader.biBitCount    = 32;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biSizeImage   = size;
}