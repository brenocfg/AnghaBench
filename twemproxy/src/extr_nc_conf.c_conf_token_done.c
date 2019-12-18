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
struct conf {scalar_t__ valid_token; int /*<<< orphan*/  token; int /*<<< orphan*/  valid_parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_token_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
conf_token_done(struct conf *cf)
{
    ASSERT(cf->valid_parser);

    if (cf->valid_token) {
        yaml_token_delete(&cf->token);
        cf->valid_token = 0;
    }
}