#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/raw_acceleration_vessel_frame.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class RawAccelerationVesselFrame : public MemoryBlockParser
{
public:
    RawAccelerationVesselFrame() : MemoryBlockParser(28, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::RawAccelerationVesselFrame res;
        buffer >> res.xv1_msec2 >> res.xv2_msec2 >> res.xv3_msec2;
        outBinaryNav.rawAccelerationVesselFrame = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder