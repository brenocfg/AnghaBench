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
typedef  int cdio_log_level_t ;

/* Variables and functions */
#define  CDIO_LOG_ASSERT 132 
#define  CDIO_LOG_DEBUG 131 
#define  CDIO_LOG_ERROR 130 
#define  CDIO_LOG_INFO 129 
#define  CDIO_LOG_WARN 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cdio_assert_not_reached () ; 
 int cdio_loglevel_default ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

extern void
cdio_default_log_handler(cdio_log_level_t level, const char message[])
{
  switch (level)
    {
    case CDIO_LOG_ERROR:
      if (level >= cdio_loglevel_default) {
        fprintf (stderr, "**ERROR: %s\n", message);
        fflush (stderr);
      }
      exit (EXIT_FAILURE);
      break;
    case CDIO_LOG_DEBUG:
      if (level >= cdio_loglevel_default) {
        fprintf (stdout, "--DEBUG: %s\n", message);
      }
      break;
    case CDIO_LOG_WARN:
      if (level >= cdio_loglevel_default) {
        fprintf (stdout, "++ WARN: %s\n", message);
      }
      break;
    case CDIO_LOG_INFO:
      if (level >= cdio_loglevel_default) {
        fprintf (stdout, "   INFO: %s\n", message);
      }
      break;
    case CDIO_LOG_ASSERT:
      if (level >= cdio_loglevel_default) {
        fprintf (stderr, "!ASSERT: %s\n", message);
        fflush (stderr);
      }
      abort ();
      break;
    default:
      cdio_assert_not_reached ();
      break;
    }

  fflush (stdout);
}