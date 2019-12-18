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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dbi_len; scalar_t__ dbi_buf; int /*<<< orphan*/  dbi_vp; int /*<<< orphan*/  dbi_err; } ;
typedef  TYPE_1__ dump_bytes_io_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  FAPPEND ; 
 int /*<<< orphan*/  RLIM64_INFINITY ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_bytes_cb(void *arg)
{
	dump_bytes_io_t *dbi = (dump_bytes_io_t *)arg;
	ssize_t resid; /* have to get resid to get detailed errno */

	dbi->dbi_err = vn_rdwr(UIO_WRITE, dbi->dbi_vp,
	    (caddr_t)dbi->dbi_buf, dbi->dbi_len,
	    0, UIO_SYSSPACE, FAPPEND, RLIM64_INFINITY, CRED(), &resid);
}