#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_10__ {int /*<<< orphan*/  refs; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_9__ {int /*<<< orphan*/ * opaque; } ;
struct TYPE_11__ {TYPE_1__ gc; TYPE_2__ picture; } ;
typedef  TYPE_3__ picture_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ picture_Setup (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_priv_t *picture_NewPrivate(const video_format_t *restrict p_fmt,
                                          size_t extra)
{
    /* */
    picture_priv_t *priv = malloc(sizeof (*priv) + extra);
    if( unlikely(priv == NULL) )
        return NULL;

    picture_t *p_picture = &priv->picture;

    memset( p_picture, 0, sizeof( *p_picture ) );

    p_picture->format = *p_fmt;
    /* Make sure the real dimensions are a multiple of 16 */
    if( picture_Setup( p_picture, p_fmt ) )
    {
        free( p_picture );
        return NULL;
    }

    atomic_init(&p_picture->refs, 1);
    priv->gc.opaque = NULL;

    return priv;
}