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
struct vlc_h2_frame {int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  external_tls ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 size_t vlc_h2_frame_size (struct vlc_h2_frame*) ; 
 scalar_t__ vlc_tls_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void conn_send(struct vlc_h2_frame *f)
{
    assert(f != NULL);

    size_t len = vlc_h2_frame_size(f);
    ssize_t val = vlc_tls_Write(external_tls, f->data, len);
    assert((size_t)val == len);
    free(f);
}