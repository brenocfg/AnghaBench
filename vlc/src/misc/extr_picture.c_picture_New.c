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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/ * picture_NewFromFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

picture_t *picture_New( vlc_fourcc_t i_chroma, int i_width, int i_height, int i_sar_num, int i_sar_den )
{
    video_format_t fmt;

    video_format_Init( &fmt, 0 );
    video_format_Setup( &fmt, i_chroma, i_width, i_height,
                        i_width, i_height, i_sar_num, i_sar_den );

    return picture_NewFromFormat( &fmt );
}