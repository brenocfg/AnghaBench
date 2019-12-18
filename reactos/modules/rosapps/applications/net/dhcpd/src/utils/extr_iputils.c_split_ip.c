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
typedef  int u8b ;

/* Variables and functions */

int split_ip( char *text, u8b *dest, int place )
{
  int dotcount;

  /* Don't touch this, unless you like pointer aritmethic */

  *dest = 0;

  if( !text )
    return -1;

  for( dotcount = 0; (dotcount < place) && ( text ); text++ )
      if( *text == '.' )
	dotcount++;

  if( !text )
    return -2;

  while(( *text != '.' ) && ( *text != '\0' ))
    {
      *dest *= 10;
      *dest += (u8b)(*text-48);
      /* 48 is not a hack, is just the code of 0 */
      text++;
    }

  return 0;
}