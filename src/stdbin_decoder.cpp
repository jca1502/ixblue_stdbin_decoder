#include <iXblue_stdbin_decoder/stdbin_decoder.h>

/* Navigation data blocs */
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/acceleration_geographic_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/acceleration_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ahrs_algorithm_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ahrs_system_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ahrs_user_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_heading.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_heading_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_quaternion.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_quaternion_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/course_speed_over_ground.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/current_geographic_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/current_geographic_frame_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/heading_roll_pitch_rate.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/heave_surge_sway_speed.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ins_algorithm_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ins_system_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ins_user_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/position.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/position_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/raw_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/realtime_heave_surge_sway.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/rotation_rate_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/rotation_rate_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/sensor_status.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/smart_heave.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/speed_geographic_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/speed_geographic_frame_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/speed_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/system_date.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/navigation_data/temperatures.h>

/* Extended navigation data blocs */
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/raw_rotation_rate_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_attitude_heading.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_attitude_heading_deviation.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_position.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_position_deviation.h>

/* External data blocs */
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/depth.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/dmi.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/dvl_ground_speed.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/dvl_water_speed.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/emlog.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/eventmarker.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/gnss.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/lbl.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/logbook.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/sound_velocity.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/turret_angles.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/usbl.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/utc.h>
#include <iXblue_stdbin_decoder/memory_blocs_parsers/external_data/vtg.h>

using namespace StdBinDecoder;
using namespace boost::asio;

StdBinDecoder::StdBinDecoder::StdBinDecoder()
    : navigationParsers(
          {std::make_shared<Parser::AttitudeHeading>(),
           std::make_shared<Parser::AttitudeHeadingDeviation>(),
           std::make_shared<Parser::RealTimeHeaveSurgeSway>(),
           std::make_shared<Parser::SmartHeave>(),
           std::make_shared<Parser::HeadingRollPitchRate>(),
           std::make_shared<Parser::RotationRateVesselFrame>(),
           std::make_shared<Parser::AccelerationVesselFrame>(),
           std::make_shared<Parser::Position>(),
           std::make_shared<Parser::PositionDeviation>(),
           std::make_shared<Parser::SpeedGeographicFrame>(),
           std::make_shared<Parser::SpeedGeographicFrameDeviation>(),
           std::make_shared<Parser::CurrentGeographicFrame>(),
           std::make_shared<Parser::CurrentGeographicFrameDeviation>(),
           std::make_shared<Parser::SystemDate>(),
           std::make_shared<Parser::SensorStatus>(),
           std::make_shared<Parser::INSAlgorithmStatus>(),
           std::make_shared<Parser::INSSystemStatus>(),
           std::make_shared<Parser::INSUserStatus>(),
           std::make_shared<Parser::AHRSAlgorithmStatus>(),
           std::make_shared<Parser::AHRSSystemStatus>(),
           std::make_shared<Parser::AHRSUserStatus>(),
           std::make_shared<Parser::HeaveSurgeSwaySpeed>(),
           std::make_shared<Parser::SpeedVesselFrame>(),
           std::make_shared<Parser::AccelerationGeographicFrame>(),
           std::make_shared<Parser::CourseSpeedoverGround>(),
           std::make_shared<Parser::Temperatures>(),
           std::make_shared<Parser::AttitudeQuaternion>(),
           std::make_shared<Parser::AttitudeQuaternionDeviation>(),
           std::make_shared<Parser::RawAccelerationVesselFrame>(),
           std::make_shared<Parser::AccelerationVesselFrameDeviation>(),
           std::make_shared<Parser::RotationRateVesselFrameDeviation>()},
          [](const MemoryBlockParserPtr& lhs, const MemoryBlockParserPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          }),
      extendedNavigationParsers(
          {std::make_shared<Parser::RotationAccelerationVesselFrame>(),
           std::make_shared<Parser::RotationAccelerationVesselFrameDeviation>(),
           std::make_shared<Parser::RawRotationRateVesselFrame>(),
           std::make_shared<Parser::VehicleAttitudeHeading>(),
           std::make_shared<Parser::VehiclePosition>(),
           std::make_shared<Parser::VehiclePositionDeviation>()},
          [](const MemoryBlockParserPtr& lhs, const MemoryBlockParserPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          }),
      externalDataParsers(
          {std::make_shared<Parser::Utc>(),
           std::make_shared<Parser::Gnss1>(),
           std::make_shared<Parser::Gnss2>(),
           std::make_shared<Parser::GnssManual>(),
           std::make_shared<Parser::Emlog1>(),
           std::make_shared<Parser::Emlog2>(),
           std::make_shared<Parser::Depth>(),
           std::make_shared<Parser::Usbl1>(),
           std::make_shared<Parser::Usbl2>(),
           std::make_shared<Parser::Usbl3>(),
           std::make_shared<Parser::DvlGroundSpeed1>(),
           std::make_shared<Parser::DvlWaterSpeed1>(),
           std::make_shared<Parser::SoundVelocity>(),
           std::make_shared<Parser::Dmi>(),
           std::make_shared<Parser::Lbl1>(),
           std::make_shared<Parser::Lbl2>(),
           std::make_shared<Parser::Lbl3>(),
           std::make_shared<Parser::Lbl4>(),
           std::make_shared<Parser::EventMarkerA>(),
           std::make_shared<Parser::EventMarkerB>(),
           std::make_shared<Parser::EventMarkerC>(),
           std::make_shared<Parser::DvlGroundSpeed2>(),
           std::make_shared<Parser::DvlWaterSpeed2>(),
           std::make_shared<Parser::TurretAngles>(),
           std::make_shared<Parser::Vtg1>(),
           std::make_shared<Parser::Vtg2>(),
           std::make_shared<Parser::LogBook>()},
          [](const MemoryBlockParserPtr& lhs, const MemoryBlockParserPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          })

