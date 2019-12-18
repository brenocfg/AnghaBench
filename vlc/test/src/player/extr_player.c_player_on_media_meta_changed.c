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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct ctx {int dummy; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_PUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_media_meta_changed ; 

__attribute__((used)) static void
player_on_media_meta_changed(vlc_player_t *player, input_item_t *media,
                             void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    input_item_Hold(media);
    VEC_PUSH(on_media_meta_changed, media);
}