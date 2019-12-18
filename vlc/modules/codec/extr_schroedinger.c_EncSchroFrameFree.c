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
struct enc_picture_free_t {int /*<<< orphan*/  p_pic; } ;
typedef  int /*<<< orphan*/  SchroFrame ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct enc_picture_free_t*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EncSchroFrameFree( SchroFrame *frame, void *priv )
{
    struct enc_picture_free_t *p_free = priv;

    if( !p_free )
        return;

    picture_Release( p_free->p_pic );
    free( p_free );
    (void)frame;
}