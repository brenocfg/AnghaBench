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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct bhyvegc_image {int width; int height; void* data; } ;
struct bhyvegc {int raw; struct bhyvegc_image* gc_image; } ;

/* Variables and functions */
 void* calloc (int,int) ; 

struct bhyvegc *
bhyvegc_init(uint16_t width, uint16_t height, void *fbaddr)
{
	struct bhyvegc *gc;
	struct bhyvegc_image *gc_image;

	gc = calloc(1, sizeof (struct bhyvegc));

	gc_image = calloc(1, sizeof(struct bhyvegc_image));
	gc_image->width = width;
	gc_image->height = height;
	if (fbaddr) {
		gc_image->data = fbaddr;
		gc->raw = 1;
	} else {
		gc_image->data = calloc(width * height, sizeof (uint32_t));
		gc->raw = 0;
	}

	gc->gc_image = gc_image;

	return (gc);
}