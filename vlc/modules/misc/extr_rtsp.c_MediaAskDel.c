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
typedef  int /*<<< orphan*/  vod_t ;
typedef  int /*<<< orphan*/  vod_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommandPush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTSP_CMD_TYPE_DEL ; 

__attribute__((used)) static void MediaAskDel ( vod_t *p_vod, vod_media_t *p_media )
{
    CommandPush( p_vod, RTSP_CMD_TYPE_DEL, p_media, NULL, 0, 0.0, NULL );
}