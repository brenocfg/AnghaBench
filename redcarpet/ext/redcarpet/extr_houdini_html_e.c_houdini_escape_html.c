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
typedef  int /*<<< orphan*/  uint8_t ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  houdini_escape_html0 (struct buf*,int /*<<< orphan*/  const*,size_t,int) ; 

void
houdini_escape_html(struct buf *ob, const uint8_t *src, size_t size)
{
	houdini_escape_html0(ob, src, size, 1);
}