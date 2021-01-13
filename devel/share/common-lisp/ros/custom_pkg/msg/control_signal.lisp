; Auto-generated. Do not edit!


(cl:in-package custom_pkg-msg)


;//! \htmlinclude control_signal.msg.html

(cl:defclass <control_signal> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (accel
    :reader accel
    :initarg :accel
    :type cl:float
    :initform 0.0)
   (steer
    :reader steer
    :initarg :steer
    :type cl:float
    :initform 0.0)
   (status
    :reader status
    :initarg :status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass control_signal (<control_signal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <control_signal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'control_signal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name custom_pkg-msg:<control_signal> is deprecated: use custom_pkg-msg:control_signal instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <control_signal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:header-val is deprecated.  Use custom_pkg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'accel-val :lambda-list '(m))
(cl:defmethod accel-val ((m <control_signal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:accel-val is deprecated.  Use custom_pkg-msg:accel instead.")
  (accel m))

(cl:ensure-generic-function 'steer-val :lambda-list '(m))
(cl:defmethod steer-val ((m <control_signal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:steer-val is deprecated.  Use custom_pkg-msg:steer instead.")
  (steer m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <control_signal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:status-val is deprecated.  Use custom_pkg-msg:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <control_signal>) ostream)
  "Serializes a message object of type '<control_signal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'accel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steer))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <control_signal>) istream)
  "Deserializes a message object of type '<control_signal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'accel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steer) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'status) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<control_signal>)))
  "Returns string type for a message object of type '<control_signal>"
  "custom_pkg/control_signal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'control_signal)))
  "Returns string type for a message object of type 'control_signal"
  "custom_pkg/control_signal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<control_signal>)))
  "Returns md5sum for a message object of type '<control_signal>"
  "da55517947a600b569ad9bc4fd50c76b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'control_signal)))
  "Returns md5sum for a message object of type 'control_signal"
  "da55517947a600b569ad9bc4fd50c76b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<control_signal>)))
  "Returns full string definition for message of type '<control_signal>"
  (cl:format cl:nil "Header header~%float32 accel~%float32 steer~%int8 status~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'control_signal)))
  "Returns full string definition for message of type 'control_signal"
  (cl:format cl:nil "Header header~%float32 accel~%float32 steer~%int8 status~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <control_signal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <control_signal>))
  "Converts a ROS message object to a list"
  (cl:list 'control_signal
    (cl:cons ':header (header msg))
    (cl:cons ':accel (accel msg))
    (cl:cons ':steer (steer msg))
    (cl:cons ':status (status msg))
))
