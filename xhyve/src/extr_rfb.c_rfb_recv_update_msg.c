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
typedef  int /*<<< orphan*/  updt_msg ;
typedef  int /*<<< orphan*/  uint8_t ;
struct rfb_updt_msg {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
struct rfb_softc {scalar_t__ width; scalar_t__ height; scalar_t__ enc_resize_ok; } ;
struct bhyvegc_image {scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */
 struct bhyvegc_image* console_get_image () ; 
 int /*<<< orphan*/  console_refresh () ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  rfb_send_resize_update_msg (struct rfb_softc*,int) ; 
 int /*<<< orphan*/  rfb_send_screen (struct rfb_softc*,int,int) ; 
 int /*<<< orphan*/  stream_read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
rfb_recv_update_msg(struct rfb_softc *rc, int cfd, int discardonly)
{
	struct rfb_updt_msg updt_msg;
	struct bhyvegc_image *gc_image;

	(void)stream_read(cfd, ((uint8_t *)&updt_msg) + 1 , sizeof(updt_msg) - 1);

	console_refresh();
	gc_image = console_get_image();

	updt_msg.x = htons(updt_msg.x);
	updt_msg.y = htons(updt_msg.y);
	updt_msg.width = htons(updt_msg.width);
	updt_msg.height = htons(updt_msg.height);

	if (updt_msg.width != gc_image->width ||
	    updt_msg.height != gc_image->height) {
		rc->width = gc_image->width;
		rc->height = gc_image->height;
		if (rc->enc_resize_ok)
			rfb_send_resize_update_msg(rc, cfd);
	}

	if (discardonly)
		return;

	rfb_send_screen(rc, cfd, 1);
}