#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct http_parser_url {int field_set; TYPE_1__* field_data; } ;
typedef  enum http_parser_url_fields { ____Placeholder_http_parser_url_fields } http_parser_url_fields ;
struct TYPE_2__ {size_t off; size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* zcalloc (size_t) ; 

__attribute__((used)) static char *copy_url_part(char *url, struct http_parser_url *parts, enum http_parser_url_fields field) {
    char *part = NULL;

    if (parts->field_set & (1 << field)) {
        uint16_t off = parts->field_data[field].off;
        uint16_t len = parts->field_data[field].len;
        part = zcalloc(len + 1 * sizeof(char));
        memcpy(part, &url[off], len);
    }

    return part;
}