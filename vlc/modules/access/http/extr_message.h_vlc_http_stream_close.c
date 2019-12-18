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
struct vlc_http_stream {TYPE_1__* cbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct vlc_http_stream*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vlc_http_stream*,int) ; 

__attribute__((used)) static inline void vlc_http_stream_close(struct vlc_http_stream *s, bool abort)
{
    s->cbs->close(s, abort);
}