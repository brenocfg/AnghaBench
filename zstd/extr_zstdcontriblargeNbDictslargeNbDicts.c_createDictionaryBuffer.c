#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* ptr; size_t capacity; size_t size; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL (int) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 size_t UINT_MAX ; 
 size_t ZDICT_trainFromBuffer (void* const,size_t,void const*,size_t const*,unsigned int) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ createBuffer_fromFile (char const*) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static buffer_t
createDictionaryBuffer(const char* dictionaryName,
                       const void* srcBuffer,
                       const size_t* srcBlockSizes, size_t nbBlocks,
                       size_t requestedDictSize)
{
    if (dictionaryName) {
        DISPLAYLEVEL(3, "loading dictionary %s \n", dictionaryName);
        return createBuffer_fromFile(dictionaryName);  /* note : result might be kBuffNull */

    } else {

        DISPLAYLEVEL(3, "creating dictionary, of target size %u bytes \n",
                        (unsigned)requestedDictSize);
        void* const dictBuffer = malloc(requestedDictSize);
        CONTROL(dictBuffer != NULL);

        assert(nbBlocks <= UINT_MAX);
        size_t const dictSize = ZDICT_trainFromBuffer(dictBuffer, requestedDictSize,
                                                      srcBuffer,
                                                      srcBlockSizes, (unsigned)nbBlocks);
        CONTROL(!ZSTD_isError(dictSize));

        buffer_t result;
        result.ptr = dictBuffer;
        result.capacity = requestedDictSize;
        result.size = dictSize;
        return result;
    }
}