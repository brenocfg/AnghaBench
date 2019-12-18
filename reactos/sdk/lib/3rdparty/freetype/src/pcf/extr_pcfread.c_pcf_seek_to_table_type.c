#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pos; } ;
struct TYPE_5__ {size_t type; scalar_t__ offset; size_t size; size_t format; } ;
typedef  TYPE_1__* PCF_Table ;
typedef  size_t FT_ULong ;
typedef  TYPE_2__* FT_Stream ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ FT_STREAM_SKIP (scalar_t__) ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_File_Format ; 
 int /*<<< orphan*/  Invalid_Stream_Skip ; 

__attribute__((used)) static FT_Error
  pcf_seek_to_table_type( FT_Stream  stream,
                          PCF_Table  tables,
                          FT_ULong   ntables, /* same as PCF_Toc->count */
                          FT_ULong   type,
                          FT_ULong  *aformat,
                          FT_ULong  *asize )
  {
    FT_Error  error = FT_ERR( Invalid_File_Format );
    FT_ULong  i;


    for ( i = 0; i < ntables; i++ )
      if ( tables[i].type == type )
      {
        if ( stream->pos > tables[i].offset )
        {
          error = FT_THROW( Invalid_Stream_Skip );
          goto Fail;
        }

        if ( FT_STREAM_SKIP( tables[i].offset - stream->pos ) )
        {
          error = FT_THROW( Invalid_Stream_Skip );
          goto Fail;
        }

        *asize   = tables[i].size;
        *aformat = tables[i].format;

        return FT_Err_Ok;
      }

  Fail:
    *asize = 0;
    return error;
  }