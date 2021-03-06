#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/rotation_acceleration_vessel_frame.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class RotationAccelerationVesselFrame : public MemoryBlockParser
{
public:
    RotationAccelerationVesselFrame() : MemoryBlockParser(0, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::RotationAccelerationVesselFrame res;
        buffer >> res.xv1_degsec2 >> res.xv2_degsec2 >> res.xv3_degsec2;
        outBinaryNav.rotationAccelerationVesselFrame = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder