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
 int /*<<< orphan*/  _ismbblead (unsigned int) ; 
 unsigned int toupper (unsigned int) ; 

unsigned int _mbbtoupper(unsigned int c)
{
	if (!_ismbblead(c) )
		return toupper(c);

	return c;
}