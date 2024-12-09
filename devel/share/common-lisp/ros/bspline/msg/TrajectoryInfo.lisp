; Auto-generated. Do not edit!


(cl:in-package bspline-msg)


;//! \htmlinclude TrajectoryInfo.msg.html

(cl:defclass <TrajectoryInfo> (roslisp-msg-protocol:ros-message)
  ((duration
    :reader duration
    :initarg :duration
    :type cl:float
    :initform 0.0)
   (start_time
    :reader start_time
    :initarg :start_time
    :type cl:real
    :initform 0)
   (pos_end
    :reader pos_end
    :initarg :pos_end
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (pos
    :reader pos
    :initarg :pos
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (vel
    :reader vel
    :initarg :vel
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (acc
    :reader acc
    :initarg :acc
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (start_yaw_
    :reader start_yaw_
    :initarg :start_yaw_
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass TrajectoryInfo (<TrajectoryInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TrajectoryInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TrajectoryInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bspline-msg:<TrajectoryInfo> is deprecated: use bspline-msg:TrajectoryInfo instead.")))

(cl:ensure-generic-function 'duration-val :lambda-list '(m))
(cl:defmethod duration-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:duration-val is deprecated.  Use bspline-msg:duration instead.")
  (duration m))

(cl:ensure-generic-function 'start_time-val :lambda-list '(m))
(cl:defmethod start_time-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:start_time-val is deprecated.  Use bspline-msg:start_time instead.")
  (start_time m))

(cl:ensure-generic-function 'pos_end-val :lambda-list '(m))
(cl:defmethod pos_end-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:pos_end-val is deprecated.  Use bspline-msg:pos_end instead.")
  (pos_end m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:pos-val is deprecated.  Use bspline-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:vel-val is deprecated.  Use bspline-msg:vel instead.")
  (vel m))

(cl:ensure-generic-function 'acc-val :lambda-list '(m))
(cl:defmethod acc-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:acc-val is deprecated.  Use bspline-msg:acc instead.")
  (acc m))

(cl:ensure-generic-function 'start_yaw_-val :lambda-list '(m))
(cl:defmethod start_yaw_-val ((m <TrajectoryInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bspline-msg:start_yaw_-val is deprecated.  Use bspline-msg:start_yaw_ instead.")
  (start_yaw_ m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TrajectoryInfo>) ostream)
  "Serializes a message object of type '<TrajectoryInfo>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'duration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'start_time)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'start_time) (cl:floor (cl:slot-value msg 'start_time)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos_end) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'vel) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'acc) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'start_yaw_) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TrajectoryInfo>) istream)
  "Deserializes a message object of type '<TrajectoryInfo>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'duration) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'start_time) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos_end) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'vel) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'acc) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'start_yaw_) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TrajectoryInfo>)))
  "Returns string type for a message object of type '<TrajectoryInfo>"
  "bspline/TrajectoryInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TrajectoryInfo)))
  "Returns string type for a message object of type 'TrajectoryInfo"
  "bspline/TrajectoryInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TrajectoryInfo>)))
  "Returns md5sum for a message object of type '<TrajectoryInfo>"
  "b0196503bee48a48bdf71c44f3ed61d6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TrajectoryInfo)))
  "Returns md5sum for a message object of type 'TrajectoryInfo"
  "b0196503bee48a48bdf71c44f3ed61d6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TrajectoryInfo>)))
  "Returns full string definition for message of type '<TrajectoryInfo>"
  (cl:format cl:nil "float64 duration~%time start_time~%geometry_msgs/Vector3 pos_end~%geometry_msgs/Vector3 pos~%geometry_msgs/Vector3 vel~%geometry_msgs/Vector3 acc~%geometry_msgs/Vector3 start_yaw_~%~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TrajectoryInfo)))
  "Returns full string definition for message of type 'TrajectoryInfo"
  (cl:format cl:nil "float64 duration~%time start_time~%geometry_msgs/Vector3 pos_end~%geometry_msgs/Vector3 pos~%geometry_msgs/Vector3 vel~%geometry_msgs/Vector3 acc~%geometry_msgs/Vector3 start_yaw_~%~%~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TrajectoryInfo>))
  (cl:+ 0
     8
     8
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos_end))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'vel))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'acc))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'start_yaw_))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TrajectoryInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'TrajectoryInfo
    (cl:cons ':duration (duration msg))
    (cl:cons ':start_time (start_time msg))
    (cl:cons ':pos_end (pos_end msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':vel (vel msg))
    (cl:cons ':acc (acc msg))
    (cl:cons ':start_yaw_ (start_yaw_ msg))
))
