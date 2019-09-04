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
 int /*<<< orphan*/  _mbscpy (unsigned char*,unsigned char const*) ; 
 scalar_t__ _mbslen (unsigned char const*) ; 
 scalar_t__ malloc (scalar_t__) ; 

unsigned char * _mbsdup(const unsigned char *_s)
{
	unsigned char *rv;
	if (_s == 0)
		return 0;
	rv = (unsigned char *)malloc(_mbslen(_s) + 1);
	if (rv == 0)
		return 0;
	_mbscpy(rv, _s);
	return rv;
}