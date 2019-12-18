#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ vncBuffer ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* vncNewBuffer (int,int,int) ; 

HBITMAP
ui_create_bitmap(int width, int height, uint8 * data)
{
	vncBuffer *buf;

	buf = vncNewBuffer(width, height, 8);
	memcpy(buf->data, data, width * height);

	return (HBITMAP) buf;
}