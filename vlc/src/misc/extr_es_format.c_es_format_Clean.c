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
struct TYPE_6__ {TYPE_3__* psz_encoding; } ;
struct TYPE_7__ {scalar_t__ i_extra; scalar_t__ i_cat; unsigned int i_extra_languages; TYPE_3__* p_extra_languages; TYPE_1__ subs; int /*<<< orphan*/  video; TYPE_3__* p_extra; TYPE_3__* psz_description; TYPE_3__* psz_language; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_8__ {struct TYPE_8__* psz_description; struct TYPE_8__* psz_language; } ;

/* Variables and functions */
 scalar_t__ SPU_ES ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 

void es_format_Clean(es_format_t *fmt)
{
    free(fmt->psz_language);
    free(fmt->psz_description);
    assert(fmt->i_extra == 0 || fmt->p_extra != NULL);
    free(fmt->p_extra);

    if (fmt->i_cat == VIDEO_ES)
        video_format_Clean( &fmt->video );
    if (fmt->i_cat == SPU_ES)
        free(fmt->subs.psz_encoding);

    for (unsigned i = 0; i < fmt->i_extra_languages; i++)
    {
        free(fmt->p_extra_languages[i].psz_language);
        free(fmt->p_extra_languages[i].psz_description);
    }
    free(fmt->p_extra_languages);

    /* es_format_Clean can be called multiple times */
    es_format_Init(fmt, UNKNOWN_ES, 0);
}