// Generated by gencpp from file cacc_msgs/CaccControlPacket.msg
// DO NOT EDIT!


#ifndef CACC_MSGS_MESSAGE_CACCCONTROLPACKET_H
#define CACC_MSGS_MESSAGE_CACCCONTROLPACKET_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace cacc_msgs
{
template <class ContainerAllocator>
struct CaccControlPacket_
{
  typedef CaccControlPacket_<ContainerAllocator> Type;

  CaccControlPacket_()
    : id(0)
    , vel_ref(0.0)
    , acc_ref(0.0)
    , checksum(0)  {
    }
  CaccControlPacket_(const ContainerAllocator& _alloc)
    : id(0)
    , vel_ref(0.0)
    , acc_ref(0.0)
    , checksum(0)  {
  (void)_alloc;
    }



   typedef int16_t _id_type;
  _id_type id;

   typedef float _vel_ref_type;
  _vel_ref_type vel_ref;

   typedef float _acc_ref_type;
  _acc_ref_type acc_ref;

   typedef uint32_t _checksum_type;
  _checksum_type checksum;





  typedef boost::shared_ptr< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> const> ConstPtr;

}; // struct CaccControlPacket_

typedef ::cacc_msgs::CaccControlPacket_<std::allocator<void> > CaccControlPacket;

typedef boost::shared_ptr< ::cacc_msgs::CaccControlPacket > CaccControlPacketPtr;
typedef boost::shared_ptr< ::cacc_msgs::CaccControlPacket const> CaccControlPacketConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::cacc_msgs::CaccControlPacket_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::cacc_msgs::CaccControlPacket_<ContainerAllocator1> & lhs, const ::cacc_msgs::CaccControlPacket_<ContainerAllocator2> & rhs)
{
  return lhs.id == rhs.id &&
    lhs.vel_ref == rhs.vel_ref &&
    lhs.acc_ref == rhs.acc_ref &&
    lhs.checksum == rhs.checksum;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::cacc_msgs::CaccControlPacket_<ContainerAllocator1> & lhs, const ::cacc_msgs::CaccControlPacket_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace cacc_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ca73aaf0f9afa68bd8dfa673d8298a2c";
  }

  static const char* value(const ::cacc_msgs::CaccControlPacket_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xca73aaf0f9afa68bULL;
  static const uint64_t static_value2 = 0xd8dfa673d8298a2cULL;
};

template<class ContainerAllocator>
struct DataType< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cacc_msgs/CaccControlPacket";
  }

  static const char* value(const ::cacc_msgs::CaccControlPacket_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int16 id\n"
"float32 vel_ref\n"
"float32 acc_ref\n"
"\n"
"uint32 checksum\n"
;
  }

  static const char* value(const ::cacc_msgs::CaccControlPacket_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.vel_ref);
      stream.next(m.acc_ref);
      stream.next(m.checksum);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct CaccControlPacket_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::cacc_msgs::CaccControlPacket_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::cacc_msgs::CaccControlPacket_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<int16_t>::stream(s, indent + "  ", v.id);
    s << indent << "vel_ref: ";
    Printer<float>::stream(s, indent + "  ", v.vel_ref);
    s << indent << "acc_ref: ";
    Printer<float>::stream(s, indent + "  ", v.acc_ref);
    s << indent << "checksum: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.checksum);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CACC_MSGS_MESSAGE_CACCCONTROLPACKET_H
