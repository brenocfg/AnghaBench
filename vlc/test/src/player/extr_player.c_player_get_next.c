#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ ** data; } ;
struct ctx {int /*<<< orphan*/  played_medias; TYPE_1__ next_medias; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct ctx* get_ctx (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 int vlc_vector_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_remove (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static input_item_t *
player_get_next(vlc_player_t *player, void *data)
{
    struct ctx *ctx = get_ctx(player, data);
    input_item_t *next_media;
    if (ctx->next_medias.size > 0)
    {
        next_media = ctx->next_medias.data[0];
        vlc_vector_remove(&ctx->next_medias, 0);

        input_item_Hold(next_media);
        bool success = vlc_vector_push(&ctx->played_medias, next_media);
        assert(success);
    }
    else
        next_media = NULL;
    return next_media;
}