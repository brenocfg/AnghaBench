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
struct TYPE_2__ {int /*<<< orphan*/ * fd; int /*<<< orphan*/  fd_buf; int /*<<< orphan*/  pathname; } ;
typedef  TYPE_1__ _UserData ;

/* Variables and functions */
 int /*<<< orphan*/ * CDIO_FOPEN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CDIO_STDIO_BUFSIZE ; 
 int /*<<< orphan*/  _IOFBF ; 
 int /*<<< orphan*/  calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_stdio_open (void *user_data)
{
  _UserData *const ud = user_data;

  if ((ud->fd = CDIO_FOPEN (ud->pathname, "rb")))
    {
      ud->fd_buf = calloc (1, CDIO_STDIO_BUFSIZE);
      setvbuf (ud->fd, ud->fd_buf, _IOFBF, CDIO_STDIO_BUFSIZE);
    }

  return (ud->fd == NULL);
}