#pragma once
#ifndef _tgl_fixed_h_
#define _tgl_fixed_h_

#include "fixed_point_math.h"

/* fixed point math */
#ifdef TGL_FIXED

/* base type */
typedef fix32_t real_t;

/* min, max, epsilon */
#define REAL_EPSILON FIX32_EPSILON
#define REAL_MIN FIX32_MIN
#define REAL_MAX FIX32_MAX

/* one */
#define REAL_ONE FIX32_ONE

/* static initialization macros */
#define REAL(a) FIX32(a)

/* math macros */
#define REAL_MUL(a, b) FIX32_MUL(a, b)
#define REAL_DIV(a, b) FIX32_DIV(a, b)
#define REAL_FLOOR(a) FIX32_FLOOR(a)
#define REAL_CEIL(a) FIX32_CEIL(a)
#define REAL_FRAC(a) FIX32_FRAC(a)
#define REAL_ROUND(a) FIX32_ROUND(a)

/* type conversion macros */
#define REAL_TO_INT(a) FIX32_TO_INT(a)
#define REAL_TO_FIX16(a) ((fix16_t)(a))
#define REAL_TO_FIX32(a) (a)
#define REAL_TO_FLOAT(a) FIX32_TO_FLOAT(a)
#define REAL_TO_DOUBLE(a) FIX32_TO_DOUBLE(a)

#else

/* base type */
typedef float real_t;

/* min, max, epsilon */
#define REAL_EPSILON FLT_EPSILON
#define REAL_MIN FLT_MAX
#define REAL_MAX FLT_MIN

/* one */
#define REAL_ONE 1.0f

/* static initialization macros */
#define REAL(a) ((real_t)(a))

/* math macros */
#define REAL_MUL(a, b) ((a) * (b))
#define REAL_DIV(a, b) ((a) / (b))
#define REAL_FLOOR(a) ((int32_t)(a))
#define REAL_CEIL(a) ((int32_t)(a) == (a) ? (a) : (int32_t)((a) + 1))
#define REAL_FRAC(a) ((a) - (int32_t)(a))
#define REAL_ROUND(a) ((int32_t)((a) < 0 ? (a) - 0.5 : (a) + 0.5))

/* type conversion macros */
#define REAL_TO_INT(a) ((int)(a))
#define REAL_TO_FIX16(a) FIX16(a)
#define REAL_TO_FIX32(a) FIX32(a)
#define REAL_TO_FLOAT(a) (a)
#define REAL_TO_DOUBLE(a) ((double)(a))

#endif

#endif /* _tgl_fixed_h_ */
