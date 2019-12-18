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
 scalar_t__ PICE_isdigit (int) ; 

int PICE_isxdigit( int c )
{
	return (PICE_isdigit(c) || ((c>=0x41) && (c<=0x46)) || ((c>=0x61) && (c<=0x66)));
}