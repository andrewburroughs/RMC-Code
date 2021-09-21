// Generated by gencpp from file messages/TalonOut.msg
// DO NOT EDIT!


#ifndef MESSAGES_MESSAGE_TALONOUT_H
#define MESSAGES_MESSAGE_TALONOUT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace messages
{
template <class ContainerAllocator>
struct TalonOut_
{
  typedef TalonOut_<ContainerAllocator> Type;

  TalonOut_()
    : current(0.0)
    , voltage(0.0)
    , temperature(0.0)
    , position(0)
    , velocity(0)  {
    }
  TalonOut_(const ContainerAllocator& _alloc)
    : current(0.0)
    , voltage(0.0)
    , temperature(0.0)
    , position(0)
    , velocity(0)  {
  (void)_alloc;
    }



   typedef float _current_type;
  _current_type current;

   typedef float _voltage_type;
  _voltage_type voltage;

   typedef float _temperature_type;
  _temperature_type temperature;

   typedef int32_t _position_type;
  _position_type position;

   typedef int32_t _velocity_type;
  _velocity_type velocity;





  typedef boost::shared_ptr< ::messages::TalonOut_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::messages::TalonOut_<ContainerAllocator> const> ConstPtr;

}; // struct TalonOut_

typedef ::messages::TalonOut_<std::allocator<void> > TalonOut;

typedef boost::shared_ptr< ::messages::TalonOut > TalonOutPtr;
typedef boost::shared_ptr< ::messages::TalonOut const> TalonOutConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::messages::TalonOut_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::messages::TalonOut_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace messages

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/lunar/share/std_msgs/cmake/../msg'], 'messages': ['/home/nvidia/SoftwareDevelopment/ROS/src/messages/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::messages::TalonOut_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::messages::TalonOut_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::messages::TalonOut_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::messages::TalonOut_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::messages::TalonOut_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::messages::TalonOut_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::messages::TalonOut_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1dfab55edab53accf343c309dd48ae24";
  }

  static const char* value(const ::messages::TalonOut_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1dfab55edab53accULL;
  static const uint64_t static_value2 = 0xf343c309dd48ae24ULL;
};

template<class ContainerAllocator>
struct DataType< ::messages::TalonOut_<ContainerAllocator> >
{
  static const char* value()
  {
    return "messages/TalonOut";
  }

  static const char* value(const ::messages::TalonOut_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::messages::TalonOut_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 current\n\
float32 voltage\n\
float32 temperature\n\
int32 position\n\
int32 velocity\n\
";
  }

  static const char* value(const ::messages::TalonOut_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::messages::TalonOut_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.current);
      stream.next(m.voltage);
      stream.next(m.temperature);
      stream.next(m.position);
      stream.next(m.velocity);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TalonOut_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::messages::TalonOut_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::messages::TalonOut_<ContainerAllocator>& v)
  {
    s << indent << "current: ";
    Printer<float>::stream(s, indent + "  ", v.current);
    s << indent << "voltage: ";
    Printer<float>::stream(s, indent + "  ", v.voltage);
    s << indent << "temperature: ";
    Printer<float>::stream(s, indent + "  ", v.temperature);
    s << indent << "position: ";
    Printer<int32_t>::stream(s, indent + "  ", v.position);
    s << indent << "velocity: ";
    Printer<int32_t>::stream(s, indent + "  ", v.velocity);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MESSAGES_MESSAGE_TALONOUT_H
