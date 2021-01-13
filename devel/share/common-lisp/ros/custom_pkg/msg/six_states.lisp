; Auto-generated. Do not edit!


(cl:in-package custom_pkg-msg)


;//! \htmlinclude six_states.msg.html

(cl:defclass <six_states> (roslisp-msg-protocol:ros-message)
  ((X
    :reader X
    :initarg :X
    :type cl:float
    :initform 0.0)
   (Y
    :reader Y
    :initarg :Y
    :type cl:float
    :initform 0.0)
   (yaw
    :reader yaw
    :initarg :yaw
    :type cl:float
    :initform 0.0)
   (vx
    :reader vx
    :initarg :vx
    :type cl:float
    :initform 0.0)
   (vy
    :reader vy
    :initarg :vy
    :type cl:float
    :initform 0.0)
   (yr
    :reader yr
    :initarg :yr
    :type cl:float
    :initform 0.0))
)

(cl:defclass six_states (<six_states>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <six_states>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'six_states)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name custom_pkg-msg:<six_states> is deprecated: use custom_pkg-msg:six_states instead.")))

(cl:ensure-generic-function 'X-val :lambda-list '(m))
(cl:defmethod X-val ((m <six_states>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:X-val is deprecated.  Use custom_pkg-msg:X instead.")
  (X m))

(cl:ensure-generic-function 'Y-val :lambda-list '(m))
(cl:defmethod Y-val ((m <six_states>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:Y-val is deprecated.  Use custom_pkg-msg:Y instead.")
  (Y m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <six_states>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:yaw-val is deprecated.  Use custom_pkg-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'vx-val :lambda-list '(m))
(cl:defmethod vx-val ((m <six_states>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:vx-val is deprecated.  Use custom_pkg-msg:vx instead.")
  (vx m))

(cl:ensure-generic-function 'vy-val :lambda-list '(m))
(cl:defmethod vy-val ((m <six_states>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:vy-val is deprecated.  Use custom_pkg-msg:vy instead.")
  (vy m))

(cl:ensure-generic-function 'yr-val :lambda-list '(m))
(cl:defmethod yr-val ((m <six_states>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader custom_pkg-msg:yr-val is deprecated.  Use custom_pkg-msg:yr instead.")
  (yr m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <six_states>) ostream)
  "Serializes a message object of type '<six_states>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'X))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yr))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <six_states>) istream)
  "Deserializes a message object of type '<six_states>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'X) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yr) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<six_states>)))
  "Returns string type for a message object of type '<six_states>"
  "custom_pkg/six_states")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'six_states)))
  "Returns string type for a message object of type 'six_states"
  "custom_pkg/six_states")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<six_states>)))
  "Returns md5sum for a message object of type '<six_states>"
  "df2621eb80c5f027459612d1c5297bf8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'six_states)))
  "Returns md5sum for a message object of type 'six_states"
  "df2621eb80c5f027459612d1c5297bf8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<six_states>)))
  "Returns full string definition for message of type '<six_states>"
  (cl:format cl:nil "# This is a message to hold data for six system states~%# X[m] Y[m] yaw angle[rad] vx[m/s] vy[m/s] yaw rate[rad/s]~%float32 X ~%float32 Y~%float32 yaw~%float32 vx~%float32 vy~%float32 yr~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'six_states)))
  "Returns full string definition for message of type 'six_states"
  (cl:format cl:nil "# This is a message to hold data for six system states~%# X[m] Y[m] yaw angle[rad] vx[m/s] vy[m/s] yaw rate[rad/s]~%float32 X ~%float32 Y~%float32 yaw~%float32 vx~%float32 vy~%float32 yr~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <six_states>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <six_states>))
  "Converts a ROS message object to a list"
  (cl:list 'six_states
    (cl:cons ':X (X msg))
    (cl:cons ':Y (Y msg))
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':vx (vx msg))
    (cl:cons ':vy (vy msg))
    (cl:cons ':yr (yr msg))
))
