#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ readonly; } ;
typedef  TYPE_1__ device_extension ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_MEDIA_WRITE_PROTECTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static NTSTATUS is_writable(device_extension* Vcb) {
    TRACE("IOCTL_DISK_IS_WRITABLE\n");

    return Vcb->readonly ? STATUS_MEDIA_WRITE_PROTECTED : STATUS_SUCCESS;
}