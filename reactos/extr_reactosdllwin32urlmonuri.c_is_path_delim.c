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
typedef  scalar_t__ URL_SCHEME ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ URL_SCHEME_FILE ; 

__attribute__((used)) static inline BOOL is_path_delim(URL_SCHEME scheme, WCHAR val) {
    return (!val || (val == '#' && scheme != URL_SCHEME_FILE) || val == '?');
}