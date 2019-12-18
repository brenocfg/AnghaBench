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
typedef  int /*<<< orphan*/  vlc_log_t ;
typedef  int /*<<< orphan*/  va_list ;
struct vlc_logger_external {int /*<<< orphan*/  opaque; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* log ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_vaLogExternal(void *d, int type, const vlc_log_t *item,
                              const char *format, va_list ap)
{
    struct vlc_logger_external *ext = d;

    ext->ops->log(ext->opaque, type, item, format, ap);
}