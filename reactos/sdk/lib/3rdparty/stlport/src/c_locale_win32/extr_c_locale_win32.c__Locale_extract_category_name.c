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
typedef  int /*<<< orphan*/  _Locale_lcid_t ;

/* Variables and functions */
 char* __Extract_locale_name (char const*,char const*,char*) ; 
 char const* __TranslateToSystem (char const*,char*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static char const* _Locale_extract_category_name(const char* name, const char* category, char* buf,
                                                 _Locale_lcid_t* hint, int *__err_code) {
  const char* cname = __Extract_locale_name(name, category, buf);
  if (cname == 0 || (cname[0] == 'C' && cname[1] == 0)) {
    return cname;
  }
  return __TranslateToSystem(cname, buf, hint, __err_code);
}