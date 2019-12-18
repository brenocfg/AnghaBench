#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  b_crypt_hdr; } ;
typedef  TYPE_1__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_SPACE_HDRS ; 
 int /*<<< orphan*/  arc_space_consume (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdr_full_cons (void*,void*,int) ; 

__attribute__((used)) static int
hdr_full_crypt_cons(void *vbuf, void *unused, int kmflag)
{
	arc_buf_hdr_t *hdr = vbuf;

	hdr_full_cons(vbuf, unused, kmflag);
	bzero(&hdr->b_crypt_hdr, sizeof (hdr->b_crypt_hdr));
	arc_space_consume(sizeof (hdr->b_crypt_hdr), ARC_SPACE_HDRS);

	return (0);
}