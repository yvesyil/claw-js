#include "claw/utils.h"

size_t claw_dtype_byte_size(enum claw_dtype type)
{
	switch (type) {
	case CLAW_INT8:
	case CLAW_UINT8:
		return 1;
	case CLAW_INT16:
	case CLAW_UINT16:
		return 2;
	case CLAW_INT32:
	case CLAW_UINT32:
	case CLAW_FLT32:
		return 4;
	case CLAW_INT64:
	case CLAW_UINT64:
	case CLAW_FLT64:
		return 8;
	}
}

// TODO implement a proper rand func.
inline double claw_get_rand_unit()
{
	return (double)rand() / (double)RAND_MAX;
}
inline float claw_get_rand_unitf()
{
	return (float)rand() / (float)RAND_MAX;
}