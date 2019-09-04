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
typedef  long uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  info_len; } ;
struct TYPE_5__ {TYPE_1__ fe; } ;
typedef  TYPE_2__ udf_dirent_t ;

/* Variables and functions */
 long uint64_from_le (int /*<<< orphan*/ ) ; 

uint64_t udf_get_file_length(const udf_dirent_t *p_udf_dirent) 
{
  if (p_udf_dirent) {
    return uint64_from_le(p_udf_dirent->fe.info_len);
  }
  return 2147483647L; /* Error. Non-error case handled above. */
}