#include "Id.h"

unsigned int global_id = 0;

unsigned int get_next_id() {
    return ++global_id;
}