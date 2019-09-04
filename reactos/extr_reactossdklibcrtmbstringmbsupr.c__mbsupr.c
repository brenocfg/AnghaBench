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
 scalar_t__ _MBIS16 (int) ; 
 int /*<<< orphan*/  _mbset (unsigned char*,int) ; 
 unsigned char* _mbsinc (unsigned char*) ; 
 int _mbsnextc (unsigned char*) ; 
 int toupper (int) ; 

unsigned char *_mbsupr (unsigned char *string)
{
    int c;
    unsigned char *save = string;

    while ((c = _mbsnextc (string))) {

	if (_MBIS16 (c) == 0)
	    c = toupper (c);

	_mbset (string, c);

	string = _mbsinc (string);

    }

    return save;
}