/* Auto-generated by genmsg_cpp for file /home/jchen/workspace/src/quadrotor_msgs/msg/PositionCommand.msg
 */
#ifndef QUADROTOR_MSGS_MESSAGE_POSITIONCOMMAND_H
#define QUADROTOR_MSGS_MESSAGE_POSITIONCOMMAND_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Vector3.h"

namespace quadrotor_msgs {
template <class ContainerAllocator>
struct PositionCommand_ {
  typedef PositionCommand_<ContainerAllocator> Type;

  PositionCommand_()
    : header(), position(), velocity(), acceleration(), yaw(0.0), yaw_dot(0.0), kx(), kv() {
    kx.assign(0.0);
    kv.assign(0.0);
  }

  PositionCommand_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , position(_alloc)
    , velocity(_alloc)
    , acceleration(_alloc)
    , yaw(0.0)
    , yaw_dot(0.0)
    , kx()
    , kv() {
    kx.assign(0.0);
    kv.assign(0.0);
  }

  typedef ::std_msgs::Header_<ContainerAllocator> _header_type;
  ::std_msgs::Header_<ContainerAllocator> header;

  typedef ::geometry_msgs::Point_<ContainerAllocator> _position_type;
  ::geometry_msgs::Point_<ContainerAllocator> position;

  typedef ::geometry_msgs::Vector3_<ContainerAllocator> _velocity_type;
  ::geometry_msgs::Vector3_<ContainerAllocator> velocity;

  typedef ::geometry_msgs::Vector3_<ContainerAllocator> _acceleration_type;
  ::geometry_msgs::Vector3_<ContainerAllocator> acceleration;

  typedef double _yaw_type;
  double yaw;

  typedef double _yaw_dot_type;
  double yaw_dot;

  typedef boost::array<double, 3> _kx_type;
  boost::array<double, 3> kx;

  typedef boost::array<double, 3> _kv_type;
  boost::array<double, 3> kv;

  typedef boost::shared_ptr< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> const> ConstPtr;
};  // struct PositionCommand

typedef ::quadrotor_msgs::PositionCommand_<std::allocator<void> > PositionCommand;

typedef boost::shared_ptr< ::quadrotor_msgs::PositionCommand> PositionCommandPtr;
typedef boost::shared_ptr< ::quadrotor_msgs::PositionCommand const> PositionCommandConstPtr;

template <typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s,
                         const ::quadrotor_msgs::PositionCommand_<ContainerAllocator>& v) {
  ros::message_operations::Printer< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> >::stream(
      s, "", v);
  return s;
}

}  // namespace quadrotor_msgs

namespace ros {
namespace message_traits {
template <class ContainerAllocator>
struct IsMessage< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > : public TrueType {};
template <class ContainerAllocator>
struct IsMessage< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> const> : public TrueType {};
template <class ContainerAllocator>
struct MD5Sum< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > {
  static const char* value() {
    return "835935bcd6f18632d9e26a3093237902";
  }

  static const char* value(const ::quadrotor_msgs::PositionCommand_<ContainerAllocator>&) {
    return value();
  }
  static const uint64_t static_value1 = 0x835935bcd6f18632ULL;
  static const uint64_t static_value2 = 0xd9e26a3093237902ULL;
};

template <class ContainerAllocator>
struct DataType< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > {
  static const char* value() {
    return "quadrotor_msgs/PositionCommand";
  }

  static const char* value(const ::quadrotor_msgs::PositionCommand_<ContainerAllocator>&) {
    return value();
  }
};

template <class ContainerAllocator>
struct Definition< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > {
  static const char* value() {
    return "Header header\n\
geometry_msgs/Point position\n\
geometry_msgs/Vector3 velocity\n\
geometry_msgs/Vector3 acceleration\n\
float64 yaw\n\
float64 yaw_dot\n\
float64[3] kx\n\
float64[3] kv\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::quadrotor_msgs::PositionCommand_<ContainerAllocator>&) {
    return value();
  }
};

template <class ContainerAllocator>
struct HasHeader< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > : public TrueType {};
template <class ContainerAllocator>
struct HasHeader<const ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > : public TrueType {};
}  // namespace message_traits
}  // namespace ros

namespace ros {
namespace serialization {

template <class ContainerAllocator>
struct Serializer< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > {
  template <typename Stream, typename T>
  inline static void allInOne(Stream& stream, T m) {
    stream.next(m.header);
    stream.next(m.position);
    stream.next(m.velocity);
    stream.next(m.acceleration);
    stream.next(m.yaw);
    stream.next(m.yaw_dot);
    stream.next(m.kx);
    stream.next(m.kv);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
};  // struct PositionCommand_
}  // namespace serialization
}  // namespace ros

namespace ros {
namespace message_operations {

template <class ContainerAllocator>
struct Printer< ::quadrotor_msgs::PositionCommand_<ContainerAllocator> > {
  template <typename Stream>
  static void stream(Stream& s, const std::string& indent,
                     const ::quadrotor_msgs::PositionCommand_<ContainerAllocator>& v) {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "position: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.position);
    s << indent << "velocity: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.velocity);
    s << indent << "acceleration: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.acceleration);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
    s << indent << "yaw_dot: ";
    Printer<double>::stream(s, indent + "  ", v.yaw_dot);
    s << indent << "kx[]" << std::endl;
    for (size_t i = 0; i < v.kx.size(); ++i) {
      s << indent << "  kx[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.kx[i]);
    }
    s << indent << "kv[]" << std::endl;
    for (size_t i = 0; i < v.kv.size(); ++i) {
      s << indent << "  kv[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.kv[i]);
    }
  }
};

}  // namespace message_operations
}  // namespace ros

#endif  // QUADROTOR_MSGS_MESSAGE_POSITIONCOMMAND_H
