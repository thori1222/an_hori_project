; Auto-generated. Do not edit!


(cl:in-package cacc_msgs-msg)


;//! \htmlinclude CaccControlPacket.msg.html

(cl:defclass <CaccControlPacket> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (vel_ref
    :reader vel_ref
    :initarg :vel_ref
    :type cl:float
    :initform 0.0)
   (acc_ref
    :reader acc_ref
    :initarg :acc_ref
    :type cl:float
    :initform 0.0)
   (checksum
    :reader checksum
    :initarg :checksum
    :type cl:integer
    :initform 0))
)

(cl:defclass CaccControlPacket (<CaccControlPacket>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CaccControlPacket>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CaccControlPacket)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name cacc_msgs-msg:<CaccControlPacket> is deprecated: use cacc_msgs-msg:CaccControlPacket instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <CaccControlPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:id-val is deprecated.  Use cacc_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'vel_ref-val :lambda-list '(m))
(cl:defmethod vel_ref-val ((m <CaccControlPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_ref-val is deprecated.  Use cacc_msgs-msg:vel_ref instead.")
  (vel_ref m))

(cl:ensure-generic-function 'acc_ref-val :lambda-list '(m))
(cl:defmethod acc_ref-val ((m <CaccControlPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:acc_ref-val is deprecated.  Use cacc_msgs-msg:acc_ref instead.")
  (acc_ref m))

(cl:ensure-generic-function 'checksum-val :lambda-list '(m))
(cl:defmethod checksum-val ((m <CaccControlPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:checksum-val is deprecated.  Use cacc_msgs-msg:checksum instead.")
  (checksum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CaccControlPacket>) ostream)
  "Serializes a message object of type '<CaccControlPacket>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel_ref))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acc_ref))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'checksum)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'checksum)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'checksum)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'checksum)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CaccControlPacket>) istream)
  "Deserializes a message object of type '<CaccControlPacket>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel_ref) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acc_ref) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CaccControlPacket>)))
  "Returns string type for a message object of type '<CaccControlPacket>"
  "cacc_msgs/CaccControlPacket")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CaccControlPacket)))
  "Returns string type for a message object of type 'CaccControlPacket"
  "cacc_msgs/CaccControlPacket")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CaccControlPacket>)))
  "Returns md5sum for a message object of type '<CaccControlPacket>"
  "ca73aaf0f9afa68bd8dfa673d8298a2c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CaccControlPacket)))
  "Returns md5sum for a message object of type 'CaccControlPacket"
  "ca73aaf0f9afa68bd8dfa673d8298a2c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CaccControlPacket>)))
  "Returns full string definition for message of type '<CaccControlPacket>"
  (cl:format cl:nil "int16 id~%float32 vel_ref~%float32 acc_ref~%~%uint32 checksum~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CaccControlPacket)))
  "Returns full string definition for message of type 'CaccControlPacket"
  (cl:format cl:nil "int16 id~%float32 vel_ref~%float32 acc_ref~%~%uint32 checksum~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CaccControlPacket>))
  (cl:+ 0
     2
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CaccControlPacket>))
  "Converts a ROS message object to a list"
  (cl:list 'CaccControlPacket
    (cl:cons ':id (id msg))
    (cl:cons ':vel_ref (vel_ref msg))
    (cl:cons ':acc_ref (acc_ref msg))
    (cl:cons ':checksum (checksum msg))
))
