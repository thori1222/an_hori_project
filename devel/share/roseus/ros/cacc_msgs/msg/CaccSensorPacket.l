;; Auto-generated. Do not edit!


(when (boundp 'cacc_msgs::CaccSensorPacket)
  (if (not (find-package "CACC_MSGS"))
    (make-package "CACC_MSGS"))
  (shadow 'CaccSensorPacket (find-package "CACC_MSGS")))
(unless (find-package "CACC_MSGS::CACCSENSORPACKET")
  (make-package "CACC_MSGS::CACCSENSORPACKET"))

(in-package "ROS")
;;//! \htmlinclude CaccSensorPacket.msg.html


(defclass cacc_msgs::CaccSensorPacket
  :super ros::object
  :slots (_id _manual _thw _alpha _beta _sensor2frontbumper _sensor2rearbumper _vel_gain _vel_gain_low _vel_gain_dec _x _y _u _v _yaw _speed _acceleration _front_x _front_y _front_u _front_v _front_yaw _front_speed _front_acceleration _front_distance _rear_x _rear_y _rear_u _rear_v _rear_yaw _rear_speed _rear_acceleration _rear_distance _checksum ))

(defmethod cacc_msgs::CaccSensorPacket
  (:init
   (&key
    ((:id __id) 0)
    ((:manual __manual) nil)
    ((:thw __thw) 0.0)
    ((:alpha __alpha) 0.0)
    ((:beta __beta) 0.0)
    ((:sensor2frontbumper __sensor2frontbumper) 0.0)
    ((:sensor2rearbumper __sensor2rearbumper) 0.0)
    ((:vel_gain __vel_gain) 0)
    ((:vel_gain_low __vel_gain_low) 0)
    ((:vel_gain_dec __vel_gain_dec) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:u __u) 0.0)
    ((:v __v) 0.0)
    ((:yaw __yaw) 0.0)
    ((:speed __speed) 0.0)
    ((:acceleration __acceleration) 0.0)
    ((:front_x __front_x) 0.0)
    ((:front_y __front_y) 0.0)
    ((:front_u __front_u) 0.0)
    ((:front_v __front_v) 0.0)
    ((:front_yaw __front_yaw) 0.0)
    ((:front_speed __front_speed) 0.0)
    ((:front_acceleration __front_acceleration) 0.0)
    ((:front_distance __front_distance) 0.0)
    ((:rear_x __rear_x) 0.0)
    ((:rear_y __rear_y) 0.0)
    ((:rear_u __rear_u) 0.0)
    ((:rear_v __rear_v) 0.0)
    ((:rear_yaw __rear_yaw) 0.0)
    ((:rear_speed __rear_speed) 0.0)
    ((:rear_acceleration __rear_acceleration) 0.0)
    ((:rear_distance __rear_distance) 0.0)
    ((:checksum __checksum) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _manual __manual)
   (setq _thw (float __thw))
   (setq _alpha (float __alpha))
   (setq _beta (float __beta))
   (setq _sensor2frontbumper (float __sensor2frontbumper))
   (setq _sensor2rearbumper (float __sensor2rearbumper))
   (setq _vel_gain (round __vel_gain))
   (setq _vel_gain_low (round __vel_gain_low))
   (setq _vel_gain_dec (round __vel_gain_dec))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _u (float __u))
   (setq _v (float __v))
   (setq _yaw (float __yaw))
   (setq _speed (float __speed))
   (setq _acceleration (float __acceleration))
   (setq _front_x (float __front_x))
   (setq _front_y (float __front_y))
   (setq _front_u (float __front_u))
   (setq _front_v (float __front_v))
   (setq _front_yaw (float __front_yaw))
   (setq _front_speed (float __front_speed))
   (setq _front_acceleration (float __front_acceleration))
   (setq _front_distance (float __front_distance))
   (setq _rear_x (float __rear_x))
   (setq _rear_y (float __rear_y))
   (setq _rear_u (float __rear_u))
   (setq _rear_v (float __rear_v))
   (setq _rear_yaw (float __rear_yaw))
   (setq _rear_speed (float __rear_speed))
   (setq _rear_acceleration (float __rear_acceleration))
   (setq _rear_distance (float __rear_distance))
   (setq _checksum (round __checksum))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:manual
   (&optional __manual)
   (if __manual (setq _manual __manual)) _manual)
  (:thw
   (&optional __thw)
   (if __thw (setq _thw __thw)) _thw)
  (:alpha
   (&optional __alpha)
   (if __alpha (setq _alpha __alpha)) _alpha)
  (:beta
   (&optional __beta)
   (if __beta (setq _beta __beta)) _beta)
  (:sensor2frontbumper
   (&optional __sensor2frontbumper)
   (if __sensor2frontbumper (setq _sensor2frontbumper __sensor2frontbumper)) _sensor2frontbumper)
  (:sensor2rearbumper
   (&optional __sensor2rearbumper)
   (if __sensor2rearbumper (setq _sensor2rearbumper __sensor2rearbumper)) _sensor2rearbumper)
  (:vel_gain
   (&optional __vel_gain)
   (if __vel_gain (setq _vel_gain __vel_gain)) _vel_gain)
  (:vel_gain_low
   (&optional __vel_gain_low)
   (if __vel_gain_low (setq _vel_gain_low __vel_gain_low)) _vel_gain_low)
  (:vel_gain_dec
   (&optional __vel_gain_dec)
   (if __vel_gain_dec (setq _vel_gain_dec __vel_gain_dec)) _vel_gain_dec)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:u
   (&optional __u)
   (if __u (setq _u __u)) _u)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:acceleration
   (&optional __acceleration)
   (if __acceleration (setq _acceleration __acceleration)) _acceleration)
  (:front_x
   (&optional __front_x)
   (if __front_x (setq _front_x __front_x)) _front_x)
  (:front_y
   (&optional __front_y)
   (if __front_y (setq _front_y __front_y)) _front_y)
  (:front_u
   (&optional __front_u)
   (if __front_u (setq _front_u __front_u)) _front_u)
  (:front_v
   (&optional __front_v)
   (if __front_v (setq _front_v __front_v)) _front_v)
  (:front_yaw
   (&optional __front_yaw)
   (if __front_yaw (setq _front_yaw __front_yaw)) _front_yaw)
  (:front_speed
   (&optional __front_speed)
   (if __front_speed (setq _front_speed __front_speed)) _front_speed)
  (:front_acceleration
   (&optional __front_acceleration)
   (if __front_acceleration (setq _front_acceleration __front_acceleration)) _front_acceleration)
  (:front_distance
   (&optional __front_distance)
   (if __front_distance (setq _front_distance __front_distance)) _front_distance)
  (:rear_x
   (&optional __rear_x)
   (if __rear_x (setq _rear_x __rear_x)) _rear_x)
  (:rear_y
   (&optional __rear_y)
   (if __rear_y (setq _rear_y __rear_y)) _rear_y)
  (:rear_u
   (&optional __rear_u)
   (if __rear_u (setq _rear_u __rear_u)) _rear_u)
  (:rear_v
   (&optional __rear_v)
   (if __rear_v (setq _rear_v __rear_v)) _rear_v)
  (:rear_yaw
   (&optional __rear_yaw)
   (if __rear_yaw (setq _rear_yaw __rear_yaw)) _rear_yaw)
  (:rear_speed
   (&optional __rear_speed)
   (if __rear_speed (setq _rear_speed __rear_speed)) _rear_speed)
  (:rear_acceleration
   (&optional __rear_acceleration)
   (if __rear_acceleration (setq _rear_acceleration __rear_acceleration)) _rear_acceleration)
  (:rear_distance
   (&optional __rear_distance)
   (if __rear_distance (setq _rear_distance __rear_distance)) _rear_distance)
  (:checksum
   (&optional __checksum)
   (if __checksum (setq _checksum __checksum)) _checksum)
  (:serialization-length
   ()
   (+
    ;; int16 _id
    2
    ;; bool _manual
    1
    ;; float32 _thw
    4
    ;; float32 _alpha
    4
    ;; float32 _beta
    4
    ;; float32 _sensor2frontbumper
    4
    ;; float32 _sensor2rearbumper
    4
    ;; int16 _vel_gain
    2
    ;; int16 _vel_gain_low
    2
    ;; int16 _vel_gain_dec
    2
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _u
    4
    ;; float32 _v
    4
    ;; float32 _yaw
    4
    ;; float32 _speed
    4
    ;; float32 _acceleration
    4
    ;; float32 _front_x
    4
    ;; float32 _front_y
    4
    ;; float32 _front_u
    4
    ;; float32 _front_v
    4
    ;; float32 _front_yaw
    4
    ;; float32 _front_speed
    4
    ;; float32 _front_acceleration
    4
    ;; float32 _front_distance
    4
    ;; float32 _rear_x
    4
    ;; float32 _rear_y
    4
    ;; float32 _rear_u
    4
    ;; float32 _rear_v
    4
    ;; float32 _rear_yaw
    4
    ;; float32 _rear_speed
    4
    ;; float32 _rear_acceleration
    4
    ;; float32 _rear_distance
    4
    ;; uint32 _checksum
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _id
       (write-word _id s)
     ;; bool _manual
       (if _manual (write-byte -1 s) (write-byte 0 s))
     ;; float32 _thw
       (sys::poke _thw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _alpha
       (sys::poke _alpha (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _beta
       (sys::poke _beta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _sensor2frontbumper
       (sys::poke _sensor2frontbumper (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _sensor2rearbumper
       (sys::poke _sensor2rearbumper (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int16 _vel_gain
       (write-word _vel_gain s)
     ;; int16 _vel_gain_low
       (write-word _vel_gain_low s)
     ;; int16 _vel_gain_dec
       (write-word _vel_gain_dec s)
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _u
       (sys::poke _u (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _v
       (sys::poke _v (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acceleration
       (sys::poke _acceleration (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_x
       (sys::poke _front_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_y
       (sys::poke _front_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_u
       (sys::poke _front_u (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_v
       (sys::poke _front_v (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_yaw
       (sys::poke _front_yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_speed
       (sys::poke _front_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_acceleration
       (sys::poke _front_acceleration (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _front_distance
       (sys::poke _front_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_x
       (sys::poke _rear_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_y
       (sys::poke _rear_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_u
       (sys::poke _rear_u (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_v
       (sys::poke _rear_v (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_yaw
       (sys::poke _rear_yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_speed
       (sys::poke _rear_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_acceleration
       (sys::poke _rear_acceleration (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rear_distance
       (sys::poke _rear_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _checksum
       (write-long _checksum s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _id
     (setq _id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; bool _manual
     (setq _manual (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _thw
     (setq _thw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _alpha
     (setq _alpha (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _beta
     (setq _beta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _sensor2frontbumper
     (setq _sensor2frontbumper (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _sensor2rearbumper
     (setq _sensor2rearbumper (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int16 _vel_gain
     (setq _vel_gain (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _vel_gain_low
     (setq _vel_gain_low (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _vel_gain_dec
     (setq _vel_gain_dec (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _u
     (setq _u (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _v
     (setq _v (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acceleration
     (setq _acceleration (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_x
     (setq _front_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_y
     (setq _front_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_u
     (setq _front_u (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_v
     (setq _front_v (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_yaw
     (setq _front_yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_speed
     (setq _front_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_acceleration
     (setq _front_acceleration (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _front_distance
     (setq _front_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_x
     (setq _rear_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_y
     (setq _rear_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_u
     (setq _rear_u (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_v
     (setq _rear_v (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_yaw
     (setq _rear_yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_speed
     (setq _rear_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_acceleration
     (setq _rear_acceleration (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rear_distance
     (setq _rear_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _checksum
     (setq _checksum (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get cacc_msgs::CaccSensorPacket :md5sum-) "53f6fd0b756b85940b07ea746c26c901")
(setf (get cacc_msgs::CaccSensorPacket :datatype-) "cacc_msgs/CaccSensorPacket")
(setf (get cacc_msgs::CaccSensorPacket :definition-)
      "#Header Header

int16 id
bool manual #1: manual. 0: automated
float32 thw
float32 alpha
float32 beta
float32 sensor2frontbumper
float32 sensor2rearbumper
int16 vel_gain
int16 vel_gain_low
int16 vel_gain_dec

#ego car
float32 x
float32 y
float32 u
float32 v
float32 yaw
float32 speed
float32 acceleration

#front car
float32 front_x
float32 front_y
float32 front_u
float32 front_v
float32 front_yaw
float32 front_speed
float32 front_acceleration
float32 front_distance

#rear car
float32 rear_x
float32 rear_y
float32 rear_u
float32 rear_v
float32 rear_yaw
float32 rear_speed
float32 rear_acceleration
float32 rear_distance

uint32 checksum
")



(provide :cacc_msgs/CaccSensorPacket "53f6fd0b756b85940b07ea746c26c901")


