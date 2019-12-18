#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct CDIO_STAT_STRUCT {int /*<<< orphan*/  st_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  read; int /*<<< orphan*/  stat; int /*<<< orphan*/  seek; int /*<<< orphan*/  open; int /*<<< orphan*/ * member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ cdio_stream_io_functions ;
struct TYPE_7__ {char* pathname; int /*<<< orphan*/  st_size; } ;
typedef  TYPE_2__ _UserData ;
typedef  int /*<<< orphan*/  CdioDataSource_t ;

/* Variables and functions */
 int CDIO_STAT_CALL (char*,struct CDIO_STAT_STRUCT*) ; 
 char* _cdio_strdup_fixpath (char const*) ; 
 int /*<<< orphan*/  _stdio_close ; 
 int /*<<< orphan*/  _stdio_free ; 
 int /*<<< orphan*/  _stdio_open ; 
 int /*<<< orphan*/  _stdio_read ; 
 int /*<<< orphan*/  _stdio_seek ; 
 int /*<<< orphan*/  _stdio_stat ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdio_free (char*) ; 
 int /*<<< orphan*/ * cdio_stream_new (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdio_warn (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

CdioDataSource_t *
cdio_stdio_new(const char pathname[])
{
  CdioDataSource_t *new_obj = NULL;
  cdio_stream_io_functions funcs = { NULL, NULL, NULL, NULL, NULL, NULL };
  _UserData *ud = NULL;
  struct CDIO_STAT_STRUCT statbuf;
  char* pathdup;

  if (pathname == NULL)
    return NULL;

  /* MinGW may require a translated path */
  pathdup = _cdio_strdup_fixpath(pathname);
  if (pathdup == NULL)
    return NULL;

  if (CDIO_STAT_CALL (pathdup, &statbuf) == -1)
    {
      cdio_warn ("could not retrieve file info for `%s': %s",
                 pathdup, strerror (errno));
      cdio_free(pathdup);
      return NULL;
    }

  ud = calloc (1, sizeof (_UserData));
  cdio_assert (ud != NULL);

  ud->pathname = pathdup;
  ud->st_size  = statbuf.st_size; /* let's hope it doesn't change... */

  funcs.open   = _stdio_open;
  funcs.seek   = _stdio_seek;
  funcs.stat   = _stdio_stat;
  funcs.read   = _stdio_read;
  funcs.close  = _stdio_close;
  funcs.free   = _stdio_free;

  new_obj = cdio_stream_new(ud, &funcs);

  return new_obj;
}