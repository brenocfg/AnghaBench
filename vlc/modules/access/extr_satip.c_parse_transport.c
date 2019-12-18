#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {char* udp_address; int /*<<< orphan*/  udp_port; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int UDP_ADDRESS_LEN ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  __MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int parse_port (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int parse_transport(stream_t *access, char *request_line) {
    access_sys_t *sys = access->p_sys;
    char *state;
    char *tok;
    int err;

    tok = strtok_r(request_line, ";", &state);
    if (tok == NULL || strncmp(tok, "RTP/AVP", 7) != 0)
        return VLC_EGENERIC;

    tok = strtok_r(NULL, ";", &state);
    if (tok == NULL || strncmp(tok, "multicast", 9) != 0)
        return 0;

    while ((tok = strtok_r(NULL, ";", &state)) != NULL) {
        if (strncmp(tok, "destination=", 12) == 0) {
            memcpy(sys->udp_address, tok + 12, __MIN(strlen(tok + 12), UDP_ADDRESS_LEN - 1));
        } else if (strncmp(tok, "port=", 5) == 0) {
            char port[6];
            char *end;

            memset(port, 0x00, 6);
            memcpy(port, tok + 5, __MIN(strlen(tok + 5), 5));
            if ((end = strstr(port, "-")) != NULL)
                *end = '\0';
            err = parse_port(port, &sys->udp_port);
            if (err)
                return err;
        }
    }

    return 0;
}