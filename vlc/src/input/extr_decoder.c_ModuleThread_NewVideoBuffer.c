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
struct decoder_owner {int /*<<< orphan*/  out_pool; int /*<<< orphan*/  p_vout; } ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_Wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t *ModuleThread_NewVideoBuffer( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    assert( p_owner->p_vout );

    picture_t *pic = picture_pool_Wait( p_owner->out_pool );
    if (pic)
        picture_Reset( pic );
    return pic;
}