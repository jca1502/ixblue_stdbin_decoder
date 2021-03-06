#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/heave_surge_sway_speed.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class HeaveSurgeSwaySpeed : public MemoryBlockParser
{
public:
    HeaveSurgeSwaySpeed() : MemoryBlockParser(21, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::HeaveSurgeSwaySpeed res;
        buffer >> res.realtime_heave_speed >> res.surge_speed >> res.sway_speed;
        outBinaryNav.heaveSurgeSwaySpeed = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder