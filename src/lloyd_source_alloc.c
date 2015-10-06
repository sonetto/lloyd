#include "include/lloyd_alloc.h"
#include "include/lloyd_context.h"

struct lloyd_source_data *lloyd_source_alloc() {
    return lloyd_alloc(lloyd.sources);
}
