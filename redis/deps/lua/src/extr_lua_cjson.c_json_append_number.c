#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strbuf_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int encode_invalid_numbers; int /*<<< orphan*/  encode_number_precision; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  FPCONV_G_FMT_BUFSIZE ; 
 int fpconv_g_fmt (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  json_encode_exception (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,char*) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_append_mem (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strbuf_empty_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_ensure_empty_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_extend_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void json_append_number(lua_State *l, json_config_t *cfg,
                               strbuf_t *json, int lindex)
{
    double num = lua_tonumber(l, lindex);
    int len;

    if (cfg->encode_invalid_numbers == 0) {
        /* Prevent encoding invalid numbers */
        if (isinf(num) || isnan(num))
            json_encode_exception(l, cfg, json, lindex, "must not be NaN or Inf");
    } else if (cfg->encode_invalid_numbers == 1) {
        /* Encode invalid numbers, but handle "nan" separately
         * since some platforms may encode as "-nan". */
        if (isnan(num)) {
            strbuf_append_mem(json, "nan", 3);
            return;
        }
    } else {
        /* Encode invalid numbers as "null" */
        if (isinf(num) || isnan(num)) {
            strbuf_append_mem(json, "null", 4);
            return;
        }
    }

    strbuf_ensure_empty_length(json, FPCONV_G_FMT_BUFSIZE);
    len = fpconv_g_fmt(strbuf_empty_ptr(json), num, cfg->encode_number_precision);
    strbuf_extend_length(json, len);
}