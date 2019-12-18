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
typedef  char const sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  char const sd_bus ;
typedef  char const ExecContext ;

/* Variables and functions */
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  exec_context_fdname (char const*,int) ; 
 int sd_bus_message_append (char const*,char*,int /*<<< orphan*/ ) ; 
 char const* streq (char const*,char*) ; 

__attribute__((used)) static int property_get_stdio_fdname(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        ExecContext *c = userdata;
        int fileno;

        assert(bus);
        assert(c);
        assert(property);
        assert(reply);

        if (streq(property, "StandardInputFileDescriptorName"))
                fileno = STDIN_FILENO;
        else if (streq(property, "StandardOutputFileDescriptorName"))
                fileno = STDOUT_FILENO;
        else {
                assert(streq(property, "StandardErrorFileDescriptorName"));
                fileno = STDERR_FILENO;
        }

        return sd_bus_message_append(reply, "s", exec_context_fdname(c, fileno));
}