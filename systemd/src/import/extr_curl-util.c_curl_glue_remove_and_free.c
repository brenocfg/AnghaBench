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
struct TYPE_4__ {scalar_t__ curl; } ;
typedef  TYPE_1__ CurlGlue ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (scalar_t__,int /*<<< orphan*/ *) ; 

void curl_glue_remove_and_free(CurlGlue *g, CURL *c) {
        assert(g);

        if (!c)
                return;

        if (g->curl)
                curl_multi_remove_handle(g->curl, c);

        curl_easy_cleanup(c);
}