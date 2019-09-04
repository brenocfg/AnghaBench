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
struct TYPE_4__ {int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biBitCount; int /*<<< orphan*/  biPlanes; } ;
struct TYPE_5__ {TYPE_1__ bmiHeader; } ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 

__attribute__((used)) static void ICCVID_dump_BITMAPINFO(const BITMAPINFO * bmi)
{
    TRACE(
        "planes = %d\n"
        "bpp    = %d\n"
        "height = %d\n"
        "width  = %d\n"
        "compr  = %s\n",
        bmi->bmiHeader.biPlanes,
        bmi->bmiHeader.biBitCount,
        bmi->bmiHeader.biHeight,
        bmi->bmiHeader.biWidth,
        debugstr_an( (const char *)&bmi->bmiHeader.biCompression, 4 ) );
}