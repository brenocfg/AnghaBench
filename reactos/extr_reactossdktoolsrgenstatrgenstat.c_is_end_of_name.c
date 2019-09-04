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
 int is_end_of_tag (char) ; 

__attribute__((used)) static int
is_end_of_name(char ch)
{
  /* Currently the same as is_end_of_tag() */
  return is_end_of_tag(ch);
}