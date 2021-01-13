;; Auto-generated. Do not edit!


(when (boundp 'cacc_msgs::CaccControlPacket)
  (if (not (find-package "CACC_MSGS"))
    (make-package "CACC_MSGS"))
  (shadow 'CaccControlPacket (find-package "CACC_MSGS")))
(unless (find-package "CACC_MSGS::CACCCONTROLPACKET")
  (make-package "CACC_MSGS::CACCCONTROLPACKET"))

(in-package "ROS")
;;//! \htmlinclude CaccControlPacket.msg.html


(defclass cacc_msgs::CaccControlPacket
  :super ros::object
  :slots (_id _vel_ref _acc_ref _checksum ))

(defmethod cacc_msgs::CaccControlPacket
  (:init
   (&key
    ((:id __id) 0)
    ((:vel_ref __vel_ref) 0.0)
    ((:acc_ref __acc_ref) 0.0)
    ((:checksum __checksum) 0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _vel_ref (float __vel_ref))
   (setq _acc_ref (float __acc_ref))
   (setq _checksum (round __checksum))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:vel_ref
   (&optional __vel_ref)
   (if __vel_ref (setq _vel_ref __vel_ref)) _vel_ref)
  (:acc_ref
   (&optional __acc_ref)
   (if __acc_ref (setq _acc_ref __acc_ref)) _acc_ref)
  (:checksum
   (&optional __checksum)
   (if __checksum (setq _checksum __checksum)) _checksum)
  (:serialization-length
   ()
   (+
    ;; int16 _id
    2
    ;; float32 _vel_ref
    4
    ;; float32 _acc_ref
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
     ;; float32 _vel_ref
       (sys::poke _vel_ref (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acc_ref
       (sys::poke _acc_ref (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _checksum
       (write-long _checksum s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _id
     (setq _id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _vel_ref
     (setq _vel_ref (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acc_ref
     (setq _acc_ref (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _checksum
     (setq _checksum (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get cacc_msgs::CaccControlPacket :md5sum-) "ca73aaf0f9afa68bd8dfa673d8298a2c")
(setf (get cacc_msgs::CaccControlPacket :datatype-) "cacc_msgs/CaccControlPacket")
(setf (get cacc_msgs::CaccControlPacket :definition-)
      "int16 id
float32 vel_ref
float32 acc_ref

uint32 checksum
")



(provide :cacc_msgs/CaccControlPacket "ca73aaf0f9afa68bd8dfa673d8298a2c")


