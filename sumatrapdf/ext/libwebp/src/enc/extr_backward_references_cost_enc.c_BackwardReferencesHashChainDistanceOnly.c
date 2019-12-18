#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  VP8LHashChain ;
typedef  int /*<<< orphan*/  VP8LColorCache ;
struct TYPE_15__ {int /*<<< orphan*/  error_; } ;
typedef  TYPE_1__ VP8LBackwardRefs ;
struct TYPE_16__ {double* literal_; float* costs_; } ;
typedef  TYPE_2__ CostModel ;
typedef  TYPE_2__ CostManager ;

/* Variables and functions */
 int /*<<< orphan*/  AddSingleLiteralWithCostModel (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *,TYPE_2__* const,int,int const,float const,float*,scalar_t__* const) ; 
 int /*<<< orphan*/  CostManagerClear (TYPE_2__*) ; 
 int /*<<< orphan*/  CostManagerInit (TYPE_2__*,scalar_t__* const,int const,TYPE_2__* const) ; 
 int /*<<< orphan*/  CostModelBuild (TYPE_2__* const,int,int,TYPE_1__ const* const) ; 
 double GetDistanceCost (TYPE_2__* const,int const) ; 
 int MAX_LENGTH ; 
 int NUM_LENGTH_CODES ; 
 int NUM_LITERAL_CODES ; 
 int /*<<< orphan*/  PushInterval (TYPE_2__*,float const,int,int) ; 
 int /*<<< orphan*/  UpdateCostAtIndex (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  VP8LColorCacheClear (int /*<<< orphan*/ *) ; 
 int VP8LColorCacheInit (int /*<<< orphan*/ *,int) ; 
 int VP8LDistanceToPlaneCode (int,int) ; 
 int /*<<< orphan*/  VP8LHashChainFindCopy (int /*<<< orphan*/  const* const,int,int*,int*) ; 
 scalar_t__ WebPSafeCalloc (unsigned long long,size_t const) ; 
 int /*<<< orphan*/  WebPSafeFree (TYPE_2__* const) ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int BackwardReferencesHashChainDistanceOnly(
    int xsize, int ysize, const uint32_t* const argb, int cache_bits,
    const VP8LHashChain* const hash_chain, const VP8LBackwardRefs* const refs,
    uint16_t* const dist_array) {
  int i;
  int ok = 0;
  int cc_init = 0;
  const int pix_count = xsize * ysize;
  const int use_color_cache = (cache_bits > 0);
  const size_t literal_array_size =
      sizeof(double) * (NUM_LITERAL_CODES + NUM_LENGTH_CODES +
                        ((cache_bits > 0) ? (1 << cache_bits) : 0));
  const size_t cost_model_size = sizeof(CostModel) + literal_array_size;
  CostModel* const cost_model =
      (CostModel*)WebPSafeCalloc(1ULL, cost_model_size);
  VP8LColorCache hashers;
  CostManager* cost_manager =
      (CostManager*)WebPSafeMalloc(1ULL, sizeof(*cost_manager));
  int offset_prev = -1, len_prev = -1;
  double offset_cost = -1;
  int first_offset_is_constant = -1;  // initialized with 'impossible' value
  int reach = 0;

  if (cost_model == NULL || cost_manager == NULL) goto Error;

  cost_model->literal_ = (double*)(cost_model + 1);
  if (use_color_cache) {
    cc_init = VP8LColorCacheInit(&hashers, cache_bits);
    if (!cc_init) goto Error;
  }

  if (!CostModelBuild(cost_model, xsize, cache_bits, refs)) {
    goto Error;
  }

  if (!CostManagerInit(cost_manager, dist_array, pix_count, cost_model)) {
    goto Error;
  }

  // We loop one pixel at a time, but store all currently best points to
  // non-processed locations from this point.
  dist_array[0] = 0;
  // Add first pixel as literal.
  AddSingleLiteralWithCostModel(argb, &hashers, cost_model, 0, use_color_cache,
                                0.f, cost_manager->costs_, dist_array);

  for (i = 1; i < pix_count; ++i) {
    const float prev_cost = cost_manager->costs_[i - 1];
    int offset, len;
    VP8LHashChainFindCopy(hash_chain, i, &offset, &len);

    // Try adding the pixel as a literal.
    AddSingleLiteralWithCostModel(argb, &hashers, cost_model, i,
                                  use_color_cache, prev_cost,
                                  cost_manager->costs_, dist_array);

    // If we are dealing with a non-literal.
    if (len >= 2) {
      if (offset != offset_prev) {
        const int code = VP8LDistanceToPlaneCode(xsize, offset);
        offset_cost = GetDistanceCost(cost_model, code);
        first_offset_is_constant = 1;
        PushInterval(cost_manager, prev_cost + offset_cost, i, len);
      } else {
        assert(offset_cost >= 0);
        assert(len_prev >= 0);
        assert(first_offset_is_constant == 0 || first_offset_is_constant == 1);
        // Instead of considering all contributions from a pixel i by calling:
        //         PushInterval(cost_manager, prev_cost + offset_cost, i, len);
        // we optimize these contributions in case offset_cost stays the same
        // for consecutive pixels. This describes a set of pixels similar to a
        // previous set (e.g. constant color regions).
        if (first_offset_is_constant) {
          reach = i - 1 + len_prev - 1;
          first_offset_is_constant = 0;
        }

        if (i + len - 1 > reach) {
          // We can only be go further with the same offset if the previous
          // length was maxed, hence len_prev == len == MAX_LENGTH.
          // TODO(vrabaud), bump i to the end right away (insert cache and
          // update cost).
          // TODO(vrabaud), check if one of the points in between does not have
          // a lower cost.
          // Already consider the pixel at "reach" to add intervals that are
          // better than whatever we add.
          int offset_j, len_j = 0;
          int j;
          assert(len == MAX_LENGTH || len == pix_count - i);
          // Figure out the last consecutive pixel within [i, reach + 1] with
          // the same offset.
          for (j = i; j <= reach; ++j) {
            VP8LHashChainFindCopy(hash_chain, j + 1, &offset_j, &len_j);
            if (offset_j != offset) {
              VP8LHashChainFindCopy(hash_chain, j, &offset_j, &len_j);
              break;
            }
          }
          // Update the cost at j - 1 and j.
          UpdateCostAtIndex(cost_manager, j - 1, 0);
          UpdateCostAtIndex(cost_manager, j, 0);

          PushInterval(cost_manager, cost_manager->costs_[j - 1] + offset_cost,
                       j, len_j);
          reach = j + len_j - 1;
        }
      }
    }

    UpdateCostAtIndex(cost_manager, i, 1);
    offset_prev = offset;
    len_prev = len;
  }

  ok = !refs->error_;
Error:
  if (cc_init) VP8LColorCacheClear(&hashers);
  CostManagerClear(cost_manager);
  WebPSafeFree(cost_model);
  WebPSafeFree(cost_manager);
  return ok;
}