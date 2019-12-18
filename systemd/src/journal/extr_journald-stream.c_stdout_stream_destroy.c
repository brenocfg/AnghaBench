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
struct TYPE_4__ {scalar_t__ state_file; } ;
typedef  TYPE_1__ StdoutStream ;

/* Variables and functions */
 int /*<<< orphan*/  stdout_stream_free (TYPE_1__*) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

void stdout_stream_destroy(StdoutStream *s) {
        if (!s)
                return;

        if (s->state_file)
                (void) unlink(s->state_file);

        stdout_stream_free(s);
}