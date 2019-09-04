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
typedef  int /*<<< orphan*/  tab_cmd ;
typedef  int /*<<< orphan*/  spaces_cmd ;
typedef  int /*<<< orphan*/  space_cmd ;
typedef  int /*<<< orphan*/  shortpath_cmd ;
typedef  int /*<<< orphan*/  pwd_cmd ;
typedef  int /*<<< orphan*/  path_cmd ;
typedef  int /*<<< orphan*/  or_broken_cmd ;
typedef  int /*<<< orphan*/  drive_cmd ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  broken (int) ; 
 int /*<<< orphan*/  drive ; 
 int drive_len ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  path ; 
 int path_len ; 
 int /*<<< orphan*/  shortpath ; 
 int shortpath_len ; 
 int /*<<< orphan*/  workdir ; 
 int workdir_len ; 

__attribute__((used)) static const char *compare_line(const char *out_line, const char *out_end, const char *exp_line,
        const char *exp_end)
{
    const char *out_ptr = out_line, *exp_ptr = exp_line;
    const char *err = NULL;

    static const char pwd_cmd[] = {'@','p','w','d','@'};
    static const char drive_cmd[] = {'@','d','r','i','v','e','@'};
    static const char path_cmd[]  = {'@','p','a','t','h','@'};
    static const char shortpath_cmd[]  = {'@','s','h','o','r','t','p','a','t','h','@'};
    static const char space_cmd[] = {'@','s','p','a','c','e','@'};
    static const char spaces_cmd[] = {'@','s','p','a','c','e','s','@'};
    static const char tab_cmd[]   = {'@','t','a','b','@'};
    static const char or_broken_cmd[] = {'@','o','r','_','b','r','o','k','e','n','@'};

    while(exp_ptr < exp_end) {
        if(*exp_ptr == '@') {
            if(exp_ptr+sizeof(pwd_cmd) <= exp_end
                    && !memcmp(exp_ptr, pwd_cmd, sizeof(pwd_cmd))) {
                exp_ptr += sizeof(pwd_cmd);
                if(out_end-out_ptr < workdir_len
                   || (CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, out_ptr, workdir_len,
                       workdir, workdir_len) != CSTR_EQUAL)) {
                    err = out_ptr;
                }else {
                    out_ptr += workdir_len;
                    continue;
                }
            } else if(exp_ptr+sizeof(drive_cmd) <= exp_end
                    && !memcmp(exp_ptr, drive_cmd, sizeof(drive_cmd))) {
                exp_ptr += sizeof(drive_cmd);
                if(out_end-out_ptr < drive_len
                   || (CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE,
                                      out_ptr, drive_len, drive, drive_len) != CSTR_EQUAL)) {
                    err = out_ptr;
                }else {
                    out_ptr += drive_len;
                    continue;
                }
            } else if(exp_ptr+sizeof(path_cmd) <= exp_end
                    && !memcmp(exp_ptr, path_cmd, sizeof(path_cmd))) {
                exp_ptr += sizeof(path_cmd);
                if(out_end-out_ptr < path_len
                   || (CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE,
                                      out_ptr, path_len, path, path_len) != CSTR_EQUAL)) {
                    err = out_ptr;
                }else {
                    out_ptr += path_len;
                    continue;
                }
            } else if(exp_ptr+sizeof(shortpath_cmd) <= exp_end
                    && !memcmp(exp_ptr, shortpath_cmd, sizeof(shortpath_cmd))) {
                exp_ptr += sizeof(shortpath_cmd);
                if(out_end-out_ptr < shortpath_len
                   || (CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE,
                                      out_ptr, shortpath_len, shortpath, shortpath_len) != CSTR_EQUAL)) {
                    err = out_ptr;
                }else {
                    out_ptr += shortpath_len;
                    continue;
                }
            }else if(exp_ptr+sizeof(space_cmd) <= exp_end
                    && !memcmp(exp_ptr, space_cmd, sizeof(space_cmd))) {
                exp_ptr += sizeof(space_cmd);
                if(out_ptr < out_end && *out_ptr == ' ') {
                    out_ptr++;
                    continue;
                } else {
                    err = out_end;
                }
            }else if(exp_ptr+sizeof(spaces_cmd) <= exp_end
                    && !memcmp(exp_ptr, spaces_cmd, sizeof(spaces_cmd))) {
                exp_ptr += sizeof(spaces_cmd);
                if(out_ptr < out_end && *out_ptr == ' ') {
                    while (out_ptr < out_end && *out_ptr == ' ') out_ptr++;
                    continue;
                } else {
                    err = out_end;
                }
            }else if(exp_ptr+sizeof(tab_cmd) <= exp_end
                    && !memcmp(exp_ptr, tab_cmd, sizeof(tab_cmd))) {
                exp_ptr += sizeof(tab_cmd);
                if(out_ptr < out_end && *out_ptr == '\t') {
                    out_ptr++;
                    continue;
                } else {
                    err = out_end;
                }
            }else if(exp_ptr+sizeof(or_broken_cmd) <= exp_end
                     && !memcmp(exp_ptr, or_broken_cmd, sizeof(or_broken_cmd))) {
                if(out_ptr == out_end)
                    return NULL;
                else
                    err = out_ptr;
            }else if(out_ptr == out_end || *out_ptr != *exp_ptr)
                err = out_ptr;
        }else if(out_ptr == out_end || *out_ptr != *exp_ptr) {
            err = out_ptr;
        }

        if(err) {
            if(!broken(1))
                return err;

            while(exp_ptr+sizeof(or_broken_cmd) <= exp_end && memcmp(exp_ptr, or_broken_cmd, sizeof(or_broken_cmd)))
                exp_ptr++;
            exp_ptr += sizeof(or_broken_cmd);
            if (exp_ptr > exp_end) return err;
            out_ptr = out_line;
            err = NULL;
            continue;
        }

        exp_ptr++;
        out_ptr++;
    }

    if(exp_ptr != exp_end)
        return out_ptr;
    else if(out_ptr != out_end)
        return exp_end;

    return NULL;
}