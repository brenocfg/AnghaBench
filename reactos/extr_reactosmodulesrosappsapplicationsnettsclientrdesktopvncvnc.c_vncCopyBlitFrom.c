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
typedef  int /*<<< orphan*/  vncBuffer ;
typedef  int /*<<< orphan*/  rfbScreenInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  rfbMarkRectAsModified (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  vncCopyBlitFromNoEncode (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 

void
vncCopyBlitFrom(rfbScreenInfoPtr s, int x, int y, int w, int h, vncBuffer * src, int srcx, int srcy)
{
	vncCopyBlitFromNoEncode(s, x, y, w, h, src, srcx, srcy);
	rfbMarkRectAsModified(s, x, y, x + w, y + h);
}