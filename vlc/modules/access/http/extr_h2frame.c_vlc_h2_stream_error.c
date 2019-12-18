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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct vlc_h2_parser {int /*<<< orphan*/  opaque; TYPE_1__* cbs; } ;
struct TYPE_2__ {int (* stream_error ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_h2_stream_error(struct vlc_h2_parser *p, uint_fast32_t id,
                               uint_fast32_t code)
{
    return p->cbs->stream_error(p->opaque, id, code);
}