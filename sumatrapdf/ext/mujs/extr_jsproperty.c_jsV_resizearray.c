#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_9__ {int length; } ;
struct TYPE_10__ {TYPE_1__ a; } ;
struct TYPE_11__ {int count; TYPE_2__ u; } ;
typedef  TYPE_3__ js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  jsV_delproperty (int /*<<< orphan*/ *,TYPE_3__*,char const*) ; 
 TYPE_3__* jsV_newiterator (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 char* jsV_nextiterator (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int jsV_numbertointeger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsV_numbertostring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  jsV_stringtonumber (int /*<<< orphan*/ *,char const*) ; 
 char const* js_itoa (char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

void jsV_resizearray(js_State *J, js_Object *obj, int newlen)
{
	char buf[32];
	const char *s;
	int k;
	if (newlen < obj->u.a.length) {
		if (obj->u.a.length > obj->count * 2) {
			js_Object *it = jsV_newiterator(J, obj, 1);
			while ((s = jsV_nextiterator(J, it))) {
				k = jsV_numbertointeger(jsV_stringtonumber(J, s));
				if (k >= newlen && !strcmp(s, jsV_numbertostring(J, buf, k)))
					jsV_delproperty(J, obj, s);
			}
		} else {
			for (k = newlen; k < obj->u.a.length; ++k) {
				jsV_delproperty(J, obj, js_itoa(buf, k));
			}
		}
	}
	obj->u.a.length = newlen;
}