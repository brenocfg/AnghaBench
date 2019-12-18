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
typedef  int /*<<< orphan*/ * sd_bus_message ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ **,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_log_parse_error (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int json_transform_one (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int json_variant_new_array (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  json_variant_unref_many (int /*<<< orphan*/ **,size_t) ; 
 int log_oom () ; 
 int sd_bus_message_at_end (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int json_transform_array_or_struct(sd_bus_message *m, JsonVariant **ret) {
        size_t n_elements = 0, n_allocated = 0;
        JsonVariant **elements = NULL;
        int r;

        assert(m);
        assert(ret);

        for (;;) {
                r = sd_bus_message_at_end(m, false);
                if (r < 0) {
                        bus_log_parse_error(r);
                        goto finish;
                }
                if (r > 0)
                        break;

                if (!GREEDY_REALLOC(elements, n_allocated, n_elements + 1)) {
                        r = log_oom();
                        goto finish;
                }

                r = json_transform_one(m, elements + n_elements);
                if (r < 0)
                        goto finish;

                n_elements++;
        }

        r = json_variant_new_array(ret, elements, n_elements);

finish:
        json_variant_unref_many(elements, n_elements);
        free(elements);

        return r;
}