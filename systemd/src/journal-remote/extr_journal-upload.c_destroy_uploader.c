#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  events; int /*<<< orphan*/  sigint_event; int /*<<< orphan*/  sigterm_event; int /*<<< orphan*/  input_event; int /*<<< orphan*/  url; int /*<<< orphan*/  current_cursor; int /*<<< orphan*/  last_cursor; int /*<<< orphan*/  answer; int /*<<< orphan*/  header; int /*<<< orphan*/  easy; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  close_fd_input (TYPE_1__*) ; 
 int /*<<< orphan*/  close_journal_input (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_uploader(Uploader *u) {
        assert(u);

        curl_easy_cleanup(u->easy);
        curl_slist_free_all(u->header);
        free(u->answer);

        free(u->last_cursor);
        free(u->current_cursor);

        free(u->url);

        u->input_event = sd_event_source_unref(u->input_event);

        close_fd_input(u);
        close_journal_input(u);

        sd_event_source_unref(u->sigterm_event);
        sd_event_source_unref(u->sigint_event);
        sd_event_unref(u->events);
}