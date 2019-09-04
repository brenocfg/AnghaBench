#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct chmcSect0 {int file_len; } ;
struct chmcLzxInfo {TYPE_2__* section; TYPE_1__* chm; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {struct chmcSect0 sect0; } ;

/* Variables and functions */
 int write (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int _lzx_put_bytes(void *arg, int n, void *buf)
{
	struct chmcLzxInfo *lzx_info = (struct chmcLzxInfo *)arg;
	struct chmcSect0 *sect0 = &lzx_info->chm->sect0;
	int wx;
	static int counter = 0;

	counter += n;
	wx = write(lzx_info->section->fd, buf, n);
	sect0->file_len += wx;
	lzx_info->section->len += wx;

	return wx;
}