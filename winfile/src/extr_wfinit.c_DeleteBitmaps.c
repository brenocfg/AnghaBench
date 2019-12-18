#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  SelectObject (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ hbmBitmaps ; 
 int /*<<< orphan*/  hbmSave ; 
 scalar_t__ hdcMem ; 

VOID
DeleteBitmaps()
{
   if (hdcMem) {

      SelectObject(hdcMem, hbmSave);

      if (hbmBitmaps)
         DeleteObject(hbmBitmaps);
      DeleteDC(hdcMem);
   }
}