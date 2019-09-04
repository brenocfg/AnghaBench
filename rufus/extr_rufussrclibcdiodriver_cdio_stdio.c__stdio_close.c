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
struct TYPE_2__ {int /*<<< orphan*/ * fd_buf; int /*<<< orphan*/ * fd; } ;
typedef  TYPE_1__ _UserData ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_stdio_close(void *user_data)
{
  _UserData *const ud = user_data;

  if (fclose (ud->fd))
    cdio_error ("fclose (): %s", strerror (errno));

  ud->fd = NULL;

  free (ud->fd_buf);
  ud->fd_buf = NULL;

  return 0;
}