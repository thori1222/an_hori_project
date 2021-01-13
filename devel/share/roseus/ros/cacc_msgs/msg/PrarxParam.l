;; Auto-generated. Do not edit!


(when (boundp 'cacc_msgs::PrarxParam)
  (if (not (find-package "CACC_MSGS"))
    (make-package "CACC_MSGS"))
  (shadow 'PrarxParam (find-package "CACC_MSGS")))
(unless (find-package "CACC_MSGS::PRARXPARAM")
  (make-package "CACC_MSGS::PRARXPARAM"))

(in-package "ROS")
;;//! \htmlinclude PrarxParam.msg.html


(defclass cacc_msgs::PrarxParam
  :super ros::object
  :slots (_theta1 _theta2 _eta _scale ))

(defmethod cacc_msgs::PrarxParam
  (:init
   (&key
    ((:theta1 __theta1) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:theta2 __theta2) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:eta __eta) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:scale __scale) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _theta1 __theta1)
   (setq _theta2 __theta2)
   (setq _eta __eta)
   (setq _scale __scale)
   self)
  (:theta1
   (&optional __theta1)
   (if __theta1 (setq _theta1 __theta1)) _theta1)
  (:theta2
   (&optional __theta2)
   (if __theta2 (setq _theta2 __theta2)) _theta2)
  (:eta
   (&optional __eta)
   (if __eta (setq _eta __eta)) _eta)
  (:scale
   (&optional __scale)
   (if __scale (setq _scale __scale)) _scale)
  (:serialization-length
   ()
   (+
    ;; float32[] _theta1
    (* 4    (length _theta1)) 4
    ;; float32[] _theta2
    (* 4    (length _theta2)) 4
    ;; float32[] _eta
    (* 4    (length _eta)) 4
    ;; float32[] _scale
    (* 4    (length _scale)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _theta1
     (write-long (length _theta1) s)
     (dotimes (i (length _theta1))
       (sys::poke (elt _theta1 i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _theta2
     (write-long (length _theta2) s)
     (dotimes (i (length _theta2))
       (sys::poke (elt _theta2 i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _eta
     (write-long (length _eta) s)
     (dotimes (i (length _eta))
       (sys::poke (elt _eta i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _scale
     (write-long (length _scale) s)
     (dotimes (i (length _scale))
       (sys::poke (elt _scale i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _theta1
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _theta1 (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _theta1 i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _theta2
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _theta2 (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _theta2 i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _eta
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _eta (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _eta i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _scale
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _scale (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _scale i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get cacc_msgs::PrarxParam :md5sum-) "50e5d6a7f9d855220ccc7cbcc9f77398")
(setf (get cacc_msgs::PrarxParam :datatype-) "cacc_msgs/PrarxParam")
(setf (get cacc_msgs::PrarxParam :definition-)
      "float32[] theta1
float32[] theta2
float32[] eta
float32[] scale
")



(provide :cacc_msgs/PrarxParam "50e5d6a7f9d855220ccc7cbcc9f77398")


