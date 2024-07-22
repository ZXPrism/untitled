#pragma once

#include "core/Settings.h"

#include <bitset>
#include <cstdint>

namespace core {

    using Entity = std::uint32_t;
    using Signature = std::bitset<ECS_MAX_COMPONENTS>;

} // namespace core
