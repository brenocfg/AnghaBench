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
 int /*<<< orphan*/  _MBGETH (int) ; 
 int /*<<< orphan*/  _MBGETL (int) ; 
 scalar_t__ _MBIS16 (int) ; 
 scalar_t__ _MBLMASK (int) ; 

unsigned char *_mbset (unsigned char *string, int c)
{
    unsigned char *save = string;

    if (_MBIS16 (c)) {

	if (_MBLMASK (c) == 0) {
	    *string++ = '\0';
	    *string++ = '\0';
	}
	else {
	    *string++ = _MBGETH (c);
	    *string++ = _MBGETL (c);
	}

    }
    else {

	*string++ = c;

    }

    return save;
}