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
struct write_buffer {struct write_buffer* buffer; scalar_t__ userobject; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct write_buffer*) ;} ;
struct socket_server {TYPE_1__ soi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct write_buffer*) ; 
 int /*<<< orphan*/  stub1 (struct write_buffer*) ; 

__attribute__((used)) static inline void
write_buffer_free(struct socket_server *ss, struct write_buffer *wb) {
	if (wb->userobject) {
		ss->soi.free(wb->buffer);
	} else {
		FREE(wb->buffer);
	}
	FREE(wb);
}