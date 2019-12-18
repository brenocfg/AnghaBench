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
 scalar_t__ isspace (char) ; 
 char* strsep (char**,char const*) ; 

__attribute__((used)) static char *get_value(char **buffer) {
        static const char *quote_string = "\"\n";
        static const char *comma_string = ",\n";
        char *val;
        const char *end;

        if (**buffer == '"') {
                /*
                 * skip leading quote, terminate when quote seen
                 */
                (*buffer)++;
                end = quote_string;
        } else {
                end = comma_string;
        }
        val = strsep(buffer, end);
        if (val && end == quote_string)
                /*
                 * skip trailing quote
                 */
                (*buffer)++;

        while (isspace(**buffer))
                (*buffer)++;

        return val;
}