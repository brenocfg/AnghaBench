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
typedef  scalar_t__ uint_fast32_t ;
struct TYPE_2__ {scalar_t__ sid; int eos; scalar_t__ len; } ;
struct vlc_h2_parser {TYPE_1__ headers; int /*<<< orphan*/  parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_h2_parse_headers_block ; 

__attribute__((used)) static void vlc_h2_parse_headers_start(struct vlc_h2_parser *p,
                                       uint_fast32_t sid, bool eos)
{
    assert(sid != 0);
    assert(p->headers.sid == 0);

    p->parser = vlc_h2_parse_headers_block;
    p->headers.sid = sid;
    p->headers.eos = eos;
    p->headers.len = 0;
}