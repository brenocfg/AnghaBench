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
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  scalar_t__ FT_UShort ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_INVALID_OFFSET ; 
 scalar_t__ GXV_PROP_ATTACHING_TO_RIGHT ; 
 scalar_t__ GXV_PROP_COMPLEMENTARY_BRACKET_OFFSET ; 
 int GXV_PROP_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ GXV_PROP_DIRECTIONALITY_CLASS ; 
 scalar_t__ GXV_PROP_FLOATER ; 
 scalar_t__ GXV_PROP_RESERVED ; 
 scalar_t__ GXV_PROP_USE_COMPLEMENTARY_BRACKET ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_glyphid_validate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_prop_zero_advance_validate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static void
  gxv_prop_property_validate( FT_UShort      property,
                              FT_UShort      glyph,
                              GXV_Validator  gxvalid )
  {
    if ( glyph != 0 && ( property & GXV_PROP_FLOATER ) )
      gxv_prop_zero_advance_validate( glyph, gxvalid );

    if ( property & GXV_PROP_USE_COMPLEMENTARY_BRACKET )
    {
      FT_UShort  offset;
      char       complement;


      offset = (FT_UShort)( property & GXV_PROP_COMPLEMENTARY_BRACKET_OFFSET );
      if ( offset == 0 )
      {
        GXV_TRACE(( "  found zero offset to property\n" ));
        FT_INVALID_OFFSET;
      }

      complement = (char)( offset >> 8 );
      if ( complement & 0x08 )
      {
        /* Top bit is set: negative */

        /* Calculate the absolute offset */
        complement = (char)( ( complement & 0x07 ) + 1 );

        /* The gid for complement must be greater than 0 */
        if ( glyph <= complement )
        {
          GXV_TRACE(( "  found non-positive glyph complement\n" ));
          FT_INVALID_DATA;
        }
      }
      else
      {
        /* The gid for complement must be the face. */
        gxv_glyphid_validate( (FT_UShort)( glyph + complement ), gxvalid );
      }
    }
    else
    {
      if ( property & GXV_PROP_COMPLEMENTARY_BRACKET_OFFSET )
        GXV_TRACE(( "glyph %d cannot have complementary bracketing\n",
                    glyph ));
    }

    /* this is introduced in version 2.0 */
    if ( property & GXV_PROP_ATTACHING_TO_RIGHT )
    {
      if ( GXV_PROP_DATA( version ) == 0x00010000UL )
      {
        GXV_TRACE(( "  found older version (1.0) in new version table\n" ));
        FT_INVALID_DATA;
      }
    }

    if ( property & GXV_PROP_RESERVED )
    {
      GXV_TRACE(( "  found non-zero bits in reserved bits\n" ));
      FT_INVALID_DATA;
    }

    if ( ( property & GXV_PROP_DIRECTIONALITY_CLASS ) > 11 )
    {
      /* TODO: Too restricted. Use the validation level. */
      if ( GXV_PROP_DATA( version ) == 0x00010000UL ||
           GXV_PROP_DATA( version ) == 0x00020000UL )
      {
        GXV_TRACE(( "  found too old version in directionality class\n" ));
        FT_INVALID_DATA;
      }
    }
  }