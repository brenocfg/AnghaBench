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
 int _MBC_ILLEGAL ; 
 int _MBC_LEAD ; 
 int _MBC_SINGLE ; 
 int _MBC_TRAIL ; 

int _mbbtype(unsigned char c , int type)
{
	if ( type == 1 ) {
		if ((c >= 0x40 && c <= 0x7e ) || (c >= 0x80 && c <= 0xfc ) )
		{
			return _MBC_TRAIL;
		}
		else if (( c >= 0x20 && c <= 0x7E ) || ( c >= 0xA1 && c <= 0xDF ) ||
			 ( c >= 0x81 && c <= 0x9F ) || ( c >= 0xE0 && c <= 0xFC ) )
			 return _MBC_ILLEGAL;
		else
			return 0;
	} else  {
		if (( c >= 0x20 && c <= 0x7E ) || ( c >= 0xA1  && c <= 0xDF )) {
			return _MBC_SINGLE;
		}
		else if ( (c >= 0x81 && c <= 0x9F ) || ( c >= 0xE0 && c <= 0xFC) )
			return _MBC_LEAD;
		else if (( c >= 0x20 && c <= 0x7E ) || ( c >= 0xA1 && c <= 0xDF ) ||
			 ( c >= 0x81 && c <= 0x9F ) || ( c >= 0xE0 && c <= 0xFC ) )
			 return _MBC_ILLEGAL;
		else
			return 0;
	}
	return 0;
}