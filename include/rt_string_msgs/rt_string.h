#ifndef RTT_STRING_MSGS_MESSAGE_RT_STRING_H
#define RTT_STRING_MSGS_MESSAGE_RT_STRING_H

#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>
#include <ros/static_assert.h> 

#include <std_msgs/String.h>
#include <rtt/rt_string.hpp>


namespace rt_string_msgs {
template <typename ContainerAllocator> using rt_string_ = RTT::rt_string;
}

namespace ros 
{
namespace message_traits 
{

template <>
struct IsFixedSize< ::RTT::rt_string >
  : FalseType
  { };

template <>
struct IsFixedSize< ::RTT::rt_string const>
  : FalseType
  { };

template <>
struct IsMessage< ::RTT::rt_string>
  : TrueType
  { };

template <>
struct IsMessage< ::RTT::rt_string const>
  : TrueType
  { };

template <>
struct HasHeader< ::RTT::rt_string >
  : FalseType
  { };

template <>
struct HasHeader< ::RTT::rt_string const>
  : FalseType
  { };


template<>
struct MD5Sum< ::RTT::rt_string >
{
  static const char* value()
  {
    //Ensure that if the definition of std_msgs/String changes we have a compile error here.
    ROS_STATIC_ASSERT(MD5Sum< std_msgs::String_< RTT::os::rt_allocator<void> > >::static_value1 == 0x992ce8a1687cec8cULL);
    ROS_STATIC_ASSERT(MD5Sum< std_msgs::String_< RTT::os::rt_allocator<void> >>::static_value2 == 0x8bd883ec73ca41d1ULL);
    return MD5Sum< std_msgs::String_< RTT::os::rt_allocator<void> > >::value();
  }

  static const char* value(const ::RTT::rt_string&)
  {
    return MD5Sum< std_msgs::String_< RTT::os::rt_allocator<void> > >::value();
  }

};

template <>
struct DataType< ::RTT::rt_string >
{
  static const char* value()
  {
    return DataType< std_msgs::String_< RTT::os::rt_allocator<void> > >::value();
  }

  static const char* value(const ::RTT::rt_string&)
  {
    return DataType< std_msgs::String_< RTT::os::rt_allocator<void> > >::value();
  }
};

template <>
struct Definition< ::RTT::rt_string >
{
  static const char* value()
  {
    return Definition< std_msgs::String_< RTT::os::rt_allocator<void> > >::value();
  }

  static const char* value(const ::RTT::rt_string&)
  {
    return Definition< std_msgs::String_< RTT::os::rt_allocator<void> > >::value();
  }
};


} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{
template<> struct Serializer< ::RTT::rt_string >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T s)
  {
    stream.next(s);
  }
  
  ROS_DECLARE_ALLINONE_SERIALIZER;
};

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template <>
struct Printer< ::RTT::rt_string >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::RTT::rt_string& str)
  {
    
    s << indent << "data: ";
    s << indent << str;
  }
};

} // namespace message_operations
} // namespace ros

#endif // RTT_STRING_MSGS_MESSAGE_RT_STRING_H

