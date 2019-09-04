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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int Uri_CREATE_CANONICALIZE ; 
 int Uri_CREATE_CRACK_UNKNOWN_SCHEMES ; 
 int Uri_CREATE_DECODE_EXTRA_INFO ; 
 int Uri_CREATE_IE_SETTINGS ; 
 int Uri_CREATE_NO_CANONICALIZE ; 
 int Uri_CREATE_NO_CRACK_UNKNOWN_SCHEMES ; 
 int Uri_CREATE_NO_DECODE_EXTRA_INFO ; 
 int Uri_CREATE_NO_IE_SETTINGS ; 
 int Uri_CREATE_NO_PRE_PROCESS_HTML_URI ; 
 int Uri_CREATE_PRE_PROCESS_HTML_URI ; 

__attribute__((used)) static inline BOOL has_invalid_flag_combination(DWORD flags) {
    return((flags & Uri_CREATE_DECODE_EXTRA_INFO && flags & Uri_CREATE_NO_DECODE_EXTRA_INFO) ||
           (flags & Uri_CREATE_CANONICALIZE && flags & Uri_CREATE_NO_CANONICALIZE) ||
           (flags & Uri_CREATE_CRACK_UNKNOWN_SCHEMES && flags & Uri_CREATE_NO_CRACK_UNKNOWN_SCHEMES) ||
           (flags & Uri_CREATE_PRE_PROCESS_HTML_URI && flags & Uri_CREATE_NO_PRE_PROCESS_HTML_URI) ||
           (flags & Uri_CREATE_IE_SETTINGS && flags & Uri_CREATE_NO_IE_SETTINGS));
}