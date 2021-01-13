// Generated by gencpp from file cacc_msgs/PrarxParam.msg
// DO NOT EDIT!


#ifndef CACC_MSGS_MESSAGE_PRARXPARAM_H
#define CACC_MSGS_MESSAGE_PRARXPARAM_H


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
struct PrarxParam_
{
  typedef PrarxParam_<ContainerAllocator> Type;

  PrarxParam_()
    : theta1()
    , theta2()
    , eta()
    , scale()  {
    }
  PrarxParam_(const ContainerAllocator& _alloc)
    : theta1(_alloc)
    , theta2(_alloc)
    , eta(_alloc)
    , scale(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _theta1_type;
  _theta1_type theta1;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _theta2_type;
  _theta2_type theta2;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _eta_type;
  _eta_type eta;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _scale_type;
  _scale_type scale;





  typedef boost::shared_ptr< ::cacc_msgs::PrarxParam_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::cacc_msgs::PrarxParam_<ContainerAllocator> const> ConstPtr;

}; // struct PrarxParam_

typedef ::cacc_msgs::PrarxParam_<std::allocator<void> > PrarxParam;

typedef boost::shared_ptr< ::cacc_msgs::PrarxParam > PrarxParamPtr;
typedef boost::shared_ptr< ::cacc_msgs::PrarxParam const> PrarxParamConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::cacc_msgs::PrarxParam_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::cacc_msgs::PrarxParam_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::cacc_msgs::PrarxParam_<ContainerAllocator1> & lhs, const ::cacc_msgs::PrarxParam_<ContainerAllocator2> & rhs)
{
  return lhs.theta1 == rhs.theta1 &&
    lhs.theta2 == rhs.theta2 &&
    lhs.eta == rhs.eta &&
    lhs.scale == rhs.scale;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::cacc_msgs::PrarxParam_<ContainerAllocator1> & lhs, const ::cacc_msgs::PrarxParam_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace cacc_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::cacc_msgs::PrarxParam_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::cacc_msgs::PrarxParam_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::cacc_msgs::PrarxParam_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
{
  static const char* value()
  {
    return "50e5d6a7f9d855220ccc7cbcc9f77398";
  }

  static const char* value(const ::cacc_msgs::PrarxParam_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x50e5d6a7f9d85522ULL;
  static const uint64_t static_value2 = 0x0ccc7cbcc9f77398ULL;
};

template<class ContainerAllocator>
struct DataType< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cacc_msgs/PrarxParam";
  }

  static const char* value(const ::cacc_msgs::PrarxParam_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32[] theta1\n"
"float32[] theta2\n"
"float32[] eta\n"
"float32[] scale\n"
;
  }

  static const char* value(const ::cacc_msgs::PrarxParam_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.theta1);
      stream.next(m.theta2);
      stream.next(m.eta);
      stream.next(m.scale);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PrarxParam_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::cacc_msgs::PrarxParam_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::cacc_msgs::PrarxParam_<ContainerAllocator>& v)
  {
    s << indent << "theta1[]" << std::endl;
    for (size_t i = 0; i < v.theta1.size(); ++i)
    {
      s << indent << "  theta1[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.theta1[i]);
    }
    s << indent << "theta2[]" << std::endl;
    for (size_t i = 0; i < v.theta2.size(); ++i)
    {
      s << indent << "  theta2[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.theta2[i]);
    }
    s << indent << "eta[]" << std::endl;
    for (size_t i = 0; i < v.eta.size(); ++i)
    {
      s << indent << "  eta[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.eta[i]);
    }
    s << indent << "scale[]" << std::endl;
    for (size_t i = 0; i < v.scale.size(); ++i)
    {
      s << indent << "  scale[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.scale[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // CACC_MSGS_MESSAGE_PRARXPARAM_H
