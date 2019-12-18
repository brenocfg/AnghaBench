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
struct TYPE_2__ {int tb_change_cnt; scalar_t__ tb_off; scalar_t__ tb_len; int /*<<< orphan*/  tb_buflen; int /*<<< orphan*/  tb_noremap; int /*<<< orphan*/ * tb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPELEN_INIT ; 
 int /*<<< orphan*/  noremapbuf_init ; 
 TYPE_1__ typebuf ; 
 int /*<<< orphan*/ * typebuf_init ; 

__attribute__((used)) static void
init_typebuf()
{
    if (typebuf.tb_buf == NULL)
    {
	typebuf.tb_buf = typebuf_init;
	typebuf.tb_noremap = noremapbuf_init;
	typebuf.tb_buflen = TYPELEN_INIT;
	typebuf.tb_len = 0;
	typebuf.tb_off = 0;
	typebuf.tb_change_cnt = 1;
    }
}