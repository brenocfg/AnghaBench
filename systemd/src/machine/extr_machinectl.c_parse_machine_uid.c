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

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ arg_uid ; 
 scalar_t__ isempty (char const*) ; 
 char* strchr (char const*,char) ; 
 char* strdup (scalar_t__) ; 
 char* strndup (char const*,int) ; 

__attribute__((used)) static int parse_machine_uid(const char *spec, const char **machine, char **uid) {
        /*
         * Whatever is specified in the spec takes priority over global arguments.
         */
        char *_uid = NULL;
        const char *_machine = NULL;

        if (spec) {
                const char *at;

                at = strchr(spec, '@');
                if (at) {
                        if (at == spec)
                                /* Do the same as ssh and refuse "@host". */
                                return -EINVAL;

                        _machine = at + 1;
                        _uid = strndup(spec, at - spec);
                        if (!_uid)
                                return -ENOMEM;
                } else
                        _machine = spec;
        };

        if (arg_uid && !_uid) {
                _uid = strdup(arg_uid);
                if (!_uid)
                        return -ENOMEM;
        }

        *uid = _uid;
        *machine = isempty(_machine) ? ".host" : _machine;
        return 0;
}