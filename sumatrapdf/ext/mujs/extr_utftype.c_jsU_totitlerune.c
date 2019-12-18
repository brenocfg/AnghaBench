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
typedef  scalar_t__ const Rune ;

/* Variables and functions */
 int /*<<< orphan*/  __totitle1 ; 
 scalar_t__* bsearch (scalar_t__ const,int /*<<< orphan*/ ,int,int) ; 
 int nelem (int /*<<< orphan*/ ) ; 

Rune
totitlerune(Rune c)
{
	const Rune *p;

	p = bsearch(c, __totitle1, nelem(__totitle1)/2, 2);
	if(p && c == p[0])
		return c + p[1] - 500;
	return c;
}