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
typedef  int uint16_t ;
struct http_parser_url {int port; int field_set; TYPE_1__* field_data; } ;
typedef  enum state { ____Placeholder_state } state ;
typedef  enum http_parser_url_fields { ____Placeholder_http_parser_url_fields } http_parser_url_fields ;
struct TYPE_2__ {int len; int off; } ;

/* Variables and functions */
 int UF_FRAGMENT ; 
 int UF_HOST ; 
 int UF_MAX ; 
 int UF_PATH ; 
 int UF_PORT ; 
 int UF_QUERY ; 
 int UF_SCHEMA ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ http_parse_host (char const*,struct http_parser_url*,int) ; 
 int parse_url_char (int,char const) ; 
#define  s_dead 139 
#define  s_req_fragment 138 
#define  s_req_fragment_start 137 
#define  s_req_path 136 
#define  s_req_query_string 135 
#define  s_req_query_string_start 134 
#define  s_req_schema 133 
#define  s_req_schema_slash 132 
#define  s_req_schema_slash_slash 131 
#define  s_req_server 130 
#define  s_req_server_start 129 
#define  s_req_server_with_at 128 
 int s_req_spaces_before_url ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int) ; 

int
http_parser_parse_url(const char *buf, size_t buflen, int is_connect,
                      struct http_parser_url *u)
{
  enum state s;
  const char *p;
  enum http_parser_url_fields uf, old_uf;
  int found_at = 0;

  u->port = u->field_set = 0;
  s = is_connect ? s_req_server_start : s_req_spaces_before_url;
  old_uf = UF_MAX;

  for (p = buf; p < buf + buflen; p++) {
    s = parse_url_char(s, *p);

    /* Figure out the next field that we're operating on */
    switch (s) {
      case s_dead:
        return 1;

      /* Skip delimeters */
      case s_req_schema_slash:
      case s_req_schema_slash_slash:
      case s_req_server_start:
      case s_req_query_string_start:
      case s_req_fragment_start:
        continue;

      case s_req_schema:
        uf = UF_SCHEMA;
        break;

      case s_req_server_with_at:
        found_at = 1;

      /* FALLTHROUGH */
      case s_req_server:
        uf = UF_HOST;
        break;

      case s_req_path:
        uf = UF_PATH;
        break;

      case s_req_query_string:
        uf = UF_QUERY;
        break;

      case s_req_fragment:
        uf = UF_FRAGMENT;
        break;

      default:
        assert(!"Unexpected state");
        return 1;
    }

    /* Nothing's changed; soldier on */
    if (uf == old_uf) {
      u->field_data[uf].len++;
      continue;
    }

    u->field_data[uf].off = p - buf;
    u->field_data[uf].len = 1;

    u->field_set |= (1 << uf);
    old_uf = uf;
  }

  /* host must be present if there is a schema */
  /* parsing http:///toto will fail */
  if ((u->field_set & (1 << UF_SCHEMA)) &&
      (u->field_set & (1 << UF_HOST)) == 0) {
    return 1;
  }

  if (u->field_set & (1 << UF_HOST)) {
    if (http_parse_host(buf, u, found_at) != 0) {
      return 1;
    }
  }

  /* CONNECT requests can only contain "hostname:port" */
  if (is_connect && u->field_set != ((1 << UF_HOST)|(1 << UF_PORT))) {
    return 1;
  }

  if (u->field_set & (1 << UF_PORT)) {
    /* Don't bother with endp; we've already validated the string */
    unsigned long v = strtoul(buf + u->field_data[UF_PORT].off, NULL, 10);

    /* Ports have a max value of 2^16 */
    if (v > 0xffff) {
      return 1;
    }

    u->port = (uint16_t) v;
  }

  return 0;
}