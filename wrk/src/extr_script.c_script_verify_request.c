#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  on_message_complete; } ;
typedef  TYPE_1__ http_parser_settings ;
struct TYPE_8__ {size_t* data; } ;
typedef  TYPE_2__ http_parser ;
typedef  enum http_errno { ____Placeholder_http_errno } http_errno ;

/* Variables and functions */
 int HPE_OK ; 
 int HTTP_PARSER_ERRNO (TYPE_2__*) ; 
 int /*<<< orphan*/  HTTP_REQUEST ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 char* http_errno_description (int) ; 
 size_t http_parser_execute (TYPE_2__*,TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  http_parser_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_request (int /*<<< orphan*/ *,char**,size_t*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verify_request ; 

size_t script_verify_request(lua_State *L) {
    http_parser_settings settings = {
        .on_message_complete = verify_request
    };
    http_parser parser;
    char *request = NULL;
    size_t len, count = 0;

    script_request(L, &request, &len);
    http_parser_init(&parser, HTTP_REQUEST);
    parser.data = &count;

    size_t parsed = http_parser_execute(&parser, &settings, request, len);

    if (parsed != len || count == 0) {
        enum http_errno err = HTTP_PARSER_ERRNO(&parser);
        const char *desc = http_errno_description(err);
        const char *msg = err != HPE_OK ? desc : "incomplete request";
        int line = 1, column = 1;

        for (char *c = request; c < request + parsed; c++) {
            column++;
            if (*c == '\n') {
                column = 1;
                line++;
            }
        }

        fprintf(stderr, "%s at %d:%d\n", msg, line, column);
        exit(1);
    }

    return count;
}