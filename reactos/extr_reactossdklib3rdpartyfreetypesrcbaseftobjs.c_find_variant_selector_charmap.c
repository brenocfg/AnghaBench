#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ platform_id; scalar_t__ encoding_id; } ;
struct TYPE_7__ {int num_charmaps; TYPE_2__** charmaps; } ;
typedef  TYPE_1__* FT_Face ;
typedef  TYPE_2__* FT_CharMap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ASSERT (TYPE_1__*) ; 
 int FT_Get_CMap_Format (TYPE_2__*) ; 
 scalar_t__ TT_APPLE_ID_VARIANT_SELECTOR ; 
 scalar_t__ TT_PLATFORM_APPLE_UNICODE ; 

__attribute__((used)) static FT_CharMap
  find_variant_selector_charmap( FT_Face  face )
  {
    FT_CharMap*  first;
    FT_CharMap*  end;
    FT_CharMap*  cur;


    /* caller should have already checked that `face' is valid */
    FT_ASSERT( face );

    first = face->charmaps;

    if ( !first )
      return NULL;

    end = first + face->num_charmaps;  /* points after the last one */

    for ( cur = first; cur < end; cur++ )
    {
      if ( cur[0]->platform_id == TT_PLATFORM_APPLE_UNICODE    &&
           cur[0]->encoding_id == TT_APPLE_ID_VARIANT_SELECTOR &&
           FT_Get_CMap_Format( cur[0] ) == 14                  )
        return cur[0];
    }

    return NULL;
  }