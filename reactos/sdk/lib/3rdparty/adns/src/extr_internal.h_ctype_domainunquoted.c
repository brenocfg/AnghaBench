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
 scalar_t__ ctype_alpha (int) ; 
 scalar_t__ ctype_digit (int) ; 
 scalar_t__ strchr (char*,int) ; 

__attribute__((used)) static inline int ctype_domainunquoted(int c) {
  return ctype_alpha(c) || ctype_digit(c) || (strchr("-_/+",c) != 0);
}