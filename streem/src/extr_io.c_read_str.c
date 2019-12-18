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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_int ;

/* Variables and functions */
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_value
read_str(const char* beg, strm_int len)
{
  char *p = malloc(len);

  memcpy(p, beg, len);
  return strm_str_value(strm_str_new(p, len));
}