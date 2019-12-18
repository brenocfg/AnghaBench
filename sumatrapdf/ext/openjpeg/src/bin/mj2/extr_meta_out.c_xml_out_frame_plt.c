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
typedef  int /*<<< orphan*/  opj_tcp_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */

void xml_out_frame_plt(FILE* xmlout,
                       opj_tcp_t *tcp)   /* opt, tile-part headers only; can be used in conjunction with main header's PLM */
{
    /* NO-OP.  PLT NOT SAVED IN DATA STRUCTURE */
    /* Compare j2k_read_plt()... which doesn't retain anything! */
    /* Tile-part header indents are 12 spaces */
}