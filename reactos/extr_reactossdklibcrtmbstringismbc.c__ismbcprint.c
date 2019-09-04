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
 scalar_t__ _MBHMASK (unsigned int) ; 
 scalar_t__ _ismbbkana (unsigned int) ; 
 int _ismbclegal (unsigned int) ; 
 scalar_t__ isprint (unsigned int) ; 

int _ismbcprint( unsigned int c )
{
    return (_MBHMASK (c) ? _ismbclegal (c) : (isprint (c) || _ismbbkana (c)));
}