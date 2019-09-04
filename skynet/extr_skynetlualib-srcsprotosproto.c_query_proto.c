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
struct sproto {int protocol_n; struct protocol* proto; } ;
struct protocol {int tag; } ;

/* Variables and functions */

__attribute__((used)) static struct protocol *
query_proto(const struct sproto *sp, int tag) {
	int begin = 0, end = sp->protocol_n;
	while(begin<end) {
		int mid = (begin+end)/2;
		int t = sp->proto[mid].tag;
		if (t==tag) {
			return &sp->proto[mid];
		}
		if (tag > t) {
			begin = mid+1;
		} else {
			end = mid;
		}
	}
	return NULL;
}