{}

bool StdBinDecoder::StdBinDecoder::parse(const std::vector<uint8_t>& frameData)
{
    std::copy(std::begin(frameData), std::end(frameData),
              std::back_inserter(currentFrame));

    // Now, we will look for version of the received frame and wait to have receive enough
    // data to parse full header.
    if(haveEnoughByteToParseHeader() == false)
    {
        return false;
    }

    boost::asio::mutable_buffer buffer(currentFrame.data(), currentFrame.size());
    lastHeader = parseHeader(buffer);
    // if we didn't receive the whole frame, we return false, and wait for the next
    // memory chunck.
    if(currentFrame.size() < lastHeader.telegramSize) return false;

    for(const auto& parser : navigationParsers)
    {
        parser->parse(buffer, lastHeader.navigationBitMask, lastParsed);
    }

    if(lastHeader.extendedNavigationBitMask.is_initialized())
    {
        for(const auto& parser : extendedNavigationParsers)
        {
            parser->parse(buffer, lastHeader.extendedNavigationBitMask.get(), lastParsed);
        }
    }

    for(const auto& parser : externalDataParsers)
    {
        parser->parse(buffer, lastHeader.externalSensorBitMask, lastParsed);
    }

    currentFrame.clear(); // we clear the current frame to be ready for the next one.
    return true;
}

bool StdBinDecoder::StdBinDecoder::haveEnoughByteToParseHeader(void) const
{
    if(currentFrame.size() > 3)
    {
        uint8_t protocol_version = currentFrame.at(2);
        switch(protocol_version)
        {
        case 0x02: return currentFrame.size() >= HEADER_SIZE_V2;
        case 0x03: return currentFrame.size() >= HEADER_SIZE_V3;
        case 0x04: return currentFrame.size() >= HEADER_SIZE_V4;
        case 0x05: return currentFrame.size() >= HEADER_SIZE_V5;
        default: throw std::runtime_error("Un handled protocol version");
        }
    }
    return false;
}

Data::NavHeader StdBinDecoder::StdBinDecoder::parseHeader(mutable_buffer& buffer) const
{
    // We know we have enough bytes to parse the whole header because it had been
    // checked before.
    static constexpr size_t HEADER_MINIMAL_SIZE = 3;

    Data::NavHeader res;
    if(buffer_size(buffer) < HEADER_MINIMAL_SIZE)
    {
        throw std::runtime_error("Not enough bytes in buffer to parse header");
    }
    if(checkHeader(buffer) == false)
    {
        throw std::runtime_error("Incorrect frame header, expected 'I', 'X'");
    }
    buffer >> res.protocolVersion;
    if(res.protocolVersion < 2 && res.protocolVersion > 5)
    {
        throw std::runtime_error(
            "Unknown protocol version. Supported protocol are version 2->5");
    }

    buffer >> res.navigationBitMask;
    if(res.protocolVersion > 2)
    {
        uint32_t extendedNavigationMask;
        buffer >> extendedNavigationMask;
        res.extendedNavigationBitMask = extendedNavigationMask;
    }
    buffer >> res.externalSensorBitMask;
    uint16_t navigationSize = 0;
    if(res.protocolVersion > 3)
    {
        buffer >> navigationSize;
    }
    buffer >> res.telegramSize;
    buffer >> res.navigationDataValidityTime_100us;
    uint32_t counter;
    buffer >> counter;
    return res;
}

bool StdBinDecoder::StdBinDecoder::checkHeader(mutable_buffer& buffer) const
{
    // We already checked the buffer size before calling this method.
    uint8_t I, X;
    buffer >> I;
    buffer >> X;
    return I == 'I' && X == 'X';
}
