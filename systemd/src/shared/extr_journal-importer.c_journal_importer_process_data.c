#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int state; size_t data_size; size_t field_len; int /*<<< orphan*/  iovw; } ;
typedef  TYPE_1__ JournalImporter ;

/* Variables and functions */
#define  IMPORTER_STATE_DATA 131 
#define  IMPORTER_STATE_DATA_FINISH 130 
#define  IMPORTER_STATE_DATA_START 129 
 void* IMPORTER_STATE_EOF ; 
#define  IMPORTER_STATE_LINE 128 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  cellescape (char*,int,char*) ; 
 int get_data_data (TYPE_1__*,void**) ; 
 int get_data_newline (TYPE_1__*) ; 
 int get_data_size (TYPE_1__*) ; 
 int get_line (TYPE_1__*,char**,size_t*) ; 
 int iovw_put (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  journal_field_valid (char*,int,int) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_trace (char*,...) ; 
 char* memchr (char*,char,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int process_special_field (TYPE_1__*,char*) ; 
 char* strndupa (char*,int) ; 

int journal_importer_process_data(JournalImporter *imp) {
        int r;

        switch(imp->state) {
        case IMPORTER_STATE_LINE: {
                char *line, *sep;
                size_t n = 0;

                assert(imp->data_size == 0);

                r = get_line(imp, &line, &n);
                if (r < 0)
                        return r;
                if (r == 0) {
                        imp->state = IMPORTER_STATE_EOF;
                        return 0;
                }
                assert(n > 0);
                assert(line[n-1] == '\n');

                if (n == 1) {
                        log_trace("Received empty line, event is ready");
                        return 1;
                }

                /* MESSAGE=xxx\n
                   or
                   COREDUMP\n
                   LLLLLLLL0011223344...\n
                */
                sep = memchr(line, '=', n);
                if (sep) {
                        /* chomp newline */
                        n--;

                        if (!journal_field_valid(line, sep - line, true)) {
                                char buf[64], *t;

                                t = strndupa(line, sep - line);
                                log_debug("Ignoring invalid field: \"%s\"",
                                          cellescape(buf, sizeof buf, t));

                                return 0;
                        }

                        line[n] = '\0';
                        r = process_special_field(imp, line);
                        if (r != 0)
                                return r < 0 ? r : 0;

                        r = iovw_put(&imp->iovw, line, n);
                        if (r < 0)
                                return r;
                } else {
                        /* replace \n with = */
                        line[n-1] = '=';

                        imp->field_len = n;
                        imp->state = IMPORTER_STATE_DATA_START;

                        /* we cannot put the field in iovec until we have all data */
                }

                log_trace("Received: %.*s (%s)", (int) n, line, sep ? "text" : "binary");

                return 0; /* continue */
        }

        case IMPORTER_STATE_DATA_START:
                assert(imp->data_size == 0);

                r = get_data_size(imp);
                // log_debug("get_data_size() -> %d", r);
                if (r < 0)
                        return r;
                if (r == 0) {
                        imp->state = IMPORTER_STATE_EOF;
                        return 0;
                }

                imp->state = imp->data_size > 0 ?
                        IMPORTER_STATE_DATA : IMPORTER_STATE_DATA_FINISH;

                return 0; /* continue */

        case IMPORTER_STATE_DATA: {
                void *data;
                char *field;

                assert(imp->data_size > 0);

                r = get_data_data(imp, &data);
                // log_debug("get_data_data() -> %d", r);
                if (r < 0)
                        return r;
                if (r == 0) {
                        imp->state = IMPORTER_STATE_EOF;
                        return 0;
                }

                assert(data);

                field = (char*) data - sizeof(uint64_t) - imp->field_len;
                memmove(field + sizeof(uint64_t), field, imp->field_len);

                r = iovw_put(&imp->iovw, field + sizeof(uint64_t), imp->field_len + imp->data_size);
                if (r < 0)
                        return r;

                imp->state = IMPORTER_STATE_DATA_FINISH;

                return 0; /* continue */
        }

        case IMPORTER_STATE_DATA_FINISH:
                r = get_data_newline(imp);
                // log_debug("get_data_newline() -> %d", r);
                if (r < 0)
                        return r;
                if (r == 0) {
                        imp->state = IMPORTER_STATE_EOF;
                        return 0;
                }

                imp->data_size = 0;
                imp->state = IMPORTER_STATE_LINE;

                return 0; /* continue */
        default:
                assert_not_reached("wtf?");
        }
}