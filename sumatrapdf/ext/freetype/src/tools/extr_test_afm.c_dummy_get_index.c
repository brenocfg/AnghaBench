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
typedef  scalar_t__ FT_Offset ;

/* Variables and functions */

int
  dummy_get_index( const char*  name,
                   FT_Offset    len,
                   void*        user_data )
  {
    if ( len )
      return name[0];
    else
      return 0;
  }