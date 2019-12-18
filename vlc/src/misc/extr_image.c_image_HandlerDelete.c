#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  outfifo; scalar_t__ p_converter; scalar_t__ p_enc; int /*<<< orphan*/  p_dec; } ;
typedef  TYPE_1__ image_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteConverter (scalar_t__) ; 
 int /*<<< orphan*/  DeleteEncoder (scalar_t__) ; 
 int /*<<< orphan*/  decoder_Destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_fifo_Delete (int /*<<< orphan*/ ) ; 

void image_HandlerDelete( image_handler_t *p_image )
{
    if( !p_image ) return;

    decoder_Destroy( p_image->p_dec );
    if( p_image->p_enc ) DeleteEncoder( p_image->p_enc );
    if( p_image->p_converter ) DeleteConverter( p_image->p_converter );

    picture_fifo_Delete( p_image->outfifo );

    free( p_image );
    p_image = NULL;
}