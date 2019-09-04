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
struct optioninfo {int dummy; } ;

/* Variables and functions */
 char const* config_text ; 

void of_config(const struct optioninfo *oi, const char *arg, const char *arg2) {
  config_text= arg;
}