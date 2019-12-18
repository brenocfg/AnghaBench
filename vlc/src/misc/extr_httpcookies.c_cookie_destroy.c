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
struct TYPE_4__ {struct TYPE_4__* psz_path; struct TYPE_4__* psz_domain; struct TYPE_4__* psz_value; struct TYPE_4__* psz_name; } ;
typedef  TYPE_1__ http_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void cookie_destroy(http_cookie_t *cookie)
{
    assert(cookie != NULL);
    free(cookie->psz_name);
    free(cookie->psz_value);
    free(cookie->psz_domain);
    free(cookie->psz_path);
    free(cookie);
}