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
struct strm_string {char const* ptr; int len; } ;
typedef  int strm_value ;
typedef  int strm_string ;
typedef  int strm_int ;

/* Variables and functions */
 int STRM_TAG_STRING_6 ; 
 int STRM_TAG_STRING_F ; 
 int STRM_TAG_STRING_I ; 
 int STRM_TAG_STRING_O ; 
 int STRM_VAL_MASK ; 
 char* VAL_PTR (int) ; 
 struct strm_string* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ readonly_data_p (char const*) ; 
 int strm_tag_vptr (struct strm_string*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_string
str_new(const char* p, strm_int len, int foreign)
{
  strm_value tag;
  strm_value val;
  char* s;

  if (!p) goto mkbuf;
  if (len < 6) {
    tag = STRM_TAG_STRING_I;
    val = 0;
    s = VAL_PTR(val)+1;
    memcpy(s, p, len);
    s[-1] = len;
  }
  else if (len == 6) {
    tag = STRM_TAG_STRING_6;
    val = 0;
    s = VAL_PTR(val);
    memcpy(s, p, len);
  }
  else {
    struct strm_string* str;

    if (p && (foreign || readonly_data_p(p))) {
      tag = STRM_TAG_STRING_F;
      str = malloc(sizeof(struct strm_string));
      str->ptr = p;
    }
    else {
      char *buf;

    mkbuf:
      tag = STRM_TAG_STRING_O;
      str = malloc(sizeof(struct strm_string)+len+1);
      buf = (char*)&str[1];
      if (p) {
        memcpy(buf, p, len);
      }
      else {
        memset(buf, 0, len);
      }
      buf[len] = '\0';
      str->ptr = buf;
    }
    str->len = len;
    val = strm_tag_vptr(str, 0);
  }
  return tag | (val & STRM_VAL_MASK);
}