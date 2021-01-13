; Auto-generated. Do not edit!


(cl:in-package cacc_msgs-msg)


;//! \htmlinclude CaccSensorPacket.msg.html

(cl:defclass <CaccSensorPacket> (roslisp-msg-protocol:ros-message)
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
   (sensor2frontbumper
    :reader sensor2frontbumper
    :initarg :sensor2frontbumper
    :type cl:float
    :initform 0.0)
   (sensor2rearbumper
    :reader sensor2rearbumper
    :initarg :sensor2rearbumper
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
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (u
    :reader u
    :initarg :u
    :type cl:float
    :initform 0.0)
   (v
    :reader v
    :initarg :v
    :type cl:float
    :initform 0.0)
   (yaw
    :reader yaw
    :initarg :yaw
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
    :initform 0.0)
   (front_x
    :reader front_x
    :initarg :front_x
    :type cl:float
    :initform 0.0)
   (front_y
    :reader front_y
    :initarg :front_y
    :type cl:float
    :initform 0.0)
   (front_u
    :reader front_u
    :initarg :front_u
    :type cl:float
    :initform 0.0)
   (front_v
    :reader front_v
    :initarg :front_v
    :type cl:float
    :initform 0.0)
   (front_yaw
    :reader front_yaw
    :initarg :front_yaw
    :type cl:float
    :initform 0.0)
   (front_speed
    :reader front_speed
    :initarg :front_speed
    :type cl:float
    :initform 0.0)
   (front_acceleration
    :reader front_acceleration
    :initarg :front_acceleration
    :type cl:float
    :initform 0.0)
   (front_distance
    :reader front_distance
    :initarg :front_distance
    :type cl:float
    :initform 0.0)
   (rear_x
    :reader rear_x
    :initarg :rear_x
    :type cl:float
    :initform 0.0)
   (rear_y
    :reader rear_y
    :initarg :rear_y
    :type cl:float
    :initform 0.0)
   (rear_u
    :reader rear_u
    :initarg :rear_u
    :type cl:float
    :initform 0.0)
   (rear_v
    :reader rear_v
    :initarg :rear_v
    :type cl:float
    :initform 0.0)
   (rear_yaw
    :reader rear_yaw
    :initarg :rear_yaw
    :type cl:float
    :initform 0.0)
   (rear_speed
    :reader rear_speed
    :initarg :rear_speed
    :type cl:float
    :initform 0.0)
   (rear_acceleration
    :reader rear_acceleration
    :initarg :rear_acceleration
    :type cl:float
    :initform 0.0)
   (rear_distance
    :reader rear_distance
    :initarg :rear_distance
    :type cl:float
    :initform 0.0)
   (checksum
    :reader checksum
    :initarg :checksum
    :type cl:integer
    :initform 0))
)

(cl:defclass CaccSensorPacket (<CaccSensorPacket>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CaccSensorPacket>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CaccSensorPacket)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name cacc_msgs-msg:<CaccSensorPacket> is deprecated: use cacc_msgs-msg:CaccSensorPacket instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:id-val is deprecated.  Use cacc_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'manual-val :lambda-list '(m))
(cl:defmethod manual-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:manual-val is deprecated.  Use cacc_msgs-msg:manual instead.")
  (manual m))

(cl:ensure-generic-function 'thw-val :lambda-list '(m))
(cl:defmethod thw-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:thw-val is deprecated.  Use cacc_msgs-msg:thw instead.")
  (thw m))

(cl:ensure-generic-function 'alpha-val :lambda-list '(m))
(cl:defmethod alpha-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:alpha-val is deprecated.  Use cacc_msgs-msg:alpha instead.")
  (alpha m))

(cl:ensure-generic-function 'beta-val :lambda-list '(m))
(cl:defmethod beta-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:beta-val is deprecated.  Use cacc_msgs-msg:beta instead.")
  (beta m))

(cl:ensure-generic-function 'sensor2frontbumper-val :lambda-list '(m))
(cl:defmethod sensor2frontbumper-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:sensor2frontbumper-val is deprecated.  Use cacc_msgs-msg:sensor2frontbumper instead.")
  (sensor2frontbumper m))

(cl:ensure-generic-function 'sensor2rearbumper-val :lambda-list '(m))
(cl:defmethod sensor2rearbumper-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:sensor2rearbumper-val is deprecated.  Use cacc_msgs-msg:sensor2rearbumper instead.")
  (sensor2rearbumper m))

(cl:ensure-generic-function 'vel_gain-val :lambda-list '(m))
(cl:defmethod vel_gain-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_gain-val is deprecated.  Use cacc_msgs-msg:vel_gain instead.")
  (vel_gain m))

(cl:ensure-generic-function 'vel_gain_low-val :lambda-list '(m))
(cl:defmethod vel_gain_low-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_gain_low-val is deprecated.  Use cacc_msgs-msg:vel_gain_low instead.")
  (vel_gain_low m))

