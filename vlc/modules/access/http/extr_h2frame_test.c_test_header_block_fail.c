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
struct vlc_h2_frame {struct vlc_h2_frame* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX ; 
 int /*<<< orphan*/  assert (int) ; 
 struct vlc_h2_frame* ping () ; 
 struct vlc_h2_frame* response (int) ; 
 scalar_t__ test_bad_seq (int /*<<< orphan*/ ,struct vlc_h2_frame*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_header_block_fail(void)
{
    struct vlc_h2_frame *hf = response(true);
    struct vlc_h2_frame *pf = ping();

    /* Check what happens if non-CONTINUATION frame after HEADERS */
    assert(hf != NULL && hf->next != NULL && pf != NULL);
    pf->next = hf->next;
    hf->next = pf;
    assert(test_bad_seq(CTX, hf, NULL) == 0);
}