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
struct TYPE_6__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vlc_logger_t ;
typedef  int /*<<< orphan*/  vlc_log_t ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int /*<<< orphan*/  (* log ) (TYPE_2__*,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void vlc_vaLogCallback(vlc_logger_t *logger, int type,
                              const vlc_log_t *item, const char *format,
                              va_list ap)
{
    if (logger != NULL) {
        int canc = vlc_savecancel();

        logger->ops->log(logger, type, item, format, ap);
        vlc_restorecancel(canc);
    }
}