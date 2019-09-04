#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ keysym; char const* string; } ;
typedef  scalar_t__ KeySym ;

/* Variables and functions */
 scalar_t__ NoSymbol ; 
 TYPE_1__* StringToKeysym ; 

const char *
XKeysymToString(KeySym keysym)
{
	int i;
	for (i = 0; StringToKeysym[i].keysym != NoSymbol
	     && StringToKeysym[i].keysym != keysym; i++);
	return StringToKeysym[i].string;
}