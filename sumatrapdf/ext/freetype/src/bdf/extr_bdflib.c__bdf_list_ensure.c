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
struct TYPE_3__ {unsigned long size; int /*<<< orphan*/  field; int /*<<< orphan*/  memory; } ;
typedef  TYPE_1__ _bdf_list_t ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int FT_INT_MAX ; 
 scalar_t__ FT_RENEW_ARRAY (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Out_Of_Memory ; 

__attribute__((used)) static FT_Error
  _bdf_list_ensure( _bdf_list_t*   list,
                    unsigned long  num_items ) /* same as _bdf_list_t.used */
  {
    FT_Error  error = FT_Err_Ok;


    if ( num_items > list->size )
    {
      unsigned long  oldsize = list->size; /* same as _bdf_list_t.size */
      unsigned long  newsize = oldsize + ( oldsize >> 1 ) + 5;
      unsigned long  bigsize = (unsigned long)( FT_INT_MAX / sizeof ( char* ) );
      FT_Memory      memory  = list->memory;


      if ( oldsize == bigsize )
      {
        error = FT_THROW( Out_Of_Memory );
        goto Exit;
      }
      else if ( newsize < oldsize || newsize > bigsize )
        newsize = bigsize;

      if ( FT_RENEW_ARRAY( list->field, oldsize, newsize ) )
        goto Exit;

      list->size = newsize;
    }

  Exit:
    return error;
  }