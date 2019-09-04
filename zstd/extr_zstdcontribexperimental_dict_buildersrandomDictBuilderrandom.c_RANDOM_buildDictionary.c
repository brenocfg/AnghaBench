#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int notificationLevel; } ;
struct TYPE_8__ {TYPE_1__ zParams; } ;
typedef  TYPE_2__ ZDICT_random_params_t ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_9__ {int end; int begin; } ;
typedef  TYPE_3__ RANDOM_segment_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYUPDATE (int,char*,int /*<<< orphan*/ ) ; 
 size_t MIN (int,size_t) ; 
 TYPE_3__ RANDOM_selectSegment (size_t const,TYPE_2__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static size_t RANDOM_buildDictionary(const size_t totalSamplesSize, const BYTE *samples,
                                    void *dictBuffer, size_t dictBufferCapacity,
                                    ZDICT_random_params_t parameters) {
    BYTE *const dict = (BYTE *)dictBuffer;
    size_t tail = dictBufferCapacity;
    const int displayLevel = parameters.zParams.notificationLevel;
    while (tail > 0) {

      /* Select a segment */
      RANDOM_segment_t segment = RANDOM_selectSegment(totalSamplesSize, parameters);

      size_t segmentSize;
      segmentSize = MIN(segment.end - segment.begin + 1, tail);

      tail -= segmentSize;
      memcpy(dict + tail, samples + segment.begin, segmentSize);
      DISPLAYUPDATE(
          2, "\r%u%%       ",
          (U32)(((dictBufferCapacity - tail) * 100) / dictBufferCapacity));
    }

    return tail;
}