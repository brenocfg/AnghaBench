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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct sproto {int type_n; int /*<<< orphan*/ * type; } ;
struct protocol {int tag; int confirm; int /*<<< orphan*/ * name; int /*<<< orphan*/ ** p; } ;

/* Variables and functions */
 int SIZEOF_FIELD ; 
 int /*<<< orphan*/  SIZEOF_HEADER ; 
 int /*<<< orphan*/  SIZEOF_LENGTH ; 
 size_t SPROTO_REQUEST ; 
 size_t SPROTO_RESPONSE ; 
 int /*<<< orphan*/ * import_string (struct sproto*,int /*<<< orphan*/  const*) ; 
 int struct_field (int /*<<< orphan*/  const*,int) ; 
 int todword (int /*<<< orphan*/  const*) ; 
 int toword (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const uint8_t *
import_protocol(struct sproto *s, struct protocol *p, const uint8_t * stream) {
	const uint8_t * result;
	uint32_t sz = todword(stream);
	int fn;
	int i;
	int tag;
	stream += SIZEOF_LENGTH;
	result = stream + sz;
	fn = struct_field(stream, sz);
	stream += SIZEOF_HEADER;
	p->name = NULL;
	p->tag = -1;
	p->p[SPROTO_REQUEST] = NULL;
	p->p[SPROTO_RESPONSE] = NULL;
	p->confirm = 0;
	tag = 0;
	for (i=0;i<fn;i++,tag++) {
		int value = toword(stream + SIZEOF_FIELD * i);
		if (value & 1) {
			tag += (value-1)/2;
			continue;
		}
		value = value/2 - 1;
		switch (i) {
		case 0: // name
			if (value != -1) {
				return NULL;
			}
			p->name = import_string(s, stream + SIZEOF_FIELD *fn);
			break;
		case 1: // tag
			if (value < 0) {
				return NULL;
			}
			p->tag = value;
			break;
		case 2: // request
			if (value < 0 || value>=s->type_n)
				return NULL;
			p->p[SPROTO_REQUEST] = &s->type[value];
			break;
		case 3: // response
			if (value < 0 || value>=s->type_n)
				return NULL;
			p->p[SPROTO_RESPONSE] = &s->type[value];
			break;
		case 4:	// confirm
			p->confirm = value;
			break;
		default:
			return NULL;
		}
	}

	if (p->name == NULL || p->tag<0) {
		return NULL;
	}

	return result;
}