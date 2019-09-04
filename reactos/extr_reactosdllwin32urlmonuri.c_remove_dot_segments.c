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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugstr_wn (char*,int) ; 
 scalar_t__ is_slash (char const) ; 

__attribute__((used)) static DWORD remove_dot_segments(WCHAR *path, DWORD path_len) {
    WCHAR *out = path;
    const WCHAR *in = out;
    const WCHAR *end = out + path_len;
    DWORD len;

    while(in < end) {
        /* Move the first path segment in the input buffer to the end of
         * the output buffer, and any subsequent characters up to, including
         * the next "/" character (if any) or the end of the input buffer.
         */
        while(in < end && !is_slash(*in))
            *out++ = *in++;
        if(in == end)
            break;
        *out++ = *in++;

        while(in < end) {
            if(*in != '.')
                break;

            /* Handle ending "/." */
            if(in + 1 == end) {
                ++in;
                break;
            }

            /* Handle "/./" */
            if(is_slash(in[1])) {
                in += 2;
                continue;
            }

            /* If we don't have "/../" or ending "/.." */
            if(in[1] != '.' || (in + 2 != end && !is_slash(in[2])))
                break;

            /* Find the slash preceding out pointer and move out pointer to it */
            if(out > path+1 && is_slash(*--out))
                --out;
            while(out > path && !is_slash(*(--out)));
            if(is_slash(*out))
                ++out;
            in += 2;
            if(in != end)
                ++in;
        }
    }

    len = out - path;
    TRACE("(%p %d): Path after dot segments removed %s len=%d\n", path, path_len,
        debugstr_wn(path, len), len);
    return len;
}