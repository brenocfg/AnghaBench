#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ (* copy ) (TYPE_4__*) ;} ;
struct TYPE_5__ {TYPE_4__ context; } ;
typedef  TYPE_1__ vlc_vdp_video_field_t ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_4__*) ; 

__attribute__((used)) static inline vlc_vdp_video_field_t *vlc_vdp_video_copy(
    vlc_vdp_video_field_t *fold)
{
    return (vlc_vdp_video_field_t *)fold->context.copy(&fold->context);
}