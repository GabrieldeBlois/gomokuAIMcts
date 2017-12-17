#pragma once

#include "stdafx.h"

namespace Const
{
static const uint8_t WINALIGN(15);

static const uint8_t TABSIZE(20);

// this means that every diags that are NOT long enough to contain a winning alignement should not be calculated
static const uint8_t TABSIZE_DEVIDED(TABSIZE - WINALIGN);
};
