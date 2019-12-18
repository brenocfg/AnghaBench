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
struct TYPE_4__ {char const** data; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 size_t PROP_CHASSIS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* fallback_chassis () ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 char* strdup (char*) ; 
 char* strjoin (char*,char const*) ; 

__attribute__((used)) static char* context_fallback_icon_name(Context *c) {
        const char *chassis;

        assert(c);

        if (!isempty(c->data[PROP_CHASSIS]))
                return strjoin("computer-", c->data[PROP_CHASSIS]);

        chassis = fallback_chassis();
        if (chassis)
                return strjoin("computer-", chassis);

        return strdup("computer");
}