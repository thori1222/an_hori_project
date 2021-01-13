; Auto-generated. Do not edit!


(cl:in-package cacc_msgs-msg)


;//! \htmlinclude CaccMpcState.msg.html

(cl:defclass <CaccMpcState> (roslisp-msg-protocol:ros-message)
  ((F
    :reader F
    :initarg :F
    :type cl:float
    :initform 0.0))
)

(cl:defclass CaccMpcState (<CaccMpcState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CaccMpcState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CaccMpcState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name cacc_msgs-msg:<CaccMpcState> is deprecated: use cacc_msgs-msg:CaccMpcState instead.")))

(cl:ensure-generic-function 'F-val :lambda-list '(m))
(cl:defmethod F-val ((m <CaccMpcState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:F-val is deprecated.  Use cacc_msgs-msg:F instead.")
  (F m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CaccMpcState>) ostream)
  "Serializes a message object of type '<CaccMpcState>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'F))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CaccMpcState>) istream)
  "Deserializes a message object of type '<CaccMpcState>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'F) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CaccMpcState>)))
  "Returns string type for a message object of type '<CaccMpcState>"
  "cacc_msgs/CaccMpcState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CaccMpcState)))
  "Returns string type for a message object of type 'CaccMpcState"
  "cacc_msgs/CaccMpcState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CaccMpcState>)))
  "Returns md5sum for a message object of type '<CaccMpcState>"
  "79de4254f7d72d7dd22d2ce8ed43faa2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CaccMpcState)))
  "Returns md5sum for a message object of type 'CaccMpcState"
  "79de4254f7d72d7dd22d2ce8ed43faa2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CaccMpcState>)))
  "Returns full string definition for message of type '<CaccMpcState>"
  (cl:format cl:nil "float32 F~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CaccMpcState)))
  "Returns full string definition for message of type 'CaccMpcState"
  (cl:format cl:nil "float32 F~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CaccMpcState>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CaccMpcState>))
  "Converts a ROS message object to a list"
  (cl:list 'CaccMpcState
    (cl:cons ':F (F msg))
))
