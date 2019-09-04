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
typedef  char u8b ;

/* Variables and functions */
 scalar_t__ strlen (char*) ; 

int str2mac( u8b from[17], u8b to[16] )
{
  int i, j, length;
  u8b buffer;
  u8b dif;

  length = (int)strlen( from );

  for( i = 0, j = 0; i < length; )
    {
      buffer = 0;
      while( (from[i] != ':' ) && (from[i]!= '\0' ))
	{
	  buffer = buffer << 4;
	  (from[i]>57)?(dif=55):(dif=48);
	  buffer += (from[i] - dif);
	  i++;
	}
      to[j++] = buffer;
      i++;
    }
  return 0;
}