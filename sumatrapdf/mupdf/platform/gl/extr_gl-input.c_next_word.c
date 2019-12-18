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
 char* next_char (char*) ; 

__attribute__((used)) static char *next_word(char *p, char *end)
{
	while (p < end && !myisalnum(p)) p = next_char(p);
	while (p < end && myisalnum(p)) p = next_char(p);
	return p;
}