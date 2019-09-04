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

/* Variables and functions */
 size_t MAX_CP_LEN ; 
 size_t MAX_CTRY_LEN ; 
 size_t MAX_LANG_LEN ; 
 int /*<<< orphan*/  _STLP_STRNCPY (char*,size_t,char const*,size_t) ; 
 size_t strcspn (char const*,char*) ; 

int __ParseLocaleString(const char* lname,
                        char* lang, char* ctry, char* page) {
  int param = 0;
  size_t len;
  size_t tmpLen;

  if (lname[0] == 0)
    return 0;

  /* We look for the first country separator '_' */
  len = strcspn(lname, "_");
  if (lname[len] == '_') {
    if (len == 0 || len > MAX_LANG_LEN) return -1; /* empty lang is invalid*/
    _STLP_STRNCPY(lang, MAX_LANG_LEN + 1, lname, len);
    lname += len + 1;
    ++param;
  }

  /* We look for the last code page separator '.' */
  len = -1;
  tmpLen = strcspn(lname, ".");
  while (lname[tmpLen] == '.') {
    len = tmpLen; ++tmpLen;
    tmpLen += strcspn(lname + tmpLen, ".");
  }
  if (len != -1) { /* Means that we found a '.' */
    if (param == 0) {
      /* We have no lang yet so we have to fill it first, no country */
      if (len > MAX_LANG_LEN) return -1;
      if (len == 0) {
        /* No language nor country, only code page */
        ++param;
      }
      else
      { _STLP_STRNCPY(lang, MAX_LANG_LEN + 1, lname, len); }
      ++param;
    }
    else {
      /* We already have a lang so we are now looking for the country: */
      if (len == 0) return -1; /* We forbid locale name with the "_." motif in it */
      if (len > MAX_CTRY_LEN) return -1;
      _STLP_STRNCPY(ctry, MAX_CTRY_LEN + 1, lname, len);
    }
    ++param;
    lname += len + 1;
  }

  /* We look for ',' for compatibility with POSIX */
  len = strcspn(lname, ",");
  switch (param) {
    case 0:
      if (len > MAX_LANG_LEN) return -1;
      _STLP_STRNCPY(lang, MAX_LANG_LEN + 1, lname, len);
      break;
    case 1:
      if (len > MAX_CTRY_LEN) return -1;
      _STLP_STRNCPY(ctry, MAX_CTRY_LEN + 1, lname, len);
      break;
    default:
      if (len > MAX_CP_LEN) return -1;
      _STLP_STRNCPY(page, MAX_CP_LEN + 1, lname, len);
      break;
  }

  /* ',' POSIX modifier is not used in NT */
  return 0;
}