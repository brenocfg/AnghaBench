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
typedef  int /*<<< orphan*/  udf_file_entry_t ;
struct TYPE_3__ {int /*<<< orphan*/  fe; } ;
typedef  TYPE_1__ udf_dirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool
udf_get_file_entry(const udf_dirent_t *p_udf_dirent, 
		   /*out*/ udf_file_entry_t *p_udf_fe)
{
  if (!p_udf_dirent) return false;
  memcpy(p_udf_fe, &p_udf_dirent->fe, sizeof(udf_file_entry_t));
  return true;
}