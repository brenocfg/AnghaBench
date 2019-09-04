#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* globals; } ;
struct TYPE_4__ {int /*<<< orphan*/  face; } ;
typedef  scalar_t__ FT_ULong ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  TYPE_2__* AF_StyleMetrics ;

/* Variables and functions */
 scalar_t__ FT_Get_Char_Index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GET_UTF8_CHAR (scalar_t__,char const*) ; 

const char*
  af_shaper_get_cluster( const char*      p,
                         AF_StyleMetrics  metrics,
                         void*            buf_,
                         unsigned int*    count )
  {
    FT_Face    face      = metrics->globals->face;
    FT_ULong   ch, dummy = 0;
    FT_ULong*  buf       = (FT_ULong*)buf_;


    while ( *p == ' ' )
      p++;

    GET_UTF8_CHAR( ch, p );

    /* since we don't have an engine to handle clusters, */
    /* we scan the characters but return zero            */
    while ( !( *p == ' ' || *p == '\0' ) )
      GET_UTF8_CHAR( dummy, p );

    if ( dummy )
    {
      *buf   = 0;
      *count = 0;
    }
    else
    {
      *buf   = FT_Get_Char_Index( face, ch );
      *count = 1;
    }

    return p;
  }