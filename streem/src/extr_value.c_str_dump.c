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
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_int ;

/* Variables and functions */
 int /*<<< orphan*/  isprint (int) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strm_str_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_new (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strm_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_string
str_dump(strm_string str, strm_int len)
{
  char *buf = malloc(len);
  char *s = buf;
  char *p = (char*)strm_str_ptr(str);
  char *pend = p + strm_str_len(str);

  *s++ = '"';
  while (p<pend) {
    switch (*p) {
    case '\n':
      *s++ = '\\';
      *s++ = 'n';
      break;
    case '\r':
      *s++ = '\\';
      *s++ = 'r';
      break;
    case '\t':
      *s++ = '\\';
      *s++ = 't';
      break;
    case 033:
      *s++ = '\\';
      *s++ = 'e';
      break;
    case '\0':
      *s++ = '\\';
      *s++ = '0';
      break;
    case '"':
      *s++ = '\\';
      *s++ = '"';
      break;
    default:
      if (isprint((int)*p) || (*p&0xff) > 0x7f) {
        *s++ = (*p&0xff);
      }
      else {
        sprintf(s, "\\x%02x", (int)*p&0xff);
        s+=4;
      }
    }
    p++;
  }
  *s++ = '"';
  
  return strm_str_new(buf, len);
}