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
 int /*<<< orphan*/  sscanf (char const*,char const*,int*) ; 

long
my_atoi ( const char* a )
{
	int i = 0;
	const char* fmt = "%x";

	if ( *a == '0' )
	{
		switch ( *++a )
		{
		case 'x':
			fmt = "%x";
			++a;
			break;
		case 'd':
			fmt = "%d";
			++a;
			break;
		default:
			fmt = "%o";
			break;
		}
	}
	sscanf ( a, fmt, &i );
	return i;
}