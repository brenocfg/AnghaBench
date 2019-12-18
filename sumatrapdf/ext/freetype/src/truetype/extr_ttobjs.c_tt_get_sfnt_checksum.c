#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  stream; } ;
struct TYPE_8__ {TYPE_2__* dir_tables; TYPE_1__ root; scalar_t__ (* goto_table ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Tag; scalar_t__ CheckSum; } ;
typedef  TYPE_3__* TT_Face ;
typedef  size_t FT_UShort ;
typedef  scalar_t__ FT_ULong ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tt_synth_sfnt_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_ULong
  tt_get_sfnt_checksum( TT_Face    face,
                        FT_UShort  i )
  {
#if 0 /* if we believe the written value, use following part. */
    if ( face->dir_tables[i].CheckSum )
      return face->dir_tables[i].CheckSum;
#endif

    if ( !face->goto_table )
      return 0;

    if ( face->goto_table( face,
                           face->dir_tables[i].Tag,
                           face->root.stream,
                           NULL ) )
      return 0;

    return (FT_ULong)tt_synth_sfnt_checksum( face->root.stream,
                                             face->dir_tables[i].Length );
  }