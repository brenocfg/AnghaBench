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
struct MHD_Connection {int argument_parse_error; } ;
typedef  struct MHD_Connection RequestMeta ;

/* Variables and functions */
 int /*<<< orphan*/  MHD_GET_ARGUMENT_KIND ; 
 int /*<<< orphan*/  MHD_get_connection_values (struct MHD_Connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct MHD_Connection*) ; 
 int /*<<< orphan*/  assert (struct MHD_Connection*) ; 
 int /*<<< orphan*/  request_parse_arguments_iterator ; 

__attribute__((used)) static int request_parse_arguments(
                RequestMeta *m,
                struct MHD_Connection *connection) {

        assert(m);
        assert(connection);

        m->argument_parse_error = 0;
        MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, request_parse_arguments_iterator, m);

        return m->argument_parse_error;
}