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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  AboveCallback ; 
 int /*<<< orphan*/  AspectCallback ; 
 int /*<<< orphan*/  AutoScaleCallback ; 
 int /*<<< orphan*/  CropBorderCallback ; 
 int /*<<< orphan*/  CropCallback ; 
 int /*<<< orphan*/  FullscreenCallback ; 
 int /*<<< orphan*/  SecondarySubMarginCallback ; 
 int /*<<< orphan*/  SnapshotCallback ; 
 int /*<<< orphan*/  SubFilterCallback ; 
 int /*<<< orphan*/  SubMarginCallback ; 
 int /*<<< orphan*/  SubSourceCallback ; 
 int /*<<< orphan*/  VideoFilterCallback ; 
 int /*<<< orphan*/  ViewpointCallback ; 
 int /*<<< orphan*/  WallPaperCallback ; 
 int /*<<< orphan*/  ZoomCallback ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vout_IntfDeinit(vlc_object_t *obj)
{
    var_DelCallback(obj, "viewpoint", ViewpointCallback, NULL);
    var_DelCallback(obj, "sub-margin", SubMarginCallback, NULL);
    var_DelCallback(obj, "secondary-sub-margin", SecondarySubMarginCallback, NULL);
    var_DelCallback(obj, "sub-filter", SubFilterCallback, NULL);
    var_DelCallback(obj, "sub-source", SubSourceCallback, NULL);
    var_DelCallback(obj, "video-filter", VideoFilterCallback, NULL);
    var_DelCallback(obj, "video-snapshot", SnapshotCallback, NULL);
    var_DelCallback(obj, "fullscreen", FullscreenCallback, NULL);
    var_DelCallback(obj, "video-wallpaper", WallPaperCallback, NULL);
    var_DelCallback(obj, "video-on-top", AboveCallback, NULL);
    var_DelCallback(obj, "aspect-ratio", AspectCallback, NULL);
    var_DelCallback(obj, "crop", CropCallback, NULL);
    var_DelCallback(obj, "crop-bottom", CropBorderCallback, NULL);
    var_DelCallback(obj, "crop-right", CropBorderCallback, NULL);
    var_DelCallback(obj, "crop-top", CropBorderCallback, NULL);
    var_DelCallback(obj, "crop-left", CropBorderCallback, NULL);
    var_DelCallback(obj, "zoom", ZoomCallback, NULL);
    var_DelCallback(obj, "autoscale", AutoScaleCallback, NULL);
}