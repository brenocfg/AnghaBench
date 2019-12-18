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
typedef  int /*<<< orphan*/  vout_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AboveCallback ; 
 int /*<<< orphan*/  AspectCallback ; 
 int /*<<< orphan*/  AutoScaleCallback ; 
 int /*<<< orphan*/  CropBorderCallback ; 
 int /*<<< orphan*/  CropCallback ; 
 int /*<<< orphan*/  FullscreenCallback ; 
 int /*<<< orphan*/  SnapshotCallback ; 
 int /*<<< orphan*/  SubFilterCallback ; 
 int /*<<< orphan*/  SubMarginCallback ; 
 int /*<<< orphan*/  SubSourceCallback ; 
 int /*<<< orphan*/  VideoFilterCallback ; 
 int /*<<< orphan*/  ViewpointCallback ; 
 int /*<<< orphan*/  WallPaperCallback ; 
 int /*<<< orphan*/  ZoomCallback ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vout_IntfInit( vout_thread_t *p_vout )
{
    var_AddCallback( p_vout, "autoscale", AutoScaleCallback, NULL );
    var_AddCallback( p_vout, "zoom", ZoomCallback, NULL );
    var_AddCallback( p_vout, "crop-left", CropBorderCallback, NULL );
    var_AddCallback( p_vout, "crop-top", CropBorderCallback, NULL );
    var_AddCallback( p_vout, "crop-right", CropBorderCallback, NULL );
    var_AddCallback( p_vout, "crop-bottom", CropBorderCallback, NULL );
    var_AddCallback( p_vout, "crop", CropCallback, NULL );
    var_AddCallback( p_vout, "aspect-ratio", AspectCallback, NULL );
    var_AddCallback( p_vout, "video-on-top", AboveCallback, NULL );
    var_AddCallback( p_vout, "video-wallpaper", WallPaperCallback, NULL );
    var_AddCallback( p_vout, "fullscreen", FullscreenCallback, NULL );
    var_AddCallback( p_vout, "video-snapshot", SnapshotCallback, NULL );
    var_AddCallback( p_vout, "video-filter", VideoFilterCallback, NULL );
    var_AddCallback( p_vout, "sub-source", SubSourceCallback, NULL );
    var_AddCallback( p_vout, "sub-filter", SubFilterCallback, NULL );
    var_AddCallback( p_vout, "sub-margin", SubMarginCallback, NULL );
    var_AddCallback( p_vout, "viewpoint", ViewpointCallback, NULL );
}