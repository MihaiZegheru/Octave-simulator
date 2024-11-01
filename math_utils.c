/*
 *   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
 */

#include "math_utils.h"

#define MODULO 10007

int modulo(int value)
{
	value %= MODULO;

	if (value < 0)
		return value + MODULO;

	return value;
}
