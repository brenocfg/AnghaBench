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
struct screen {int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int VIS_CSTYLE ; 
 int VIS_NL ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_stravis (int /*<<< orphan*/ *,char const*,int) ; 

void
screen_set_title(struct screen *s, const char *title)
{
	free(s->title);
	utf8_stravis(&s->title, title, VIS_OCTAL|VIS_CSTYLE|VIS_TAB|VIS_NL);
}