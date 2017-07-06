#include <rt_string_msgs/boost/rt_string.h>

#include <rtt_roscomm/rtt_rostopic_ros_msg_transporter.hpp>
#include <rtt_roscomm/rtt_rostopic.h>
#include <rtt/types/TransportPlugin.hpp>
#include <rtt/types/TypekitPlugin.hpp>

namespace rtt_roscomm {
  using namespace RTT;
    struct ROSrt_string_msgsPlugin
      : public types::TransportPlugin
    {
      bool registerTransport(std::string name, types::TypeInfo* ti)
      {
          if(name == "RTT.rt_string") { return ti->addProtocol(ORO_ROS_PROTOCOL_ID,new RosMsgTransporter<RTT::rt_string>());} else
            return false;
      }
      
      std::string getTransportName() const {
          return "ros";
      }
      
      std::string getTypekitName() const {
          return std::string("ros-")+"rt_string_msgs";
      }
      std::string getName() const {
          return std::string("rtt-ros-") + "rt_string_msgs" + "-transport";
      }

    };
}

ORO_TYPEKIT_PLUGIN( rtt_roscomm::ROSrt_string_msgsPlugin )
