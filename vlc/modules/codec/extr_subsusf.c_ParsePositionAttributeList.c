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

/* Variables and functions */
 int ATTRIBUTE_ALIGNMENT ; 
 int ATTRIBUTE_X ; 
 int ATTRIBUTE_X_PERCENT ; 
 int ATTRIBUTE_Y ; 
 int ATTRIBUTE_Y_PERCENT ; 
 char* GrabAttributeValue (char*,char*) ; 
 int SUBPICTURE_ALIGN_BOTTOM ; 
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_RIGHT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static int ParsePositionAttributeList( char *psz_subtitle, int *i_align,
                                       int *i_x, int *i_y )
{
    int   i_mask = 0;

    char *psz_align    = GrabAttributeValue( "alignment", psz_subtitle );
    char *psz_margin_x = GrabAttributeValue( "horizontal-margin", psz_subtitle );
    char *psz_margin_y = GrabAttributeValue( "vertical-margin", psz_subtitle );
    /* -- UNSUPPORTED
    char *psz_relative = GrabAttributeValue( "relative-to", psz_subtitle );
    char *psz_rotate_x = GrabAttributeValue( "rotate-x", psz_subtitle );
    char *psz_rotate_y = GrabAttributeValue( "rotate-y", psz_subtitle );
    char *psz_rotate_z = GrabAttributeValue( "rotate-z", psz_subtitle );
    */

    *i_align = SUBPICTURE_ALIGN_BOTTOM;
    *i_x = 0;
    *i_y = 0;

    if( psz_align )
    {
        if( !strcasecmp( "TopLeft", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_TOP | SUBPICTURE_ALIGN_LEFT;
        else if( !strcasecmp( "TopCenter", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_TOP;
        else if( !strcasecmp( "TopRight", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_TOP | SUBPICTURE_ALIGN_RIGHT;
        else if( !strcasecmp( "MiddleLeft", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_LEFT;
        else if( !strcasecmp( "MiddleCenter", psz_align ) )
            *i_align = 0;
        else if( !strcasecmp( "MiddleRight", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_RIGHT;
        else if( !strcasecmp( "BottomLeft", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_BOTTOM | SUBPICTURE_ALIGN_LEFT;
        else if( !strcasecmp( "BottomCenter", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_BOTTOM;
        else if( !strcasecmp( "BottomRight", psz_align ) )
            *i_align = SUBPICTURE_ALIGN_BOTTOM | SUBPICTURE_ALIGN_RIGHT;

        i_mask |= ATTRIBUTE_ALIGNMENT;
        free( psz_align );
    }
    if( psz_margin_x )
    {
        *i_x = atoi( psz_margin_x );
        if( strchr( psz_margin_x, '%' ) )
            i_mask |= ATTRIBUTE_X_PERCENT;
        else
            i_mask |= ATTRIBUTE_X;

        free( psz_margin_x );
    }
    if( psz_margin_y )
    {
        *i_y = atoi( psz_margin_y );
        if( strchr( psz_margin_y, '%' ) )
            i_mask |= ATTRIBUTE_Y_PERCENT;
        else
            i_mask |= ATTRIBUTE_Y;

        free( psz_margin_y );
    }
    return i_mask;
}