#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_window_t ;
struct TYPE_5__ {void* sys; int /*<<< orphan*/ * cbs; } ;
typedef  TYPE_1__ vout_window_owner_t ;
struct TYPE_6__ {int is_decorated; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ vout_window_cfg_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_vidsplit_window_cbs ; 
 int /*<<< orphan*/  vout_display_GetDefaultDisplaySize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vout_window_Delete (int /*<<< orphan*/ *) ; 
 scalar_t__ vout_window_Enable (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * vout_window_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static vout_window_t *video_splitter_CreateWindow(vlc_object_t *obj,
    const vout_display_cfg_t *restrict vdcfg,
    const video_format_t *restrict source, void *sys)
{
    vout_window_cfg_t cfg = {
        .is_decorated = true,
    };
    vout_window_owner_t owner = {
        .cbs = &vlc_vidsplit_window_cbs,
        .sys = sys,
    };

    vout_display_GetDefaultDisplaySize(&cfg.width, &cfg.height, source,
                                       vdcfg);

    vout_window_t *window = vout_window_New(obj, NULL, &owner);
    if (window != NULL) {
        if (vout_window_Enable(window, &cfg)) {
            vout_window_Delete(window);
            window = NULL;
        }
    }
    return window;
}