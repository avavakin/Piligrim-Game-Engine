#pragma once

#include "../../math/vec2.h"

#define MAX_KEYS_COUNT 1024

struct ControlsTable
{
	int keyStates[MAX_KEYS_COUNT];
	vec2 deltaMove;
	vec2 mousePosition;
};