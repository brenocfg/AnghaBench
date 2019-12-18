#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int verbosity; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ vlc_logger_sys_t ;
struct TYPE_5__ {char* psz_module; } ;
typedef  TYPE_2__ vlc_log_t ;
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int,unsigned int const) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ *) ; 
 int* msg_type ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LogHtml(void *opaque, int type, const vlc_log_t *meta,
                    const char *format, va_list ap)
{
    static const unsigned color[4] = {
        0xffffff, 0xff6666, 0xffff66, 0xaaaaaa,
    };
    vlc_logger_sys_t *sys = opaque;
    FILE *stream = sys->stream;

    if (sys->verbosity < type)
        return;

    flockfile(stream);
    fprintf(stream, "%s%s: <span style=\"color: #%06x\">",
            meta->psz_module, msg_type[type], color[type]);
    /* FIXME: encode special ASCII characters */
    vfprintf(stream, format, ap);
    fputs("</span>\n", stream);
    funlockfile(stream);
}