; Auto-generated. Do not edit!


(cl:in-package cacc_msgs-msg)


;//! \htmlinclude CaccMpcParam.msg.html

(cl:defclass <CaccMpcParam> (roslisp-msg-protocol:ros-message)
  ((Ds
    :reader Ds
    :initarg :Ds
    :type cl:float
    :initform 0.0)
   (Dmin
    :reader Dmin
    :initarg :Dmin
    :type cl:float
    :initform 0.0)
   (umax
    :reader umax
    :initarg :umax
    :type cl:float
    :initform 0.0)
   (umin
    :reader umin
    :initarg :umin
    :type cl:float
    :initform 0.0)
   (sf0
    :reader sf0
    :initarg :sf0
    :type cl:integer
    :initform 0)
   (sf1
    :reader sf1
    :initarg :sf1
    :type cl:integer
    :initform 0)
   (sf2
    :reader sf2
    :initarg :sf2
    :type cl:integer
    :initform 0)
   (q0
    :reader q0
    :initarg :q0
    :type cl:integer
    :initform 0)
   (q1
    :reader q1
    :initarg :q1
    :type cl:integer
    :initform 0)
   (q2
    :reader q2
    :initarg :q2
    :type cl:integer
    :initform 0)
   (r
    :reader r
    :initarg :r
    :type cl:integer
    :initform 0)
   (su
    :reader su
    :initarg :su
    :type cl:integer
    :initform 0)
   (sd
    :reader sd
    :initarg :sd
    :type cl:integer
    :initform 0)
   (tf
    :reader tf
    :initarg :tf
    :type cl:float
    :initform 0.0)
   (ht
    :reader ht
    :initarg :ht
    :type cl:float
    :initform 0.0)
   (dv
    :reader dv
    :initarg :dv
    :type cl:fixnum
    :initform 0)
   (zeta
    :reader zeta
    :initarg :zeta
    :type cl:fixnum
    :initform 0)
   (kmax
    :reader kmax
    :initarg :kmax
    :type cl:fixnum
    :initform 0))
)

