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
typedef  int FT_UInt ;
typedef  scalar_t__ FT_String ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int FT_Byte ;

/* Variables and functions */
 scalar_t__ FT_ALLOC (scalar_t__*,int) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FREE (scalar_t__*) ; 
 int /*<<< orphan*/  FT_MEM_COPY (scalar_t__*,int*,int) ; 

__attribute__((used)) static FT_Error
  pfr_aux_name_load( FT_Byte*     p,
                     FT_UInt      len,
                     FT_Memory    memory,
                     FT_String*  *astring )
  {
    FT_Error    error  = FT_Err_Ok;
    FT_String*  result = NULL;
    FT_UInt     n, ok;


    if ( *astring )
      FT_FREE( *astring );

    if ( len > 0 && p[len - 1] == 0 )
      len--;

    /* check that each character is ASCII  */
    /* for making sure not to load garbage */
    ok = ( len > 0 );
    for ( n = 0; n < len; n++ )
      if ( p[n] < 32 || p[n] > 127 )
      {
        ok = 0;
        break;
      }

    if ( ok )
    {
      if ( FT_ALLOC( result, len + 1 ) )
        goto Exit;

      FT_MEM_COPY( result, p, len );
      result[len] = 0;
    }

  Exit:
    *astring = result;
    return error;
  }