#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  logger; } ;
typedef  TYPE_1__ vlc_object_t ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 char* vlc_object_typename (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_vaLog (int /*<<< orphan*/ *,int,char const*,char const*,char const*,unsigned int,char const*,char const*,int /*<<< orphan*/ ) ; 

void vlc_object_vaLog(vlc_object_t *obj, int prio, const char *module,
                      const char *file, unsigned line, const char *func,
                      const char *format, va_list ap)
{
    if (obj == NULL)
        return;

    const char *typename = vlc_object_typename(obj);
    /* FIXME: libvlc allows NULL type but modules don't */
    if (typename == NULL)
        typename = "generic";

    vlc_vaLog(&obj->logger, prio, typename, module, file, line, func,
              format, ap);
}