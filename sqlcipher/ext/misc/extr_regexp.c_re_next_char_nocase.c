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
typedef  int /*<<< orphan*/  ReInput ;

/* Variables and functions */
 unsigned int re_next_char (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned re_next_char_nocase(ReInput *p){
  unsigned c = re_next_char(p);
  if( c>='A' && c<='Z' ) c += 'a' - 'A';
  return c;
}