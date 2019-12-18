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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  outfifo; int /*<<< orphan*/  pf_convert; int /*<<< orphan*/  pf_write_url; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_read_url; int /*<<< orphan*/  pf_read; int /*<<< orphan*/ * p_parent; } ;
typedef  TYPE_1__ image_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  ImageConvert ; 
 int /*<<< orphan*/  ImageRead ; 
 int /*<<< orphan*/  ImageReadUrl ; 
 int /*<<< orphan*/  ImageWrite ; 
 int /*<<< orphan*/  ImageWriteUrl ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  picture_fifo_New () ; 

image_handler_t *image_HandlerCreate( vlc_object_t *p_this )
{
    image_handler_t *p_image = calloc( 1, sizeof(image_handler_t) );
    if( !p_image )
        return NULL;

    p_image->p_parent = p_this;

    p_image->pf_read = ImageRead;
    p_image->pf_read_url = ImageReadUrl;
    p_image->pf_write = ImageWrite;
    p_image->pf_write_url = ImageWriteUrl;
    p_image->pf_convert = ImageConvert;

    p_image->outfifo = picture_fifo_New();

    return p_image;
}