#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* glyph; } ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_9__ {TYPE_1__ advance; } ;
struct TYPE_8__ {TYPE_4__* face; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  scalar_t__ FT_Pos ;
typedef  TYPE_3__* FT_GlyphSlot ;
typedef  TYPE_4__* FT_Face ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_INVALID_GLYPH_ID ; 
 int /*<<< orphan*/  FT_LOAD_IGNORE_TRANSFORM ; 
 scalar_t__ FT_Load_Glyph (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_prop_zero_advance_validate( FT_UShort      gid,
                                  GXV_Validator  gxvalid )
  {
    FT_Face       face;
    FT_Error      error;
    FT_GlyphSlot  glyph;


    GXV_NAME_ENTER( "zero advance" );

    face = gxvalid->face;

    error = FT_Load_Glyph( face,
                           gid,
                           FT_LOAD_IGNORE_TRANSFORM );
    if ( error )
      FT_INVALID_GLYPH_ID;

    glyph = face->glyph;

    if ( glyph->advance.x != (FT_Pos)0 ||
         glyph->advance.y != (FT_Pos)0 )
    {
      GXV_TRACE(( "  found non-zero advance in zero-advance glyph\n" ));
      FT_INVALID_DATA;
    }

    GXV_EXIT;
  }