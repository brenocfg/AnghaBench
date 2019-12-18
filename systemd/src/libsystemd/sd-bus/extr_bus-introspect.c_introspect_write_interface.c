#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* member; int /*<<< orphan*/  signature; } ;
struct TYPE_6__ {char* member; int /*<<< orphan*/  names; int /*<<< orphan*/  result; int /*<<< orphan*/  signature; } ;
struct TYPE_5__ {char* member; char* signature; } ;
struct TYPE_8__ {TYPE_3__ signal; TYPE_2__ method; TYPE_1__ property; } ;
typedef  struct introspect {int type; int flags; int /*<<< orphan*/  f; TYPE_4__ x; } const introspect ;
typedef  struct introspect sd_bus_vtable ;

/* Variables and functions */
 int SD_BUS_VTABLE_DEPRECATED ; 
 int SD_BUS_VTABLE_HIDDEN ; 
 int _SD_BUS_VTABLE_END ; 
#define  _SD_BUS_VTABLE_METHOD 132 
#define  _SD_BUS_VTABLE_PROPERTY 131 
#define  _SD_BUS_VTABLE_SIGNAL 130 
#define  _SD_BUS_VTABLE_START 129 
#define  _SD_BUS_VTABLE_WRITABLE_PROPERTY 128 
 int /*<<< orphan*/  assert (struct introspect const*) ; 
 int /*<<< orphan*/  bus_vtable_has_names (struct introspect const*) ; 
 struct introspect* bus_vtable_next (struct introspect const*,struct introspect const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  introspect_write_arguments (struct introspect const*,char*,char const**,char*) ; 
 int /*<<< orphan*/  introspect_write_flags (struct introspect const*,int,int) ; 
 char* strempty (int /*<<< orphan*/ ) ; 

int introspect_write_interface(struct introspect *i, const sd_bus_vtable *v) {
        const sd_bus_vtable *vtable = v;
        const char *names = "";

        assert(i);
        assert(v);

        for (; v->type != _SD_BUS_VTABLE_END; v = bus_vtable_next(vtable, v)) {

                /* Ignore methods, signals and properties that are
                 * marked "hidden", but do show the interface
                 * itself */

                if (v->type != _SD_BUS_VTABLE_START && (v->flags & SD_BUS_VTABLE_HIDDEN))
                        continue;

                switch (v->type) {

                case _SD_BUS_VTABLE_START:
                        if (v->flags & SD_BUS_VTABLE_DEPRECATED)
                                fputs("  <annotation name=\"org.freedesktop.DBus.Deprecated\" value=\"true\"/>\n", i->f);
                        break;

                case _SD_BUS_VTABLE_METHOD:
                        fprintf(i->f, "  <method name=\"%s\">\n", v->x.method.member);
                        if (bus_vtable_has_names(vtable))
                                names = strempty(v->x.method.names);
                        introspect_write_arguments(i, strempty(v->x.method.signature), &names, "in");
                        introspect_write_arguments(i, strempty(v->x.method.result), &names, "out");
                        introspect_write_flags(i, v->type, v->flags);
                        fputs("  </method>\n", i->f);
                        break;

                case _SD_BUS_VTABLE_PROPERTY:
                case _SD_BUS_VTABLE_WRITABLE_PROPERTY:
                        fprintf(i->f, "  <property name=\"%s\" type=\"%s\" access=\"%s\">\n",
                                v->x.property.member,
                                v->x.property.signature,
                                v->type == _SD_BUS_VTABLE_WRITABLE_PROPERTY ? "readwrite" : "read");
                        introspect_write_flags(i, v->type, v->flags);
                        fputs("  </property>\n", i->f);
                        break;

                case _SD_BUS_VTABLE_SIGNAL:
                        fprintf(i->f, "  <signal name=\"%s\">\n", v->x.signal.member);
                        if (bus_vtable_has_names(vtable))
                                names = strempty(v->x.method.names);
                        introspect_write_arguments(i, strempty(v->x.signal.signature), &names, NULL);
                        introspect_write_flags(i, v->type, v->flags);
                        fputs("  </signal>\n", i->f);
                        break;
                }

        }

        return 0;
}