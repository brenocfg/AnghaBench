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
struct MHD_Connection {size_t mode; } ;
typedef  struct MHD_Connection RequestMeta ;

/* Variables and functions */
 int /*<<< orphan*/  MHD_HEADER_KIND ; 
 char* MHD_lookup_connection_value (struct MHD_Connection*,int /*<<< orphan*/ ,char*) ; 
 size_t OUTPUT_EXPORT ; 
 size_t OUTPUT_JSON ; 
 size_t OUTPUT_JSON_SEQ ; 
 size_t OUTPUT_JSON_SSE ; 
 size_t OUTPUT_SHORT ; 
 int /*<<< orphan*/  assert (struct MHD_Connection*) ; 
 int /*<<< orphan*/ * mime_types ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_parse_accept(
                RequestMeta *m,
                struct MHD_Connection *connection) {

        const char *header;

        assert(m);
        assert(connection);

        header = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Accept");
        if (!header)
                return 0;

        if (streq(header, mime_types[OUTPUT_JSON]))
                m->mode = OUTPUT_JSON;
        else if (streq(header, mime_types[OUTPUT_JSON_SSE]))
                m->mode = OUTPUT_JSON_SSE;
        else if (streq(header, mime_types[OUTPUT_JSON_SEQ]))
                m->mode = OUTPUT_JSON_SEQ;
        else if (streq(header, mime_types[OUTPUT_EXPORT]))
                m->mode = OUTPUT_EXPORT;
        else
                m->mode = OUTPUT_SHORT;

        return 0;
}