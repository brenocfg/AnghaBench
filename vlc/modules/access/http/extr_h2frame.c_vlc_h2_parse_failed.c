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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct vlc_h2_parser {int dummy; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 

__attribute__((used)) static int vlc_h2_parse_failed(struct vlc_h2_parser *p, struct vlc_h2_frame *f,
                               size_t len, uint_fast32_t id)
{
    free(f);
    (void) p; (void) len; (void) id;
    return -1;
}