;; Auto-generated. Do not edit!


(when (boundp 'cacc_msgs::CaccMpcState)
  (if (not (find-package "CACC_MSGS"))
    (make-package "CACC_MSGS"))
  (shadow 'CaccMpcState (find-package "CACC_MSGS")))
(unless (find-package "CACC_MSGS::CACCMPCSTATE")
  (make-package "CACC_MSGS::CACCMPCSTATE"))

(in-package "ROS")
;;//! \htmlinclude CaccMpcState.msg.html


(defclass cacc_msgs::CaccMpcState
  :super ros::object
  :slots (_F ))

(defmethod cacc_msgs::CaccMpcState
  (:init
   (&key
    ((:F __F) 0.0)
    )
   (send-super :init)
   (setq _F (float __F))
   self)
  (:F
   (&optional __F)
   (if __F (setq _F __F)) _F)
  (:serialization-length
   ()
   (+
    ;; float32 _F
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _F
       (sys::poke _F (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _F
     (setq _F (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get cacc_msgs::CaccMpcState :md5sum-) "79de4254f7d72d7dd22d2ce8ed43faa2")
(setf (get cacc_msgs::CaccMpcState :datatype-) "cacc_msgs/CaccMpcState")
(setf (get cacc_msgs::CaccMpcState :definition-)
      "float32 F
")



(provide :cacc_msgs/CaccMpcState "79de4254f7d72d7dd22d2ce8ed43faa2")


