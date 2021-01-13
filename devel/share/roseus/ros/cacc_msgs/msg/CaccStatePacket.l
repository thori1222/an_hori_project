;; Auto-generated. Do not edit!


(when (boundp 'cacc_msgs::CaccStatePacket)
  (if (not (find-package "CACC_MSGS"))
    (make-package "CACC_MSGS"))
  (shadow 'CaccStatePacket (find-package "CACC_MSGS")))
(unless (find-package "CACC_MSGS::CACCSTATEPACKET")
  (make-package "CACC_MSGS::CACCSTATEPACKET"))

(in-package "ROS")
;;//! \htmlinclude CaccStatePacket.msg.html


(defclass cacc_msgs::CaccStatePacket
  :super ros::object
  :slots (_id _manual _activated _thw _alpha _beta _vel_gain _vel_gain_low _vel_gain_dec _distance _speed _acceleration ))

(defmethod cacc_msgs::CaccStatePacket
  (:init
   (&key
    ((:id __id) 0)
    ((:manual __manual) nil)
    ((:activated __activated) nil)
    ((:thw __thw) 0.0)
    ((:alpha __alpha) 0.0)
    ((:beta __beta) 0.0)
    ((:vel_gain __vel_gain) 0)
    ((:vel_gain_low __vel_gain_low) 0)
    ((:vel_gain_dec __vel_gain_dec) 0)
    ((:distance __distance) 0.0)
    ((:speed __speed) 0.0)
    ((:acceleration __acceleration) 0.0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _manual __manual)
   (setq _activated __activated)
   (setq _thw (float __thw))
   (setq _alpha (float __alpha))
   (setq _beta (float __beta))
   (setq _vel_gain (round __vel_gain))
   (setq _vel_gain_low (round __vel_gain_low))
   (setq _vel_gain_dec (round __vel_gain_dec))
   (setq _distance (float __distance))
   (setq _speed (float __speed))
   (setq _acceleration (float __acceleration))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:manual
   (&optional __manual)
   (if __manual (setq _manual __manual)) _manual)
  (:activated
   (&optional __activated)
   (if __activated (setq _activated __activated)) _activated)
  (:thw
   (&optional __thw)
   (if __thw (setq _thw __thw)) _thw)
  (:alpha
   (&optional __alpha)
   (if __alpha (setq _alpha __alpha)) _alpha)
  (:beta
   (&optional __beta)
   (if __beta (setq _beta __beta)) _beta)
  (:vel_gain
   (&optional __vel_gain)
   (if __vel_gain (setq _vel_gain __vel_gain)) _vel_gain)
  (:vel_gain_low
   (&optional __vel_gain_low)
   (if __vel_gain_low (setq _vel_gain_low __vel_gain_low)) _vel_gain_low)
  (:vel_gain_dec
   (&optional __vel_gain_dec)
   (if __vel_gain_dec (setq _vel_gain_dec __vel_gain_dec)) _vel_gain_dec)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:acceleration
   (&optional __acceleration)
   (if __acceleration (setq _acceleration __acceleration)) _acceleration)
  (:serialization-length
   ()
   (+
    ;; int16 _id
    2
    ;; bool _manual
    1
    ;; bool _activated
    1
    ;; float32 _thw
    4
    ;; float32 _alpha
    4
    ;; float32 _beta
    4
    ;; int16 _vel_gain
    2
    ;; int16 _vel_gain_low
    2
    ;; int16 _vel_gain_dec
    2
    ;; float32 _distance
    4
    ;; float32 _speed
    4
    ;; float32 _acceleration
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
     ;; bool _activated
       (if _activated (write-byte -1 s) (write-byte 0 s))
     ;; float32 _thw
       (sys::poke _thw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _alpha
       (sys::poke _alpha (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _beta
       (sys::poke _beta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int16 _vel_gain
       (write-word _vel_gain s)
     ;; int16 _vel_gain_low
       (write-word _vel_gain_low s)
     ;; int16 _vel_gain_dec
       (write-word _vel_gain_dec s)
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acceleration
       (sys::poke _acceleration (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _id
     (setq _id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; bool _manual
     (setq _manual (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _activated
     (setq _activated (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _thw
     (setq _thw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _alpha
     (setq _alpha (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _beta
     (setq _beta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int16 _vel_gain
     (setq _vel_gain (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _vel_gain_low
     (setq _vel_gain_low (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _vel_gain_dec
     (setq _vel_gain_dec (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acceleration
     (setq _acceleration (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get cacc_msgs::CaccStatePacket :md5sum-) "d1e7f03c3be6f5504cfdc21bdc1d3462")
(setf (get cacc_msgs::CaccStatePacket :datatype-) "cacc_msgs/CaccStatePacket")
(setf (get cacc_msgs::CaccStatePacket :definition-)
      "int16 id
bool manual #1: manual. 0: automated
bool activated #1: activated, 0: non-activated (ghost-manual)
#int16 order
float32 thw
float32 alpha
float32 beta
int16 vel_gain
int16 vel_gain_low
int16 vel_gain_dec
float32 distance
float32 speed
float32 acceleration
")



(provide :cacc_msgs/CaccStatePacket "d1e7f03c3be6f5504cfdc21bdc1d3462")


