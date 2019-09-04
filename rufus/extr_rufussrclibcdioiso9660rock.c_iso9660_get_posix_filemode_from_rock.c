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
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ iso_rock_statbuf_t ;

/* Variables and functions */

mode_t
iso9660_get_posix_filemode_from_rock(const iso_rock_statbuf_t *rr)
{
  return (mode_t) rr->st_mode;
}