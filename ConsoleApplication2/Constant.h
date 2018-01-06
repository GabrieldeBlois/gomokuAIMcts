#pragma once

#include "stdafx.h"

namespace Const
{
static const uint8_t WINALIGN(3);

static const uint8_t TABSIZE(8);

// this means that every diags that are NOT long enough to contain a winning alignement should not be calculated
static const uint8_t TABSIZE_DEVIDED(TABSIZE - WINALIGN);
};
