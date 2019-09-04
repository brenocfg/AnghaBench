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
 int /*<<< orphan*/  _MBGETH (unsigned int) ; 
 int /*<<< orphan*/  _MBGETL (unsigned int) ; 
 scalar_t__ _ismbblead (int /*<<< orphan*/ ) ; 
 scalar_t__ _ismbbtrail (int /*<<< orphan*/ ) ; 

int _ismbclegal(unsigned int c)
{
	return (_ismbblead (_MBGETH (c)) && _ismbbtrail (_MBGETL (c)));
}