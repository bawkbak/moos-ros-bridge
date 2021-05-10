# moos-ros-bridge
This ros pkg is based on [moos-ros-bridge](https://github.com/SyllogismRXS/moos-ros-bridge). We change the CmakeList from rosbuild to catkin.

### How to run
Clone this repo to your catkin_ws/src. For example

First terminal, remind to source the setup.bash </br>
$ roslaunch moosros_tester example.launch </br>
Second terminal</br>
$ MOOSDB </br>
Third terminal </br>
$ (something generate /boat/localization_gps_imu/odometry)) </br>
Fourth terminal, see the data from ros to moos </br>
$ uXMS <variable_names> </br> 
```
<variable_names>:
/boat/localization_gps_imu/odometry/child_frame_id
/boat/localization_gps_imu/odometry/header/frame_id
/boat/localization_gps_imu/odometry/header/seq
/boat/localization_gps_imu/odometry/header/stamp/nsec
/boat/localization_gps_imu/odometry/header/stamp/sec
/boat/localization_gps_imu/odometry/pose/orientation/w
/boat/localization_gps_imu/odometry/pose/orientation/x
/boat/localization_gps_imu/odometry/pose/orientation/y
/boat/localization_gps_imu/odometry/pose/orientation/z
/boat/localization_gps_imu/odometry/pose/position/x
/boat/localization_gps_imu/odometry/pose/position/y
/boat/localization_gps_imu/odometry/pose/position/z
/boat/localization_gps_imu/odometry/twist/angular/x
/boat/localization_gps_imu/odometry/twist/angular/y
/boat/localization_gps_imu/odometry/twist/angular/z
/boat/localization_gps_imu/odometry/twist/linear/x
/boat/localization_gps_imu/odometry/twist/linear/y
/boat/localization_gps_imu/odometry/twist/linear/z
```









