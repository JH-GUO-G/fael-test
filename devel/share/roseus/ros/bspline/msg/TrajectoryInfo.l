;; Auto-generated. Do not edit!


(when (boundp 'bspline::TrajectoryInfo)
  (if (not (find-package "BSPLINE"))
    (make-package "BSPLINE"))
  (shadow 'TrajectoryInfo (find-package "BSPLINE")))
(unless (find-package "BSPLINE::TRAJECTORYINFO")
  (make-package "BSPLINE::TRAJECTORYINFO"))

(in-package "ROS")
;;//! \htmlinclude TrajectoryInfo.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass bspline::TrajectoryInfo
  :super ros::object
  :slots (_duration _start_time _pos_end _pos _vel _acc _start_yaw_ ))

(defmethod bspline::TrajectoryInfo
  (:init
   (&key
    ((:duration __duration) 0.0)
    ((:start_time __start_time) (instance ros::time :init))
    ((:pos_end __pos_end) (instance geometry_msgs::Vector3 :init))
    ((:pos __pos) (instance geometry_msgs::Vector3 :init))
    ((:vel __vel) (instance geometry_msgs::Vector3 :init))
    ((:acc __acc) (instance geometry_msgs::Vector3 :init))
    ((:start_yaw_ __start_yaw_) (instance geometry_msgs::Vector3 :init))
    )
   (send-super :init)
   (setq _duration (float __duration))
   (setq _start_time __start_time)
   (setq _pos_end __pos_end)
   (setq _pos __pos)
   (setq _vel __vel)
   (setq _acc __acc)
   (setq _start_yaw_ __start_yaw_)
   self)
  (:duration
   (&optional __duration)
   (if __duration (setq _duration __duration)) _duration)
  (:start_time
   (&optional __start_time)
   (if __start_time (setq _start_time __start_time)) _start_time)
  (:pos_end
   (&rest __pos_end)
   (if (keywordp (car __pos_end))
       (send* _pos_end __pos_end)
     (progn
       (if __pos_end (setq _pos_end (car __pos_end)))
       _pos_end)))
  (:pos
   (&rest __pos)
   (if (keywordp (car __pos))
       (send* _pos __pos)
     (progn
       (if __pos (setq _pos (car __pos)))
       _pos)))
  (:vel
   (&rest __vel)
   (if (keywordp (car __vel))
       (send* _vel __vel)
     (progn
       (if __vel (setq _vel (car __vel)))
       _vel)))
  (:acc
   (&rest __acc)
   (if (keywordp (car __acc))
       (send* _acc __acc)
     (progn
       (if __acc (setq _acc (car __acc)))
       _acc)))
  (:start_yaw_
   (&rest __start_yaw_)
   (if (keywordp (car __start_yaw_))
       (send* _start_yaw_ __start_yaw_)
     (progn
       (if __start_yaw_ (setq _start_yaw_ (car __start_yaw_)))
       _start_yaw_)))
  (:serialization-length
   ()
   (+
    ;; float64 _duration
    8
    ;; time _start_time
    8
    ;; geometry_msgs/Vector3 _pos_end
    (send _pos_end :serialization-length)
    ;; geometry_msgs/Vector3 _pos
    (send _pos :serialization-length)
    ;; geometry_msgs/Vector3 _vel
    (send _vel :serialization-length)
    ;; geometry_msgs/Vector3 _acc
    (send _acc :serialization-length)
    ;; geometry_msgs/Vector3 _start_yaw_
    (send _start_yaw_ :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _duration
       (sys::poke _duration (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; time _start_time
       (write-long (send _start_time :sec) s) (write-long (send _start_time :nsec) s)
     ;; geometry_msgs/Vector3 _pos_end
       (send _pos_end :serialize s)
     ;; geometry_msgs/Vector3 _pos
       (send _pos :serialize s)
     ;; geometry_msgs/Vector3 _vel
       (send _vel :serialize s)
     ;; geometry_msgs/Vector3 _acc
       (send _acc :serialize s)
     ;; geometry_msgs/Vector3 _start_yaw_
       (send _start_yaw_ :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _duration
     (setq _duration (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; time _start_time
     (send _start_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _start_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Vector3 _pos_end
     (send _pos_end :deserialize buf ptr-) (incf ptr- (send _pos_end :serialization-length))
   ;; geometry_msgs/Vector3 _pos
     (send _pos :deserialize buf ptr-) (incf ptr- (send _pos :serialization-length))
   ;; geometry_msgs/Vector3 _vel
     (send _vel :deserialize buf ptr-) (incf ptr- (send _vel :serialization-length))
   ;; geometry_msgs/Vector3 _acc
     (send _acc :deserialize buf ptr-) (incf ptr- (send _acc :serialization-length))
   ;; geometry_msgs/Vector3 _start_yaw_
     (send _start_yaw_ :deserialize buf ptr-) (incf ptr- (send _start_yaw_ :serialization-length))
   ;;
   self)
  )

(setf (get bspline::TrajectoryInfo :md5sum-) "b0196503bee48a48bdf71c44f3ed61d6")
(setf (get bspline::TrajectoryInfo :datatype-) "bspline/TrajectoryInfo")
(setf (get bspline::TrajectoryInfo :definition-)
      "float64 duration
time start_time
geometry_msgs/Vector3 pos_end
geometry_msgs/Vector3 pos
geometry_msgs/Vector3 vel
geometry_msgs/Vector3 acc
geometry_msgs/Vector3 start_yaw_



================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :bspline/TrajectoryInfo "b0196503bee48a48bdf71c44f3ed61d6")


