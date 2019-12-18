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
 int EOF ; 
 int char_avail ; 
 int ungot_char ; 

int _ungetch(int c)
{
  if (char_avail)
    return(EOF);
  ungot_char = c;
  char_avail = 1;
  return(c);
}