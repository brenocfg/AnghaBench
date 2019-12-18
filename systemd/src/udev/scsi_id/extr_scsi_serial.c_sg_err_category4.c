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
struct sg_io_v4 {int /*<<< orphan*/  response_len; scalar_t__ response; int /*<<< orphan*/  driver_status; int /*<<< orphan*/  transport_status; int /*<<< orphan*/  device_status; } ;

/* Variables and functions */
 int sg_err_category_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sg_err_category4(struct sg_io_v4 *hp) {
        return sg_err_category_new(hp->device_status, 0,
                                   hp->transport_status, hp->driver_status,
                                   (unsigned char *)(uintptr_t)hp->response,
                                   hp->response_len);
}