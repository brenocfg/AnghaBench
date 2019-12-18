#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  drr ;
struct TYPE_5__ {int /*<<< orphan*/  drr_checksum; } ;
struct TYPE_6__ {TYPE_1__ drr_end; } ;
struct TYPE_7__ {TYPE_2__ drr_u; int /*<<< orphan*/  drr_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ dmu_replay_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRR_END ; 
 int errno ; 
 int write (int,TYPE_3__*,int) ; 

__attribute__((used)) static int
send_conclusion_record(int fd, zio_cksum_t *zc)
{
	dmu_replay_record_t drr = { 0 };
	drr.drr_type = DRR_END;
	if (zc != NULL)
		drr.drr_u.drr_end.drr_checksum = *zc;
	if (write(fd, &drr, sizeof (drr)) == -1) {
		return (errno);
	}
	return (0);
}