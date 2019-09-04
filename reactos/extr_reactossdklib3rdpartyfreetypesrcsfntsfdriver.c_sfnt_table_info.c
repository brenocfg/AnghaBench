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
struct TYPE_5__ {size_t num_tables; TYPE_1__* dir_tables; } ;
struct TYPE_4__ {size_t Tag; size_t Offset; size_t Length; } ;
typedef  TYPE_2__* TT_Face ;
typedef  size_t FT_ULong ;
typedef  size_t FT_UInt ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_Argument ; 
 int /*<<< orphan*/  Table_Missing ; 

__attribute__((used)) static FT_Error
  sfnt_table_info( TT_Face    face,
                   FT_UInt    idx,
                   FT_ULong  *tag,
                   FT_ULong  *offset,
                   FT_ULong  *length )
  {
    if ( !offset || !length )
      return FT_THROW( Invalid_Argument );

    if ( !tag )
      *length = face->num_tables;
    else
    {
      if ( idx >= face->num_tables )
        return FT_THROW( Table_Missing );

      *tag    = face->dir_tables[idx].Tag;
      *offset = face->dir_tables[idx].Offset;
      *length = face->dir_tables[idx].Length;
    }

    return FT_Err_Ok;
  }