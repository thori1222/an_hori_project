;; Auto-generated. Do not edit!


(when (boundp 'custom_pkg::control_signal)
  (if (not (find-package "CUSTOM_PKG"))
    (make-package "CUSTOM_PKG"))
  (shadow 'control_signal (find-package "CUSTOM_PKG")))
(unless (find-package "CUSTOM_PKG::CONTROL_SIGNAL")
  (make-package "CUSTOM_PKG::CONTROL_SIGNAL"))

(in-package "ROS")
;;//! \htmlinclude control_signal.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass custom_pkg::control_signal
  :super ros::object
  :slots (_header _accel _steer _status ))

(defmethod custom_pkg::control_signal
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:accel __accel) 0.0)
    ((:steer __steer) 0.0)
    ((:status __status) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _accel (float __accel))
   (setq _steer (float __steer))
   (setq _status (round __status))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:accel
   (&optional __accel)
   (if __accel (setq _accel __accel)) _accel)
  (:steer
   (&optional __steer)
   (if __steer (setq _steer __steer)) _steer)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _accel
    4
    ;; float32 _steer
    4
    ;; int8 _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _accel
       (sys::poke _accel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steer
       (sys::poke _steer (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int8 _status
       (write-byte _status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _accel
     (setq _accel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steer
     (setq _steer (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int8 _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _status 127) (setq _status (- _status 256)))
   ;;
   self)
  )

(setf (get custom_pkg::control_signal :md5sum-) "da55517947a600b569ad9bc4fd50c76b")
(setf (get custom_pkg::control_signal :datatype-) "custom_pkg/control_signal")
(setf (get custom_pkg::control_signal :definition-)
      "Header header
float32 accel
float32 steer
int8 status

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :custom_pkg/control_signal "da55517947a600b569ad9bc4fd50c76b")


