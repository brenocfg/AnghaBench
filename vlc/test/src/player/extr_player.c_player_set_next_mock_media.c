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
struct media_params {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; } ;
struct ctx {int /*<<< orphan*/  next_medias; TYPE_1__ played_medias; int /*<<< orphan*/  player; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * create_mock_media (char const*,struct media_params const*) ; 
 int /*<<< orphan*/  player_set_current_mock_media (struct ctx*,char const*,struct media_params const*,int) ; 
 int /*<<< orphan*/ * vlc_player_GetCurrentMedia (int /*<<< orphan*/ ) ; 
 int vlc_vector_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
player_set_next_mock_media(struct ctx *ctx, const char *name,
                           const struct media_params *params)
{
    if (vlc_player_GetCurrentMedia(ctx->player) == NULL)
    {
        assert(ctx->played_medias.size == 0);
        player_set_current_mock_media(ctx, name, params, false);
    }
    else
    {
        input_item_t *media = create_mock_media(name, params);
        assert(media);

        assert(ctx->played_medias.size > 0);
        bool success = vlc_vector_push(&ctx->next_medias, media);
        assert(success);
    }
}