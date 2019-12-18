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
 int TOLOWER_ASC (int) ; 
 scalar_t__ VIM_ISDIGIT (int) ; 

__attribute__((used)) static int
hex_digit(int c)
{
    if (VIM_ISDIGIT(c))
	return c - '0';
    c = TOLOWER_ASC(c);
    if (c >= 'a' && c <= 'f')
	return c - 'a' + 10;
    return -1000;
}