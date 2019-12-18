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
struct TYPE_2__ {struct vlc_h2_parser* buf; int /*<<< orphan*/  decoder; } ;
struct vlc_h2_parser {TYPE_1__ headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_h2_parser*) ; 
 int /*<<< orphan*/  hpack_decode_destroy (int /*<<< orphan*/ ) ; 

void vlc_h2_parse_destroy(struct vlc_h2_parser *p)
{
    hpack_decode_destroy(p->headers.decoder);
    free(p->headers.buf);
    free(p);
}