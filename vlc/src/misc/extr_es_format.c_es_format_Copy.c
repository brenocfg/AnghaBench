#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * psz_encoding; } ;
struct TYPE_7__ {scalar_t__ i_extra; scalar_t__ i_cat; scalar_t__ i_extra_languages; TYPE_5__* p_extra_languages; TYPE_1__ subs; int /*<<< orphan*/  video; int /*<<< orphan*/ * p_extra; int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_language; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_8__ {int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_language; } ;

/* Variables and functions */
 scalar_t__ SPU_ES ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* calloc (scalar_t__,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 void* strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int es_format_Copy(es_format_t *restrict dst, const es_format_t *src)
{
    int ret = VLC_SUCCESS;

    *dst = *src;

    if (src->psz_language != NULL)
    {
        dst->psz_language = strdup(src->psz_language);
        if (unlikely(dst->psz_language == NULL))
            ret = VLC_ENOMEM;
    }
    if (src->psz_description != NULL)
    {
        dst->psz_description = strdup(src->psz_description);
        if (unlikely(dst->psz_description == NULL))
            ret = VLC_ENOMEM;
    }

    if (src->i_extra > 0)
    {
        assert(src->p_extra != NULL);
        dst->p_extra = malloc( src->i_extra );

        if( likely(dst->p_extra != NULL) )
            memcpy(dst->p_extra, src->p_extra, src->i_extra);
        else
        {
            dst->i_extra = 0;
            ret = VLC_ENOMEM;
        }
    }
    else
        dst->p_extra = NULL;

    if (src->i_cat == VIDEO_ES)
        ret = video_format_Copy( &dst->video, &src->video );

    if (src->i_cat == SPU_ES)
    {
        if (src->subs.psz_encoding != NULL)
        {
            dst->subs.psz_encoding = strdup(src->subs.psz_encoding);
            if (unlikely(dst->subs.psz_encoding == NULL))
                ret = VLC_ENOMEM;
        }
    }

    if (src->i_extra_languages > 0)
    {
        assert(src->p_extra_languages != NULL);
        dst->p_extra_languages = calloc(dst->i_extra_languages,
                                        sizeof (*dst->p_extra_languages));
        if (likely(dst->p_extra_languages != NULL))
        {
            for (unsigned i = 0; i < dst->i_extra_languages; i++)
            {
                if (src->p_extra_languages[i].psz_language != NULL)
                    dst->p_extra_languages[i].psz_language = strdup(src->p_extra_languages[i].psz_language);
                if (src->p_extra_languages[i].psz_description != NULL)
                    dst->p_extra_languages[i].psz_description = strdup(src->p_extra_languages[i].psz_description);
            }
            dst->i_extra_languages = src->i_extra_languages;
        }
        else
        {
            dst->i_extra_languages = 0;
            ret = VLC_ENOMEM;
        }
    }
    return ret;
}