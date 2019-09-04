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
typedef  int /*<<< orphan*/  vbuf ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int adns__vbuf_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 

int adns__vbuf_appendstr(vbuf *vb, const char *data) {
  int l;
  l= strlen(data);
  return adns__vbuf_append(vb,(byte*)data,l);
}