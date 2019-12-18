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
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__ cdio_log_level_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  _handler (scalar_t__,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ cdio_loglevel_default ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdio_logv(cdio_log_level_t level, const char format[], va_list args)
{
  char buf[1024] = { 0, };

  /* _handler() is user defined and we want to make sure _handler()
  doesn't call us, cdio_logv. in_recursion is used for that, however
  it has a problem in multi-threaded programs. I'm not sure how to
  handle multi-threading and recursion checking both. For now, we'll
  leave in the recursion checking, at the expense of handling
  multi-threaded log calls. To ameliorate this, we'll check the log
  level and handle calls where there is no output, before the
  recursion check.
  */
 static int in_recursion = 0;

  if (level < cdio_loglevel_default) return;

  if (in_recursion) {
    /* Can't use cdio_assert_not_reached() as that may call cdio_logv */
    assert(0);
  }

  in_recursion = 1;

  vsnprintf(buf, sizeof(buf)-1, format, args);

  _handler(level, buf);

  in_recursion = 0;
}