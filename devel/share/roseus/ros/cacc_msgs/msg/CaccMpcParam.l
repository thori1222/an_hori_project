;; Auto-generated. Do not edit!


(when (boundp 'cacc_msgs::CaccMpcParam)
  (if (not (find-package "CACC_MSGS"))
    (make-package "CACC_MSGS"))
  (shadow 'CaccMpcParam (find-package "CACC_MSGS")))
(unless (find-package "CACC_MSGS::CACCMPCPARAM")
  (make-package "CACC_MSGS::CACCMPCPARAM"))

(in-package "ROS")
;;//! \htmlinclude CaccMpcParam.msg.html


(defclass cacc_msgs::CaccMpcParam
  :super ros::object
  :slots (_Ds _Dmin _umax _umin _sf0 _sf1 _sf2 _q0 _q1 _q2 _r _su _sd _tf _ht _dv _zeta _kmax ))

(defmethod cacc_msgs::CaccMpcParam
  (:init
   (&key
    ((:Ds __Ds) 0.0)
    ((:Dmin __Dmin) 0.0)
    ((:umax __umax) 0.0)
    ((:umin __umin) 0.0)
    ((:sf0 __sf0) 0)
    ((:sf1 __sf1) 0)
    ((:sf2 __sf2) 0)
    ((:q0 __q0) 0)
    ((:q1 __q1) 0)
    ((:q2 __q2) 0)
    ((:r __r) 0)
    ((:su __su) 0)
    ((:sd __sd) 0)
    ((:tf __tf) 0.0)
    ((:ht __ht) 0.0)
    ((:dv __dv) 0)
    ((:zeta __zeta) 0)
    ((:kmax __kmax) 0)
    )
   (send-super :init)
   (setq _Ds (float __Ds))
   (setq _Dmin (float __Dmin))
   (setq _umax (float __umax))
   (setq _umin (float __umin))
   (setq _sf0 (round __sf0))
   (setq _sf1 (round __sf1))
   (setq _sf2 (round __sf2))
   (setq _q0 (round __q0))
   (setq _q1 (round __q1))
   (setq _q2 (round __q2))
   (setq _r (round __r))
   (setq _su (round __su))
   (setq _sd (round __sd))
   (setq _tf (float __tf))
   (setq _ht (float __ht))
   (setq _dv (round __dv))
   (setq _zeta (round __zeta))
   (setq _kmax (round __kmax))
   self)
  (:Ds
   (&optional __Ds)
   (if __Ds (setq _Ds __Ds)) _Ds)
  (:Dmin
   (&optional __Dmin)
   (if __Dmin (setq _Dmin __Dmin)) _Dmin)
  (:umax
   (&optional __umax)
   (if __umax (setq _umax __umax)) _umax)
  (:umin
   (&optional __umin)
   (if __umin (setq _umin __umin)) _umin)
  (:sf0
   (&optional __sf0)
   (if __sf0 (setq _sf0 __sf0)) _sf0)
  (:sf1
   (&optional __sf1)
   (if __sf1 (setq _sf1 __sf1)) _sf1)
  (:sf2
   (&optional __sf2)
   (if __sf2 (setq _sf2 __sf2)) _sf2)
  (:q0
   (&optional __q0)
   (if __q0 (setq _q0 __q0)) _q0)
  (:q1
   (&optional __q1)
   (if __q1 (setq _q1 __q1)) _q1)
  (:q2
   (&optional __q2)
   (if __q2 (setq _q2 __q2)) _q2)
  (:r
   (&optional __r)
   (if __r (setq _r __r)) _r)
  (:su
   (&optional __su)
   (if __su (setq _su __su)) _su)
  (:sd
   (&optional __sd)
   (if __sd (setq _sd __sd)) _sd)
  (:tf
   (&optional __tf)
   (if __tf (setq _tf __tf)) _tf)
  (:ht
   (&optional __ht)
   (if __ht (setq _ht __ht)) _ht)
  (:dv
   (&optional __dv)
   (if __dv (setq _dv __dv)) _dv)
  (:zeta
   (&optional __zeta)
   (if __zeta (setq _zeta __zeta)) _zeta)
  (:kmax
   (&optional __kmax)
   (if __kmax (setq _kmax __kmax)) _kmax)
  (:serialization-length
   ()
   (+
    ;; float32 _Ds
    4
    ;; float32 _Dmin
    4
    ;; float32 _umax
    4
    ;; float32 _umin
    4
    ;; int32 _sf0
    4
    ;; int32 _sf1
    4
    ;; int32 _sf2
    4
    ;; int32 _q0
    4
    ;; int32 _q1
    4
    ;; int32 _q2
    4
    ;; int32 _r
    4
    ;; int32 _su
    4
    ;; int32 _sd
    4
    ;; float32 _tf
    4
    ;; float32 _ht
    4
    ;; int16 _dv
    2
    ;; int16 _zeta
    2
    ;; int16 _kmax
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _Ds
       (sys::poke _Ds (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Dmin
       (sys::poke _Dmin (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _umax
       (sys::poke _umax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _umin
       (sys::poke _umin (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _sf0
       (write-long _sf0 s)
     ;; int32 _sf1
       (write-long _sf1 s)
     ;; int32 _sf2
       (write-long _sf2 s)
     ;; int32 _q0
       (write-long _q0 s)
     ;; int32 _q1
       (write-long _q1 s)
     ;; int32 _q2
       (write-long _q2 s)
     ;; int32 _r
       (write-long _r s)
     ;; int32 _su
       (write-long _su s)
     ;; int32 _sd
       (write-long _sd s)
     ;; float32 _tf
       (sys::poke _tf (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ht
       (sys::poke _ht (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int16 _dv
       (write-word _dv s)
     ;; int16 _zeta
       (write-word _zeta s)
     ;; int16 _kmax
       (write-word _kmax s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _Ds
     (setq _Ds (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Dmin
     (setq _Dmin (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _umax
     (setq _umax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _umin
     (setq _umin (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _sf0
     (setq _sf0 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _sf1
     (setq _sf1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _sf2
     (setq _sf2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _q0
     (setq _q0 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _q1
     (setq _q1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _q2
     (setq _q2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _r
     (setq _r (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _su
     (setq _su (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _sd
     (setq _sd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _tf
     (setq _tf (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ht
     (setq _ht (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int16 _dv
     (setq _dv (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _zeta
     (setq _zeta (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _kmax
     (setq _kmax (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get cacc_msgs::CaccMpcParam :md5sum-) "520e747c091a36b66d7fea5adeed4945")
(setf (get cacc_msgs::CaccMpcParam :datatype-) "cacc_msgs/CaccMpcParam")
(setf (get cacc_msgs::CaccMpcParam :definition-)
      "float32 Ds
float32 Dmin
float32 umax
float32 umin

int32   sf0
int32   sf1
int32   sf2
int32   q0
int32   q1
int32   q2
int32   r
int32   su
int32   sd

float32 tf
float32 ht
int16   dv
int16   zeta
int16   kmax
")



(provide :cacc_msgs/CaccMpcParam "520e747c091a36b66d7fea5adeed4945")


