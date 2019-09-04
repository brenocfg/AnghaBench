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
struct TYPE_8__ {scalar_t__ scheme_type; char const* path; void* is_opaque; void* must_have_path; int /*<<< orphan*/  has_implicit_scheme; int /*<<< orphan*/  path_len; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
typedef  int DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  TRACE (char*,char const**,TYPE_1__*,int) ; 
 void* TRUE ; 
 scalar_t__ URL_SCHEME_JAVASCRIPT ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 scalar_t__ URL_SCHEME_WILDCARD ; 
 int Uri_CREATE_NO_CRACK_UNKNOWN_SCHEMES ; 
 scalar_t__ is_hierarchical_uri (char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_authority (char const**,TYPE_1__*,int) ; 
 void* parse_path_hierarchical (char const**,TYPE_1__*,int) ; 
 int /*<<< orphan*/  parse_path_opaque (char const**,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlenW (char const*) ; 

__attribute__((used)) static BOOL parse_hierpart(const WCHAR **ptr, parse_data *data, DWORD flags) {
    const WCHAR *start = *ptr;

    data->must_have_path = FALSE;

    /* For javascript: URIs, simply set everything as a path */
    if(data->scheme_type == URL_SCHEME_JAVASCRIPT) {
        data->path = *ptr;
        data->path_len = strlenW(*ptr);
        data->is_opaque = TRUE;
        *ptr += data->path_len;
        return TRUE;
    }

    /* Checks if the authority information needs to be parsed. */
    if(is_hierarchical_uri(ptr, data)) {
        /* Only treat it as a hierarchical URI if the scheme_type is known or
         * the Uri_CREATE_NO_CRACK_UNKNOWN_SCHEMES flag is not set.
         */
        if(data->scheme_type != URL_SCHEME_UNKNOWN ||
           !(flags & Uri_CREATE_NO_CRACK_UNKNOWN_SCHEMES)) {
            TRACE("(%p %p %x): Treating URI as an hierarchical URI.\n", ptr, data, flags);
            data->is_opaque = FALSE;

            if(data->scheme_type == URL_SCHEME_WILDCARD && !data->has_implicit_scheme) {
                if(**ptr == '/' && *(*ptr+1) == '/') {
                    data->must_have_path = TRUE;
                    *ptr += 2;
                }
            }

            /* TODO: Handle hierarchical URI's, parse authority then parse the path. */
            if(!parse_authority(ptr, data, flags))
                return FALSE;

            return parse_path_hierarchical(ptr, data, flags);
        } else
            /* Reset ptr to its starting position so opaque path parsing
             * begins at the correct location.
             */
            *ptr = start;
    }

    /* If it reaches here, then the URI will be treated as an opaque
     * URI.
     */

    TRACE("(%p %p %x): Treating URI as an opaque URI.\n", ptr, data, flags);

    data->is_opaque = TRUE;
    if(!parse_path_opaque(ptr, data, flags))
        return FALSE;

    return TRUE;
}