#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dictionary_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  previous_offsets; int /*<<< orphan*/  ml_dtable; int /*<<< orphan*/  of_dtable; int /*<<< orphan*/  ll_dtable; int /*<<< orphan*/  literals_dtable; int /*<<< orphan*/  dict_content_len; scalar_t__ dict_content; TYPE_1__ header; } ;
typedef  TYPE_2__ frame_context_t ;
struct TYPE_8__ {scalar_t__ dictionary_id; int /*<<< orphan*/  previous_offsets; int /*<<< orphan*/  ml_dtable; int /*<<< orphan*/  of_dtable; int /*<<< orphan*/  ll_dtable; int /*<<< orphan*/  literals_dtable; int /*<<< orphan*/  content_size; scalar_t__ content; } ;
typedef  TYPE_3__ dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  FSE_copy_dtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUF_copy_dtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void frame_context_apply_dict(frame_context_t *const ctx,
                                     const dictionary_t *const dict) {
    // If the content pointer is NULL then it must be an empty dict
    if (!dict || !dict->content)
        return;

    // If the requested dictionary_id is non-zero, the correct dictionary must
    // be present
    if (ctx->header.dictionary_id != 0 &&
        ctx->header.dictionary_id != dict->dictionary_id) {
        ERROR("Wrong dictionary provided");
    }

    // Copy the dict content to the context for references during sequence
    // execution
    ctx->dict_content = dict->content;
    ctx->dict_content_len = dict->content_size;

    // If it's a formatted dict copy the precomputed tables in so they can
    // be used in the table repeat modes
    if (dict->dictionary_id != 0) {
        // Deep copy the entropy tables so they can be freed independently of
        // the dictionary struct
        HUF_copy_dtable(&ctx->literals_dtable, &dict->literals_dtable);
        FSE_copy_dtable(&ctx->ll_dtable, &dict->ll_dtable);
        FSE_copy_dtable(&ctx->of_dtable, &dict->of_dtable);
        FSE_copy_dtable(&ctx->ml_dtable, &dict->ml_dtable);

        // Copy the repeated offsets
        memcpy(ctx->previous_offsets, dict->previous_offsets,
               sizeof(ctx->previous_offsets));
    }
}