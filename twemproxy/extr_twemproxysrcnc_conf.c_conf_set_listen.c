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
typedef  char uint8_t ;
typedef  int uint32_t ;
struct string {char* data; int len; } ;
struct conf_listen {int valid; int perm; int /*<<< orphan*/  info; int /*<<< orphan*/  port; int /*<<< orphan*/  name; int /*<<< orphan*/  pname; } ;
struct conf {int /*<<< orphan*/  arg; } ;
struct command {int offset; } ;
typedef  scalar_t__ rstatus_t ;
typedef  int mode_t ;

/* Variables and functions */
 char* CONF_ERROR ; 
 char* CONF_OK ; 
 scalar_t__ NC_OK ; 
 struct string* array_top (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nc_atoi (char*,int) ; 
 scalar_t__ nc_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* nc_strrchr (char*,char*,char) ; 
 int /*<<< orphan*/  nc_valid_port (int /*<<< orphan*/ ) ; 
 scalar_t__ string_copy (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ string_duplicate (int /*<<< orphan*/ *,struct string*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

char *
conf_set_listen(struct conf *cf, struct command *cmd, void *conf)
{
    rstatus_t status;
    struct string *value;
    struct conf_listen *field;
    uint8_t *p, *name;
    uint32_t namelen;

    p = conf;
    field = (struct conf_listen *)(p + cmd->offset);

    if (field->valid == 1) {
        return "is a duplicate";
    }

    value = array_top(&cf->arg);

    status = string_duplicate(&field->pname, value);
    if (status != NC_OK) {
        return CONF_ERROR;
    }

    if (value->data[0] == '/') {
        uint8_t *q, *start, *perm;
        uint32_t permlen;


        /* parse "socket_path permissions" from the end */
        p = value->data + value->len -1;
        start = value->data;
        q = nc_strrchr(p, start, ' ');
        if (q == NULL) {
            /* no permissions field, so use defaults */
            name = value->data;
            namelen = value->len;
        } else {
            perm = q + 1;
            permlen = (uint32_t)(p - perm + 1);

            p = q - 1;
            name = start;
            namelen = (uint32_t)(p - start + 1);

            errno = 0;
            field->perm = (mode_t)strtol((char *)perm, NULL, 8);
            if (errno || field->perm > 0777) {
                return "has an invalid file permission in \"socket_path permission\" format string";
            }
        }
    } else {
        uint8_t *q, *start, *port;
        uint32_t portlen;

        /* parse "hostname:port" from the end */
        p = value->data + value->len - 1;
        start = value->data;
        q = nc_strrchr(p, start, ':');
        if (q == NULL) {
            return "has an invalid \"hostname:port\" format string";
        }

        port = q + 1;
        portlen = (uint32_t)(p - port + 1);

        p = q - 1;

        name = start;
        namelen = (uint32_t)(p - start + 1);

        field->port = nc_atoi(port, portlen);
        if (field->port < 0 || !nc_valid_port(field->port)) {
            return "has an invalid port in \"hostname:port\" format string";
        }
    }

    status = string_copy(&field->name, name, namelen);
    if (status != NC_OK) {
        return CONF_ERROR;
    }

    status = nc_resolve(&field->name, field->port, &field->info);
    if (status != NC_OK) {
        return CONF_ERROR;
    }

    field->valid = 1;

    return CONF_OK;
}