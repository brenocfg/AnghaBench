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
struct string {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct conf {int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 struct string* array_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_deinit (struct string*) ; 

__attribute__((used)) static void
conf_pop_scalar(struct conf *cf)
{
    struct string *value;

    value = array_pop(&cf->arg);
    log_debug(LOG_VVERB, "pop '%.*s'", value->len, value->data);
    string_deinit(value);
}