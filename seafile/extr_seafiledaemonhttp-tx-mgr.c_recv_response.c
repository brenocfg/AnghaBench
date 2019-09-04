#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; scalar_t__ content; } ;
typedef  TYPE_1__ HttpResponse ;

/* Variables and functions */
 scalar_t__ g_realloc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

__attribute__((used)) static size_t
recv_response (void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    HttpResponse *rsp = userp;

    rsp->content = g_realloc (rsp->content, rsp->size + realsize);
    if (!rsp->content) {
        seaf_warning ("Not enough memory.\n");
        /* return a value other than realsize to signify an error. */
        return 0;
    }

    memcpy (rsp->content + rsp->size, contents, realsize);
    rsp->size += realsize;

    return realsize;
}