(cl:defclass CaccMpcParam (<CaccMpcParam>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CaccMpcParam>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CaccMpcParam)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name cacc_msgs-msg:<CaccMpcParam> is deprecated: use cacc_msgs-msg:CaccMpcParam instead.")))

(cl:ensure-generic-function 'Ds-val :lambda-list '(m))
(cl:defmethod Ds-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:Ds-val is deprecated.  Use cacc_msgs-msg:Ds instead.")
  (Ds m))

(cl:ensure-generic-function 'Dmin-val :lambda-list '(m))
(cl:defmethod Dmin-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:Dmin-val is deprecated.  Use cacc_msgs-msg:Dmin instead.")
  (Dmin m))

(cl:ensure-generic-function 'umax-val :lambda-list '(m))
(cl:defmethod umax-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:umax-val is deprecated.  Use cacc_msgs-msg:umax instead.")
  (umax m))

(cl:ensure-generic-function 'umin-val :lambda-list '(m))
(cl:defmethod umin-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:umin-val is deprecated.  Use cacc_msgs-msg:umin instead.")
  (umin m))

(cl:ensure-generic-function 'sf0-val :lambda-list '(m))
(cl:defmethod sf0-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:sf0-val is deprecated.  Use cacc_msgs-msg:sf0 instead.")
  (sf0 m))

(cl:ensure-generic-function 'sf1-val :lambda-list '(m))
(cl:defmethod sf1-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:sf1-val is deprecated.  Use cacc_msgs-msg:sf1 instead.")
  (sf1 m))

(cl:ensure-generic-function 'sf2-val :lambda-list '(m))
(cl:defmethod sf2-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:sf2-val is deprecated.  Use cacc_msgs-msg:sf2 instead.")
  (sf2 m))

(cl:ensure-generic-function 'q0-val :lambda-list '(m))
(cl:defmethod q0-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:q0-val is deprecated.  Use cacc_msgs-msg:q0 instead.")
  (q0 m))

(cl:ensure-generic-function 'q1-val :lambda-list '(m))
(cl:defmethod q1-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:q1-val is deprecated.  Use cacc_msgs-msg:q1 instead.")
  (q1 m))

(cl:ensure-generic-function 'q2-val :lambda-list '(m))
(cl:defmethod q2-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:q2-val is deprecated.  Use cacc_msgs-msg:q2 instead.")
  (q2 m))

(cl:ensure-generic-function 'r-val :lambda-list '(m))
(cl:defmethod r-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:r-val is deprecated.  Use cacc_msgs-msg:r instead.")
  (r m))

(cl:ensure-generic-function 'su-val :lambda-list '(m))
(cl:defmethod su-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:su-val is deprecated.  Use cacc_msgs-msg:su instead.")
  (su m))

(cl:ensure-generic-function 'sd-val :lambda-list '(m))
(cl:defmethod sd-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:sd-val is deprecated.  Use cacc_msgs-msg:sd instead.")
  (sd m))

(cl:ensure-generic-function 'tf-val :lambda-list '(m))
(cl:defmethod tf-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:tf-val is deprecated.  Use cacc_msgs-msg:tf instead.")
  (tf m))

(cl:ensure-generic-function 'ht-val :lambda-list '(m))
(cl:defmethod ht-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:ht-val is deprecated.  Use cacc_msgs-msg:ht instead.")
  (ht m))

(cl:ensure-generic-function 'dv-val :lambda-list '(m))
(cl:defmethod dv-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:dv-val is deprecated.  Use cacc_msgs-msg:dv instead.")
  (dv m))

(cl:ensure-generic-function 'zeta-val :lambda-list '(m))
(cl:defmethod zeta-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:zeta-val is deprecated.  Use cacc_msgs-msg:zeta instead.")
  (zeta m))

(cl:ensure-generic-function 'kmax-val :lambda-list '(m))
(cl:defmethod kmax-val ((m <CaccMpcParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader cacc_msgs-msg:kmax-val is deprecated.  Use cacc_msgs-msg:kmax instead.")
  (kmax m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CaccMpcParam>) ostream)
  "Serializes a message object of type '<CaccMpcParam>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Ds))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Dmin))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'umax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'umin))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'sf0)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'sf1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'sf2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'q0)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'q1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'q2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'r)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'su)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'sd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tf))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ht))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'dv)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'zeta)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'kmax)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CaccMpcParam>) istream)
  "Deserializes a message object of type '<CaccMpcParam>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Ds) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Dmin) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'umax) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'umin) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sf0) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sf1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sf2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'q0) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'q1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'q2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'r) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'su) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tf) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ht) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'dv) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'zeta) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'kmax) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CaccMpcParam>)))
  "Returns string type for a message object of type '<CaccMpcParam>"
  "cacc_msgs/CaccMpcParam")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CaccMpcParam)))
  "Returns string type for a message object of type 'CaccMpcParam"
  "cacc_msgs/CaccMpcParam")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CaccMpcParam>)))
  "Returns md5sum for a message object of type '<CaccMpcParam>"
  "520e747c091a36b66d7fea5adeed4945")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CaccMpcParam)))
  "Returns md5sum for a message object of type 'CaccMpcParam"
  "520e747c091a36b66d7fea5adeed4945")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CaccMpcParam>)))
  "Returns full string definition for message of type '<CaccMpcParam>"
  (cl:format cl:nil "float32 Ds~%float32 Dmin~%float32 umax~%float32 umin~%~%int32   sf0~%int32   sf1~%int32   sf2~%int32   q0~%int32   q1~%int32   q2~%int32   r~%int32   su~%int32   sd~%~%float32 tf~%float32 ht~%int16   dv~%int16   zeta~%int16   kmax~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CaccMpcParam)))
  "Returns full string definition for message of type 'CaccMpcParam"
  (cl:format cl:nil "float32 Ds~%float32 Dmin~%float32 umax~%float32 umin~%~%int32   sf0~%int32   sf1~%int32   sf2~%int32   q0~%int32   q1~%int32   q2~%int32   r~%int32   su~%int32   sd~%~%float32 tf~%float32 ht~%int16   dv~%int16   zeta~%int16   kmax~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CaccMpcParam>))
  (cl:+ 0
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
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CaccMpcParam>))
  "Converts a ROS message object to a list"
  (cl:list 'CaccMpcParam
    (cl:cons ':Ds (Ds msg))
    (cl:cons ':Dmin (Dmin msg))
    (cl:cons ':umax (umax msg))
    (cl:cons ':umin (umin msg))
    (cl:cons ':sf0 (sf0 msg))
    (cl:cons ':sf1 (sf1 msg))
    (cl:cons ':sf2 (sf2 msg))
    (cl:cons ':q0 (q0 msg))
    (cl:cons ':q1 (q1 msg))
    (cl:cons ':q2 (q2 msg))
    (cl:cons ':r (r msg))
    (cl:cons ':su (su msg))
    (cl:cons ':sd (sd msg))
    (cl:cons ':tf (tf msg))
    (cl:cons ':ht (ht msg))
    (cl:cons ':dv (dv msg))
    (cl:cons ':zeta (zeta msg))
    (cl:cons ':kmax (kmax msg))
))
