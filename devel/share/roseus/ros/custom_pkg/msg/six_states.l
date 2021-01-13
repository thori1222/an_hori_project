;; Auto-generated. Do not edit!


(when (boundp 'custom_pkg::six_states)
  (if (not (find-package "CUSTOM_PKG"))
    (make-package "CUSTOM_PKG"))
  (shadow 'six_states (find-package "CUSTOM_PKG")))
(unless (find-package "CUSTOM_PKG::SIX_STATES")
  (make-package "CUSTOM_PKG::SIX_STATES"))

(in-package "ROS")
;;//! \htmlinclude six_states.msg.html


(defclass custom_pkg::six_states
  :super ros::object
  :slots (_X _Y _yaw _vx _vy _yr ))

(defmethod custom_pkg::six_states
  (:init
   (&key
    ((:X __X) 0.0)
    ((:Y __Y) 0.0)
    ((:yaw __yaw) 0.0)
    ((:vx __vx) 0.0)
    ((:vy __vy) 0.0)
    ((:yr __yr) 0.0)
    )
   (send-super :init)
   (setq _X (float __X))
   (setq _Y (float __Y))
   (setq _yaw (float __yaw))
   (setq _vx (float __vx))
   (setq _vy (float __vy))
   (setq _yr (float __yr))
   self)
  (:X
   (&optional __X)
   (if __X (setq _X __X)) _X)
  (:Y
   (&optional __Y)
   (if __Y (setq _Y __Y)) _Y)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:vx
   (&optional __vx)
   (if __vx (setq _vx __vx)) _vx)
  (:vy
   (&optional __vy)
   (if __vy (setq _vy __vy)) _vy)
  (:yr
   (&optional __yr)
   (if __yr (setq _yr __yr)) _yr)
  (:serialization-length
   ()
   (+
    ;; float32 _X
    4
    ;; float32 _Y
    4
    ;; float32 _yaw
    4
    ;; float32 _vx
    4
    ;; float32 _vy
    4
    ;; float32 _yr
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _X
       (sys::poke _X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Y
       (sys::poke _Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vx
       (sys::poke _vx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy
       (sys::poke _vy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yr
       (sys::poke _yr (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _X
     (setq _X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Y
     (setq _Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vx
     (setq _vx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy
     (setq _vy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yr
     (setq _yr (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get custom_pkg::six_states :md5sum-) "df2621eb80c5f027459612d1c5297bf8")
(setf (get custom_pkg::six_states :datatype-) "custom_pkg/six_states")
(setf (get custom_pkg::six_states :definition-)
      "# This is a message to hold data for six system states
# X[m] Y[m] yaw angle[rad] vx[m/s] vy[m/s] yaw rate[rad/s]
float32 X 
float32 Y
float32 yaw
float32 vx
float32 vy
float32 yr


")



(provide :custom_pkg/six_states "df2621eb80c5f027459612d1c5297bf8")


