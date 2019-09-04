#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sproto_type {char* name; int n; struct field* f; } ;
struct sproto {int type_n; int protocol_n; struct protocol* proto; struct sproto_type* type; } ;
struct protocol {char* name; int tag; scalar_t__ confirm; TYPE_2__** p; } ;
struct field {int type; scalar_t__ extra; char* name; int tag; scalar_t__ key; TYPE_1__* st; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 size_t SPROTO_REQUEST ; 
 size_t SPROTO_RESPONSE ; 
 int SPROTO_TARRAY ; 
#define  SPROTO_TBOOLEAN 130 
#define  SPROTO_TINTEGER 129 
#define  SPROTO_TSTRING 128 
 scalar_t__ SPROTO_TSTRING_BINARY ; 
 int SPROTO_TSTRUCT ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
sproto_dump(struct sproto *s) {
	int i,j;
	printf("=== %d types ===\n", s->type_n);
	for (i=0;i<s->type_n;i++) {
		struct sproto_type *t = &s->type[i];
		printf("%s\n", t->name);
		for (j=0;j<t->n;j++) {
			char array[2] = { 0, 0 };
			const char * type_name = NULL;
			struct field *f = &t->f[j];
			int type = f->type & ~SPROTO_TARRAY;
			if (f->type & SPROTO_TARRAY) {
				array[0] = '*';
			} else {
				array[0] = 0;
			}
			if (type == SPROTO_TSTRUCT) {
				type_name = f->st->name;
			} else {
				switch(type) {
				case SPROTO_TINTEGER:
					if (f->extra) {
						type_name = "decimal";
					} else {
						type_name = "integer";
					}
					break;
				case SPROTO_TBOOLEAN:
					type_name = "boolean";
					break;
				case SPROTO_TSTRING:
					if (f->extra == SPROTO_TSTRING_BINARY)
						type_name = "binary";
					else
						type_name = "string";
					break;
				default:
					type_name = "invalid";
					break;
				}
			}
			printf("\t%s (%d) %s%s", f->name, f->tag, array, type_name);
			if (type == SPROTO_TINTEGER && f->extra > 0) {
				printf("(%d)", f->extra);
			}
			if (f->key >= 0) {
				printf("[%d]", f->key);
			}
			printf("\n");
		}
	}
	printf("=== %d protocol ===\n", s->protocol_n);
	for (i=0;i<s->protocol_n;i++) {
		struct protocol *p = &s->proto[i];
		if (p->p[SPROTO_REQUEST]) {
			printf("\t%s (%d) request:%s", p->name, p->tag, p->p[SPROTO_REQUEST]->name);
		} else {
			printf("\t%s (%d) request:(null)", p->name, p->tag);
		}
		if (p->p[SPROTO_RESPONSE]) {
			printf(" response:%s", p->p[SPROTO_RESPONSE]->name);
		} else if (p->confirm) {
			printf(" response nil");
		}
		printf("\n");
	}
}