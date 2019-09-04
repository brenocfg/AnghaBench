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
typedef  scalar_t__ URL_SCHEME ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_FTP ; 
 scalar_t__ URL_SCHEME_GOPHER ; 
 scalar_t__ URL_SCHEME_HTTP ; 
 scalar_t__ URL_SCHEME_HTTPS ; 
 scalar_t__ URL_SCHEME_NNTP ; 
 scalar_t__ URL_SCHEME_RES ; 
 scalar_t__ URL_SCHEME_TELNET ; 
 scalar_t__ URL_SCHEME_WAIS ; 

__attribute__((used)) static inline BOOL is_hierarchical_scheme(URL_SCHEME type) {
    return(type == URL_SCHEME_HTTP || type == URL_SCHEME_FTP ||
           type == URL_SCHEME_GOPHER || type == URL_SCHEME_NNTP ||
           type == URL_SCHEME_TELNET || type == URL_SCHEME_WAIS ||
           type == URL_SCHEME_FILE || type == URL_SCHEME_HTTPS ||
           type == URL_SCHEME_RES);
}