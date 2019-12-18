#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fd; struct TYPE_3__* const pathname; } ;
typedef  TYPE_1__ _UserData ;

/* Variables and functions */
 int /*<<< orphan*/  _stdio_close (void*) ; 
 int /*<<< orphan*/  free (TYPE_1__* const) ; 

__attribute__((used)) static void
_stdio_free(void *user_data)
{
  _UserData *const ud = user_data;

  if (ud->pathname)
    free(ud->pathname);

  if (ud->fd) /* should be NULL anyway... */
    _stdio_close(user_data);

  free(ud);
}