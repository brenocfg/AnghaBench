#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ first; scalar_t__ count; } ;
typedef  scalar_t__ FT_UInt32 ;
typedef  scalar_t__ FT_UInt ;
typedef  TYPE_1__* FNT_CMap ;

/* Variables and functions */

__attribute__((used)) static FT_UInt32
  fnt_cmap_char_next( FNT_CMap    cmap,
                      FT_UInt32  *pchar_code )
  {
    FT_UInt    gindex = 0;
    FT_UInt32  result = 0;
    FT_UInt32  char_code = *pchar_code + 1;


    if ( char_code <= cmap->first )
    {
      result = cmap->first;
      gindex = 1;
    }
    else
    {
      char_code -= cmap->first;
      if ( char_code < cmap->count )
      {
        result = cmap->first + char_code;
        gindex = (FT_UInt)( char_code + 1 );
      }
    }

    *pchar_code = result;
    return gindex;
  }