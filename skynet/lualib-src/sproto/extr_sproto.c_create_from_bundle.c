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
struct sproto {int type_n; int protocol_n; int /*<<< orphan*/ * proto; int /*<<< orphan*/ * type; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int SIZEOF_FIELD ; 
 int /*<<< orphan*/  SIZEOF_HEADER ; 
 int SIZEOF_LENGTH ; 
 int count_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * import_protocol (struct sproto*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * import_type (struct sproto*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int struct_field (int /*<<< orphan*/  const*,size_t) ; 
 int todword (int /*<<< orphan*/  const*) ; 
 int toword (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct sproto *
create_from_bundle(struct sproto *s, const uint8_t * stream, size_t sz) {
	const uint8_t * content;
	const uint8_t * typedata = NULL;
	const uint8_t * protocoldata = NULL;
	int fn = struct_field(stream, sz);
	int i;
	if (fn < 0 || fn > 2)
		return NULL;

	stream += SIZEOF_HEADER;
	content = stream + fn*SIZEOF_FIELD;

	for (i=0;i<fn;i++) {
		int value = toword(stream + i*SIZEOF_FIELD);
		int n;
		if (value != 0)
			return NULL;
		n = count_array(content);
		if (n<0)
			return NULL;
		if (i == 0) {
			typedata = content+SIZEOF_LENGTH;
			s->type_n = n;
			s->type = pool_alloc(&s->memory, n * sizeof(*s->type));
		} else {
			protocoldata = content+SIZEOF_LENGTH;
			s->protocol_n = n;
			s->proto = pool_alloc(&s->memory, n * sizeof(*s->proto));
		}
		content += todword(content) + SIZEOF_LENGTH;
	}

	for (i=0;i<s->type_n;i++) {
		typedata = import_type(s, &s->type[i], typedata);
		if (typedata == NULL) {
			return NULL;
		}
	}
	for (i=0;i<s->protocol_n;i++) {
		protocoldata = import_protocol(s, &s->proto[i], protocoldata);
		if (protocoldata == NULL) {
			return NULL;
		}
	}

	return s;
}