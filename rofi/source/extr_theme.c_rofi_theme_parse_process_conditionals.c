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
struct TYPE_8__ {int w; int h; int monitor_id; } ;
typedef  TYPE_2__ workarea ;
struct TYPE_9__ {unsigned int num_widgets; int /*<<< orphan*/ * widgets; TYPE_1__* media; } ;
typedef  TYPE_3__ ThemeWidget ;
struct TYPE_10__ {unsigned int num_widgets; TYPE_3__** widgets; } ;
struct TYPE_7__ {int type; int value; } ;

/* Variables and functions */
#define  THEME_MEDIA_TYPE_MAX_ASPECT_RATIO 134 
#define  THEME_MEDIA_TYPE_MAX_HEIGHT 133 
#define  THEME_MEDIA_TYPE_MAX_WIDTH 132 
#define  THEME_MEDIA_TYPE_MIN_ASPECT_RATIO 131 
#define  THEME_MEDIA_TYPE_MIN_HEIGHT 130 
#define  THEME_MEDIA_TYPE_MIN_WIDTH 129 
#define  THEME_MEDIA_TYPE_MON_ID 128 
 int /*<<< orphan*/  monitor_active (TYPE_2__*) ; 
 TYPE_4__* rofi_theme ; 
 int /*<<< orphan*/  rofi_theme_parse_merge_widgets (TYPE_4__*,int /*<<< orphan*/ ) ; 

void  rofi_theme_parse_process_conditionals ( void )
{
    workarea mon;
    monitor_active ( &mon );
    if ( rofi_theme == NULL ) return;
    for ( unsigned int i = 0; i < rofi_theme->num_widgets; i++ ) {
            ThemeWidget *widget = rofi_theme->widgets[i];
            if ( widget->media != NULL ) {
                switch ( widget->media->type )
                {
                    case THEME_MEDIA_TYPE_MIN_WIDTH:
                        {
                            int w = widget->media->value;
                            if ( mon.w >= w ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    case THEME_MEDIA_TYPE_MAX_WIDTH:
                        {
                            int w = widget->media->value;
                            if ( mon.w < w ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    case THEME_MEDIA_TYPE_MIN_HEIGHT:
                        {
                            int h = widget->media->value;
                            if ( mon.h >= h ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    case THEME_MEDIA_TYPE_MAX_HEIGHT:
                        {
                            int h =  widget->media->value;
                            if ( mon.h < h ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    case THEME_MEDIA_TYPE_MON_ID:
                        {
                            if ( mon.monitor_id == widget->media->value ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    case THEME_MEDIA_TYPE_MIN_ASPECT_RATIO:
                        {
                            double r =  widget->media->value;
                            if ( (mon.w/(double)mon.h) >= r ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    case THEME_MEDIA_TYPE_MAX_ASPECT_RATIO:
                        {
                            double r =  widget->media->value;
                            if ( (mon.w/(double)mon.h) < r ){
                                for ( unsigned int x =0; x < widget->num_widgets; x++) {
                                    rofi_theme_parse_merge_widgets ( rofi_theme, widget->widgets[x] );
                                }
                            }
                            break;
                        }
                    default:
                        {
                            break;
                        }
                }
            }
    }
}