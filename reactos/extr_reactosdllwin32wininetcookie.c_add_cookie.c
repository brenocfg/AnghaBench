#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* container; int /*<<< orphan*/  entry; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cookie_t ;
struct TYPE_6__ {int /*<<< orphan*/  cookie_list; int /*<<< orphan*/  cookie_url; } ;
typedef  TYPE_2__ cookie_container_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_cookie(cookie_container_t *container, cookie_t *new_cookie)
{
    TRACE("Adding %s=%s to %s\n", debugstr_w(new_cookie->name), debugstr_w(new_cookie->data),
          debugstr_w(container->cookie_url));

    list_add_tail(&container->cookie_list, &new_cookie->entry);
    new_cookie->container = container;
}