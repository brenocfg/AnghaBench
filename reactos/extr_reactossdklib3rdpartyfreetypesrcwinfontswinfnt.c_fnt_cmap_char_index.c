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

__attribute__((used)) static FT_UInt
  fnt_cmap_char_index( FNT_CMap   cmap,
                       FT_UInt32  char_code )
  {
    FT_UInt  gindex = 0;


    char_code -= cmap->first;
    if ( char_code < cmap->count )
      /* we artificially increase the glyph index; */
      /* FNT_Load_Glyph reverts to the right one   */
      gindex = (FT_UInt)( char_code + 1 );
    return gindex;
  }