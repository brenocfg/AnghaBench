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
 scalar_t__ myisalnum (char*) ; 
 char* prev_char (char*,char*) ; 

__attribute__((used)) static char *prev_word(char *p, char *start)
{
	while (p > start && !myisalnum(prev_char(p, start))) p = prev_char(p, start);
	while (p > start && myisalnum(prev_char(p, start))) p = prev_char(p, start);
	return p;
}