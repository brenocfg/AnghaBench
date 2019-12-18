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
struct sg_io_hdr {int /*<<< orphan*/  sb_len_wr; int /*<<< orphan*/  sbp; int /*<<< orphan*/  driver_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  msg_status; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int sg_err_category_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sg_err_category3(struct sg_io_hdr *hp) {
        return sg_err_category_new(hp->status, hp->msg_status,
                                   hp->host_status, hp->driver_status,
                                   hp->sbp, hp->sb_len_wr);
}