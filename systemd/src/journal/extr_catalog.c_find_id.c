#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  comparison_fn_t ;
struct TYPE_6__ {int /*<<< orphan*/  catalog_item_size; int /*<<< orphan*/  n_items; int /*<<< orphan*/  header_size; } ;
struct TYPE_5__ {char* language; int /*<<< orphan*/  offset; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ CatalogItem ;
typedef  TYPE_2__ CatalogHeader ;

/* Variables and functions */
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  STR_IN_SET (char const*,char*,char*) ; 
 TYPE_1__* bsearch (TYPE_1__*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ catalog_compare_func ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 int le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int,char const*) ; 
 char* setlocale (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  zero (char*) ; 

__attribute__((used)) static const char *find_id(void *p, sd_id128_t id) {
        CatalogItem *f = NULL, key = { .id = id };
        const CatalogHeader *h = p;
        const char *loc;

        loc = setlocale(LC_MESSAGES, NULL);
        if (!isempty(loc) && !STR_IN_SET(loc, "C", "POSIX")) {
                size_t len;

                len = strcspn(loc, ".@");
                if (len > sizeof(key.language) - 1)
                        log_debug("LC_MESSAGES value too long, ignoring: \"%.*s\"", (int) len, loc);
                else {
                        strncpy(key.language, loc, len);
                        key.language[len] = '\0';

                        f = bsearch(&key,
                                    (const uint8_t*) p + le64toh(h->header_size),
                                    le64toh(h->n_items),
                                    le64toh(h->catalog_item_size),
                                    (comparison_fn_t) catalog_compare_func);
                        if (!f) {
                                char *e;

                                e = strchr(key.language, '_');
                                if (e) {
                                        *e = 0;
                                        f = bsearch(&key,
                                                    (const uint8_t*) p + le64toh(h->header_size),
                                                    le64toh(h->n_items),
                                                    le64toh(h->catalog_item_size),
                                                    (comparison_fn_t) catalog_compare_func);
                                }
                        }
                }
        }

        if (!f) {
                zero(key.language);
                f = bsearch(&key,
                            (const uint8_t*) p + le64toh(h->header_size),
                            le64toh(h->n_items),
                            le64toh(h->catalog_item_size),
                            (comparison_fn_t) catalog_compare_func);
        }

        if (!f)
                return NULL;

        return (const char*) p +
                le64toh(h->header_size) +
                le64toh(h->n_items) * le64toh(h->catalog_item_size) +
                le64toh(f->offset);
}