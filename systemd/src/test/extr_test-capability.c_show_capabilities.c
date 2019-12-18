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
typedef  char* cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (char*) ; 
 int /*<<< orphan*/  cap_free (char*) ; 
 char* cap_get_proc () ; 
 char* cap_to_text (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*,char*) ; 

__attribute__((used)) static void show_capabilities(void) {
        cap_t caps;
        char *text;

        caps = cap_get_proc();
        assert_se(caps);

        text = cap_to_text(caps, NULL);
        assert_se(text);

        log_info("Capabilities:%s", text);
        cap_free(caps);
        cap_free(text);
}