(cl:ensure-generic-function 'vel_gain_dec-val :lambda-list '(m))
(cl:defmethod vel_gain_dec-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:vel_gain_dec-val is deprecated.  Use cacc_msgs-msg:vel_gain_dec instead.")
  (vel_gain_dec m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:x-val is deprecated.  Use cacc_msgs-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:y-val is deprecated.  Use cacc_msgs-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'u-val :lambda-list '(m))
(cl:defmethod u-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:u-val is deprecated.  Use cacc_msgs-msg:u instead.")
  (u m))

(cl:ensure-generic-function 'v-val :lambda-list '(m))
(cl:defmethod v-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:v-val is deprecated.  Use cacc_msgs-msg:v instead.")
  (v m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:yaw-val is deprecated.  Use cacc_msgs-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:speed-val is deprecated.  Use cacc_msgs-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:acceleration-val is deprecated.  Use cacc_msgs-msg:acceleration instead.")
  (acceleration m))

(cl:ensure-generic-function 'front_x-val :lambda-list '(m))
(cl:defmethod front_x-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_x-val is deprecated.  Use cacc_msgs-msg:front_x instead.")
  (front_x m))

(cl:ensure-generic-function 'front_y-val :lambda-list '(m))
(cl:defmethod front_y-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_y-val is deprecated.  Use cacc_msgs-msg:front_y instead.")
  (front_y m))

(cl:ensure-generic-function 'front_u-val :lambda-list '(m))
(cl:defmethod front_u-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_u-val is deprecated.  Use cacc_msgs-msg:front_u instead.")
  (front_u m))

(cl:ensure-generic-function 'front_v-val :lambda-list '(m))
(cl:defmethod front_v-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_v-val is deprecated.  Use cacc_msgs-msg:front_v instead.")
  (front_v m))

(cl:ensure-generic-function 'front_yaw-val :lambda-list '(m))
(cl:defmethod front_yaw-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_yaw-val is deprecated.  Use cacc_msgs-msg:front_yaw instead.")
  (front_yaw m))

(cl:ensure-generic-function 'front_speed-val :lambda-list '(m))
(cl:defmethod front_speed-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_speed-val is deprecated.  Use cacc_msgs-msg:front_speed instead.")
  (front_speed m))

(cl:ensure-generic-function 'front_acceleration-val :lambda-list '(m))
(cl:defmethod front_acceleration-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_acceleration-val is deprecated.  Use cacc_msgs-msg:front_acceleration instead.")
  (front_acceleration m))

(cl:ensure-generic-function 'front_distance-val :lambda-list '(m))
(cl:defmethod front_distance-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:front_distance-val is deprecated.  Use cacc_msgs-msg:front_distance instead.")
  (front_distance m))

(cl:ensure-generic-function 'rear_x-val :lambda-list '(m))
(cl:defmethod rear_x-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_x-val is deprecated.  Use cacc_msgs-msg:rear_x instead.")
  (rear_x m))

(cl:ensure-generic-function 'rear_y-val :lambda-list '(m))
(cl:defmethod rear_y-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_y-val is deprecated.  Use cacc_msgs-msg:rear_y instead.")
  (rear_y m))

(cl:ensure-generic-function 'rear_u-val :lambda-list '(m))
(cl:defmethod rear_u-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_u-val is deprecated.  Use cacc_msgs-msg:rear_u instead.")
  (rear_u m))

(cl:ensure-generic-function 'rear_v-val :lambda-list '(m))
(cl:defmethod rear_v-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_v-val is deprecated.  Use cacc_msgs-msg:rear_v instead.")
  (rear_v m))

(cl:ensure-generic-function 'rear_yaw-val :lambda-list '(m))
(cl:defmethod rear_yaw-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_yaw-val is deprecated.  Use cacc_msgs-msg:rear_yaw instead.")
  (rear_yaw m))

(cl:ensure-generic-function 'rear_speed-val :lambda-list '(m))
(cl:defmethod rear_speed-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_speed-val is deprecated.  Use cacc_msgs-msg:rear_speed instead.")
  (rear_speed m))

(cl:ensure-generic-function 'rear_acceleration-val :lambda-list '(m))
(cl:defmethod rear_acceleration-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_acceleration-val is deprecated.  Use cacc_msgs-msg:rear_acceleration instead.")
  (rear_acceleration m))

(cl:ensure-generic-function 'rear_distance-val :lambda-list '(m))
(cl:defmethod rear_distance-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:rear_distance-val is deprecated.  Use cacc_msgs-msg:rear_distance instead.")
  (rear_distance m))

(cl:ensure-generic-function 'checksum-val :lambda-list '(m))
(cl:defmethod checksum-val ((m <CaccSensorPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:checksum-val is deprecated.  Use cacc_msgs-msg:checksum instead.")
  (checksum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CaccSensorPacket>) ostream)
  "Serializes a message object of type '<CaccSensorPacket>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'manual) 1 0)) ostream)
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sensor2frontbumper))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sensor2rearbumper))))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'u))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_u))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front_distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_u))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rear_distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'checksum)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'checksum)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'checksum)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'checksum)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CaccSensorPacket>) istream)
  "Deserializes a message object of type '<CaccSensorPacket>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:slot-value msg 'manual) (cl:not (cl:zerop (cl:read-byte istream))))
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sensor2frontbumper) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sensor2rearbumper) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'u) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'v) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acceleration) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_u) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_v) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_acceleration) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front_distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_u) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_v) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_acceleration) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rear_distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'checksum)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CaccSensorPacket>)))
  "Returns string type for a message object of type '<CaccSensorPacket>"
  "cacc_msgs/CaccSensorPacket")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CaccSensorPacket)))
  "Returns string type for a message object of type 'CaccSensorPacket"
  "cacc_msgs/CaccSensorPacket")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CaccSensorPacket>)))
  "Returns md5sum for a message object of type '<CaccSensorPacket>"
  "53f6fd0b756b85940b07ea746c26c901")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CaccSensorPacket)))
  "Returns md5sum for a message object of type 'CaccSensorPacket"
  "53f6fd0b756b85940b07ea746c26c901")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CaccSensorPacket>)))
  "Returns full string definition for message of type '<CaccSensorPacket>"
  (cl:format cl:nil "#Header Header~%~%int16 id~%bool manual #1: manual. 0: automated~%float32 thw~%float32 alpha~%float32 beta~%float32 sensor2frontbumper~%float32 sensor2rearbumper~%int16 vel_gain~%int16 vel_gain_low~%int16 vel_gain_dec~%~%#ego car~%float32 x~%float32 y~%float32 u~%float32 v~%float32 yaw~%float32 speed~%float32 acceleration~%~%#front car~%float32 front_x~%float32 front_y~%float32 front_u~%float32 front_v~%float32 front_yaw~%float32 front_speed~%float32 front_acceleration~%float32 front_distance~%~%#rear car~%float32 rear_x~%float32 rear_y~%float32 rear_u~%float32 rear_v~%float32 rear_yaw~%float32 rear_speed~%float32 rear_acceleration~%float32 rear_distance~%~%uint32 checksum~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CaccSensorPacket)))
  "Returns full string definition for message of type 'CaccSensorPacket"
  (cl:format cl:nil "#Header Header~%~%int16 id~%bool manual #1: manual. 0: automated~%float32 thw~%float32 alpha~%float32 beta~%float32 sensor2frontbumper~%float32 sensor2rearbumper~%int16 vel_gain~%int16 vel_gain_low~%int16 vel_gain_dec~%~%#ego car~%float32 x~%float32 y~%float32 u~%float32 v~%float32 yaw~%float32 speed~%float32 acceleration~%~%#front car~%float32 front_x~%float32 front_y~%float32 front_u~%float32 front_v~%float32 front_yaw~%float32 front_speed~%float32 front_acceleration~%float32 front_distance~%~%#rear car~%float32 rear_x~%float32 rear_y~%float32 rear_u~%float32 rear_v~%float32 rear_yaw~%float32 rear_speed~%float32 rear_acceleration~%float32 rear_distance~%~%uint32 checksum~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CaccSensorPacket>))
  (cl:+ 0
     2
     1
     4
     4
     4
     4
     4
     2
     2
     2
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CaccSensorPacket>))
  "Converts a ROS message object to a list"
  (cl:list 'CaccSensorPacket
    (cl:cons ':id (id msg))
    (cl:cons ':manual (manual msg))
    (cl:cons ':thw (thw msg))
    (cl:cons ':alpha (alpha msg))
    (cl:cons ':beta (beta msg))
    (cl:cons ':sensor2frontbumper (sensor2frontbumper msg))
    (cl:cons ':sensor2rearbumper (sensor2rearbumper msg))
    (cl:cons ':vel_gain (vel_gain msg))
    (cl:cons ':vel_gain_low (vel_gain_low msg))
    (cl:cons ':vel_gain_dec (vel_gain_dec msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':u (u msg))
    (cl:cons ':v (v msg))
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':acceleration (acceleration msg))
    (cl:cons ':front_x (front_x msg))
    (cl:cons ':front_y (front_y msg))
    (cl:cons ':front_u (front_u msg))
    (cl:cons ':front_v (front_v msg))
    (cl:cons ':front_yaw (front_yaw msg))
    (cl:cons ':front_speed (front_speed msg))
    (cl:cons ':front_acceleration (front_acceleration msg))
    (cl:cons ':front_distance (front_distance msg))
    (cl:cons ':rear_x (rear_x msg))
    (cl:cons ':rear_y (rear_y msg))
    (cl:cons ':rear_u (rear_u msg))
    (cl:cons ':rear_v (rear_v msg))
    (cl:cons ':rear_yaw (rear_yaw msg))
    (cl:cons ':rear_speed (rear_speed msg))
    (cl:cons ':rear_acceleration (rear_acceleration msg))
    (cl:cons ':rear_distance (rear_distance msg))
    (cl:cons ':checksum (checksum msg))
))
