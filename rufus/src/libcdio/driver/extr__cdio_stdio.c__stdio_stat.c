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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  st_size; } ;
typedef  TYPE_1__ _UserData ;

/* Variables and functions */

__attribute__((used)) static off_t
_stdio_stat(void *p_user_data)
{
  const _UserData *const ud = p_user_data;

  return ud->st_size;
}