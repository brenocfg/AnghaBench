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
struct chmcLzxInfo {scalar_t__ done; scalar_t__ todo; scalar_t__ eof; scalar_t__ error; } ;

/* Variables and functions */

__attribute__((used)) static int _lzx_at_eof(void *arg)
{
	struct chmcLzxInfo *lzx_info = (struct chmcLzxInfo *)arg;

	return lzx_info->error || lzx_info->done >= lzx_info->todo || lzx_info->eof;
}