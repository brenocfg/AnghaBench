#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int width; int height; } ;
typedef  int BOOL ;

/* Variables and functions */
 int clipH ; 
 int clipW ; 
 int clipX ; 
 int clipY ; 
 TYPE_1__* server ; 

BOOL
vncwinClipRect(int *x, int *y, int *cx, int *cy)
{
	if (*x + *cx > clipX + clipW)
		*cx = clipX + clipW - *x;
	if (*y + *cy > clipY + clipH)
		*cy = clipY + clipH - *y;
	if (*x < clipX)
	{
		*cx -= clipX - *x;
		*x = clipX;
	}
	if (*y < clipY)
	{
		*cy -= clipY - *y;
		*y = clipY;
	}
	if (*cx < 0 || *cy < 0)
		*cx = *cy = 0;
	return (*cx > 0 && *cy > 0 && *x < server->width && *y < server->height);
}