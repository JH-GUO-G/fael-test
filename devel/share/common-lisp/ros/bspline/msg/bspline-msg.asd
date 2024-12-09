
(cl:in-package :asdf)

(defsystem "bspline-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "Bspline" :depends-on ("_package_Bspline"))
    (:file "_package_Bspline" :depends-on ("_package"))
    (:file "TrajectoryInfo" :depends-on ("_package_TrajectoryInfo"))
    (:file "_package_TrajectoryInfo" :depends-on ("_package"))
    (:file "replaninfo" :depends-on ("_package_replaninfo"))
    (:file "_package_replaninfo" :depends-on ("_package"))
  ))