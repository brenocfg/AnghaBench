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
struct vlc_h2_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ping () ; 
 scalar_t__ test_raw_seq (struct vlc_h2_parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_h2_frame_test_callbacks ; 
 int /*<<< orphan*/  vlc_h2_parse_destroy (struct vlc_h2_parser*) ; 
 struct vlc_h2_parser* vlc_h2_parse_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_preface_fail(void)
{
    struct vlc_h2_parser *p;

    p = vlc_h2_parse_init(CTX, &vlc_h2_frame_test_callbacks);
    assert(p != NULL);

    assert(test_raw_seq(p, ping(), ping(), NULL) == 0);

    vlc_h2_parse_destroy(p);
}