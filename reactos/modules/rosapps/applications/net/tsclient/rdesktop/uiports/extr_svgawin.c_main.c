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

/* Variables and functions */
 int /*<<< orphan*/  get_username_and_hostname () ; 
 int /*<<< orphan*/  parse_parameters (int,char**) ; 
 int /*<<< orphan*/  ui_create_window () ; 
 int /*<<< orphan*/  ui_deinit () ; 
 int /*<<< orphan*/  ui_destroy_window () ; 
 int /*<<< orphan*/  ui_init () ; 
 int /*<<< orphan*/  ui_main_loop () ; 

int main(int in_argc, char** in_argv)
{
  get_username_and_hostname();
  if (!parse_parameters(in_argc, in_argv))
    return 0;
  if (!ui_init())
    return 1;
  if (!ui_create_window())
    return 1;
  ui_main_loop();
  ui_destroy_window();
  ui_deinit();
  return 0;
}