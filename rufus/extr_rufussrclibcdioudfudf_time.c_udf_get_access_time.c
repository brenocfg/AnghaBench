#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  access_time; } ;
struct TYPE_5__ {TYPE_1__ fe; } ;
typedef  TYPE_2__ udf_dirent_t ;
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  udf_stamp_to_time (int /*<<< orphan*/ *,long*,int /*<<< orphan*/ ) ; 

time_t
udf_get_access_time(const udf_dirent_t *p_udf_dirent)
{
  if (p_udf_dirent) {
    time_t ret_time;
    long int usec;
    udf_stamp_to_time(&ret_time, &usec, p_udf_dirent->fe.access_time);
    return ret_time;
  }
  return 0;
}