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
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 unsigned int seamless_send (int /*<<< orphan*/ *,char*,char*,unsigned long,int,int,int,int,unsigned long) ; 

unsigned int
seamless_send_position(RDPCLIENT * This, unsigned long id, int x, int y, int width, int height, unsigned long flags)
{
	return seamless_send(This, "POSITION", "0x%08lx,%d,%d,%d,%d,0x%lx", id, x, y, width, height,
			     flags);
}