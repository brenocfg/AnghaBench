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
typedef  int /*<<< orphan*/  bitmap_data ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; int /*<<< orphan*/  const* data; TYPE_1__ IWICBitmapSource_iface; } ;
typedef  TYPE_2__ BitmapTestSrc ;

/* Variables and functions */
 int /*<<< orphan*/  BitmapTestSrc_Vtbl ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CreateTestBitmap(const bitmap_data *data, BitmapTestSrc **This)
{
    *This = HeapAlloc(GetProcessHeap(), 0, sizeof(**This));

    if (*This)
    {
        (*This)->IWICBitmapSource_iface.lpVtbl = &BitmapTestSrc_Vtbl;
        (*This)->ref = 1;
        (*This)->data = data;
    }
}