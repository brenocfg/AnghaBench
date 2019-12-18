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
struct TYPE_2__ {int (* filter ) (char const*) ;} ;

/* Variables and functions */
 TYPE_1__ fc ; 
 int /*<<< orphan*/  load_dir (char const*) ; 

void ui_init_open_file(const char *dir, int (*filter)(const char *fn))
{
	fc.filter = filter;
	load_dir(dir);
}