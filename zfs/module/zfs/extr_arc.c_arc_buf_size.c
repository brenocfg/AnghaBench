#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  b_hdr; } ;
typedef  TYPE_1__ arc_buf_t ;

/* Variables and functions */
 scalar_t__ ARC_BUF_COMPRESSED (TYPE_1__*) ; 
 int /*<<< orphan*/  HDR_GET_LSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDR_GET_PSIZE (int /*<<< orphan*/ ) ; 

uint64_t
arc_buf_size(arc_buf_t *buf)
{
	return (ARC_BUF_COMPRESSED(buf) ?
	    HDR_GET_PSIZE(buf->b_hdr) : HDR_GET_LSIZE(buf->b_hdr));
}