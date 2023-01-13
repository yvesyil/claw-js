#include "claw/utils.h"

size_t claw_dtype_size(enum ClawDType type)
{
	switch (type) {
	case CLAW_INT8:
	case CLAW_UINT8:
		return 8;
	case CLAW_INT16:
	case CLAW_UINT16:
		return 16;
	case CLAW_INT32:
	case CLAW_UINT32:
	case CLAW_FLT32:
		return 32;
	case CLAW_INT64:
	case CLAW_UINT64:
	case CLAW_FLT64:
		return 64;
	}
}