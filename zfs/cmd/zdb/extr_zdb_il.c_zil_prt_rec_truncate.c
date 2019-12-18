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
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_2__ {scalar_t__ lr_length; scalar_t__ lr_offset; scalar_t__ lr_foid; } ;
typedef  TYPE_1__ lr_truncate_t ;
typedef  int /*<<< orphan*/  longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tab_prefix ; 

__attribute__((used)) static void
zil_prt_rec_truncate(zilog_t *zilog, int txtype, void *arg)
{
	lr_truncate_t *lr = arg;

	(void) printf("%sfoid %llu, offset 0x%llx, length 0x%llx\n", tab_prefix,
	    (u_longlong_t)lr->lr_foid, (longlong_t)lr->lr_offset,
	    (u_longlong_t)lr->lr_length);
}