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
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IN_SET (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char SD_BUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  SD_BUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  SD_BUS_TYPE_SIGNATURE ; 
 int /*<<< orphan*/  SD_BUS_TYPE_STRING ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*,char*) ; 
 int sd_bus_message_peek_type (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_bus_message_rewind (int /*<<< orphan*/ *,int) ; 
 int sd_bus_message_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bus_message_get_arg_skip(
                sd_bus_message *m,
                unsigned i,
                char *_type,
                const char **_contents) {

        unsigned j;
        int r;

        r = sd_bus_message_rewind(m, true);
        if (r < 0)
                return r;

        for (j = 0;; j++) {
                const char *contents;
                char type;

                r = sd_bus_message_peek_type(m, &type, &contents);
                if (r < 0)
                        return r;
                if (r == 0)
                        return -ENXIO;

                /* Don't match against arguments after the first one we don't understand */
                if (!IN_SET(type, SD_BUS_TYPE_STRING, SD_BUS_TYPE_OBJECT_PATH, SD_BUS_TYPE_SIGNATURE) &&
                    !(type == SD_BUS_TYPE_ARRAY && STR_IN_SET(contents, "s", "o", "g")))
                        return -ENXIO;

                if (j >= i) {
                        if (_contents)
                                *_contents = contents;
                        if (_type)
                                *_type = type;
                        return 0;
                }

                r = sd_bus_message_skip(m, NULL);
                if (r < 0)
                        return r;
        }

}