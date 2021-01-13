; Auto-generated. Do not edit!


(cl:in-package cacc_msgs-msg)


;//! \htmlinclude CaccStatePacket.msg.html

(cl:defclass <CaccStatePacket> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (manual
    :reader manual
    :initarg :manual
    :type cl:boolean
    :initform cl:nil)
   (activated
    :reader activated
    :initarg :activated
    :type cl:boolean
    :initform cl:nil)
   (thw
    :reader thw
    :initarg :thw
    :type cl:float
    :initform 0.0)
   (alpha
    :reader alpha
    :initarg :alpha
    :type cl:float
    :initform 0.0)
   (beta
    :reader beta
    :initarg :beta
    :type cl:float
    :initform 0.0)
   (vel_gain
    :reader vel_gain
    :initarg :vel_gain
    :type cl:fixnum
    :initform 0)
   (vel_gain_low
    :reader vel_gain_low
    :initarg :vel_gain_low
    :type cl:fixnum
    :initform 0)
   (vel_gain_dec
    :reader vel_gain_dec
    :initarg :vel_gain_dec
    :type cl:fixnum
    :initform 0)
   (distance
    :reader distance
    :initarg :distance
    :type cl:float
    :initform 0.0)
   (speed
    :reader speed
    :initarg :speed
    :type cl:float
    :initform 0.0)
   (acceleration
    :reader acceleration
    :initarg :acceleration
    :type cl:float
    :initform 0.0))
)

(cl:defclass CaccStatePacket (<CaccStatePacket>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CaccStatePacket>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CaccStatePacket)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name cacc_msgs-msg:<CaccStatePacket> is deprecated: use cacc_msgs-msg:CaccStatePacket instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:id-val is deprecated.  Use cacc_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'manual-val :lambda-list '(m))
(cl:defmethod manual-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:manual-val is deprecated.  Use cacc_msgs-msg:manual instead.")
  (manual m))

(cl:ensure-generic-function 'activated-val :lambda-list '(m))
(cl:defmethod activated-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:activated-val is deprecated.  Use cacc_msgs-msg:activated instead.")
  (activated m))

(cl:ensure-generic-function 'thw-val :lambda-list '(m))
(cl:defmethod thw-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:thw-val is deprecated.  Use cacc_msgs-msg:thw instead.")
  (thw m))

(cl:ensure-generic-function 'alpha-val :lambda-list '(m))
(cl:defmethod alpha-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:alpha-val is deprecated.  Use cacc_msgs-msg:alpha instead.")
  (alpha m))

(cl:ensure-generic-function 'beta-val :lambda-list '(m))
(cl:defmethod beta-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:beta-val is deprecated.  Use cacc_msgs-msg:beta instead.")
  (beta m))

(cl:ensure-generic-function 'vel_gain-val :lambda-list '(m))
(cl:defmethod vel_gain-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_gain-val is deprecated.  Use cacc_msgs-msg:vel_gain instead.")
  (vel_gain m))

(cl:ensure-generic-function 'vel_gain_low-val :lambda-list '(m))
(cl:defmethod vel_gain_low-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_gain_low-val is deprecated.  Use cacc_msgs-msg:vel_gain_low instead.")
  (vel_gain_low m))

(cl:ensure-generic-function 'vel_gain_dec-val :lambda-list '(m))
(cl:defmethod vel_gain_dec-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_gain_dec-val is deprecated.  Use cacc_msgs-msg:vel_gain_dec instead.")
  (vel_gain_dec m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:distance-val is deprecated.  Use cacc_msgs-msg:distance instead.")
  (distance m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:speed-val is deprecated.  Use cacc_msgs-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <CaccStatePacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:acceleration-val is deprecated.  Use cacc_msgs-msg:acceleration instead.")
  (acceleration m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CaccStatePacket>) ostream)
  "Serializes a message object of type '<CaccStatePacket>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'manual) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'activated) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'thw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'alpha))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'beta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'vel_gain)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'vel_gain_low)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'vel_gain_dec)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CaccStatePacket>) istream)
  "Deserializes a message object of type '<CaccStatePacket>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:slot-value msg 'manual) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'activated) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'thw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'alpha) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'beta) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vel_gain) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vel_gain_low) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vel_gain_dec) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acceleration) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CaccStatePacket>)))
  "Returns string type for a message object of type '<CaccStatePacket>"
  "cacc_msgs/CaccStatePacket")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CaccStatePacket)))
  "Returns string type for a message object of type 'CaccStatePacket"
  "cacc_msgs/CaccStatePacket")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CaccStatePacket>)))
  "Returns md5sum for a message object of type '<CaccStatePacket>"
  "d1e7f03c3be6f5504cfdc21bdc1d3462")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CaccStatePacket)))
  "Returns md5sum for a message object of type 'CaccStatePacket"
  "d1e7f03c3be6f5504cfdc21bdc1d3462")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CaccStatePacket>)))
  "Returns full string definition for message of type '<CaccStatePacket>"
  (cl:format cl:nil "int16 id~%bool manual #1: manual. 0: automated~%bool activated #1: activated, 0: non-activated (ghost-manual)~%#int16 order~%float32 thw~%float32 alpha~%float32 beta~%int16 vel_gain~%int16 vel_gain_low~%int16 vel_gain_dec~%float32 distance~%float32 speed~%float32 acceleration~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CaccStatePacket)))
  "Returns full string definition for message of type 'CaccStatePacket"
  (cl:format cl:nil "int16 id~%bool manual #1: manual. 0: automated~%bool activated #1: activated, 0: non-activated (ghost-manual)~%#int16 order~%float32 thw~%float32 alpha~%float32 beta~%int16 vel_gain~%int16 vel_gain_low~%int16 vel_gain_dec~%float32 distance~%float32 speed~%float32 acceleration~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CaccStatePacket>))
  (cl:+ 0
     2
     1
     1
     4
     4
     4
     2
     2
     2
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CaccStatePacket>))
  "Converts a ROS message object to a list"
  (cl:list 'CaccStatePacket
    (cl:cons ':id (id msg))
    (cl:cons ':manual (manual msg))
    (cl:cons ':activated (activated msg))
    (cl:cons ':thw (thw msg))
    (cl:cons ':alpha (alpha msg))
    (cl:cons ':beta (beta msg))
    (cl:cons ':vel_gain (vel_gain msg))
    (cl:cons ':vel_gain_low (vel_gain_low msg))
    (cl:cons ':vel_gain_dec (vel_gain_dec msg))
    (cl:cons ':distance (distance msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':acceleration (acceleration msg))
))
