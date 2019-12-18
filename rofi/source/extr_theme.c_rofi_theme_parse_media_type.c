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
typedef  int /*<<< orphan*/  ThemeMediaType ;

/* Variables and functions */
 int /*<<< orphan*/  THEME_MEDIA_TYPE_INVALID ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MAX_ASPECT_RATIO ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MAX_HEIGHT ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MAX_WIDTH ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MIN_ASPECT_RATIO ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MIN_HEIGHT ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MIN_WIDTH ; 
 int /*<<< orphan*/  THEME_MEDIA_TYPE_MON_ID ; 
 scalar_t__ g_strcmp0 (char const*,char*) ; 

ThemeMediaType rofi_theme_parse_media_type ( const char *type )
{
    if ( g_strcmp0( type, "monitor-id" ) == 0 ) {
        return THEME_MEDIA_TYPE_MON_ID;
    } else if ( g_strcmp0 ( type, "min-width")  == 0 ) {
        return THEME_MEDIA_TYPE_MIN_WIDTH;
    } else if ( g_strcmp0 ( type, "min-height")  == 0 ) {
        return THEME_MEDIA_TYPE_MIN_HEIGHT;
    } else if ( g_strcmp0 ( type, "max-width")  == 0 ) {
        return THEME_MEDIA_TYPE_MAX_WIDTH;
    } else if ( g_strcmp0 ( type, "max-height")  == 0 ) {
        return THEME_MEDIA_TYPE_MAX_HEIGHT;
    } else if ( g_strcmp0 ( type, "min-aspect-ratio") == 0 ) {
        return THEME_MEDIA_TYPE_MIN_ASPECT_RATIO;
    } else if ( g_strcmp0 ( type, "max-aspect-ratio") == 0 ) {
        return THEME_MEDIA_TYPE_MAX_ASPECT_RATIO;
    }
    return THEME_MEDIA_TYPE_INVALID;
}