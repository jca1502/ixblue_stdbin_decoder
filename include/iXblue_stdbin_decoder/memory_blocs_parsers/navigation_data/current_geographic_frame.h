#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/current_geographic_frame.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class CurrentGeographicFrame : public MemoryBlockParser
{
public:
    CurrentGeographicFrame() : MemoryBlockParser(11, 8) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::CurrentGeographicFrame res;
        buffer >> res.north_msec >> res.east_msec;
        outBinaryNav.currentGeographicFrame = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder