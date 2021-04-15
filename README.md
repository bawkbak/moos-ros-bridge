# moos-ros-bridge
This ros pkg is based on [moos-ros-bridge](https://github.com/SyllogismRXS/moos-ros-bridge). We change the CmakeList from rosbuild to catkin.

### How to run

First terminal, remind to source the setup.bash </br>
$ roslaunch moosros_tester example.launch </br>
Second terminal</br>
$ MOOSDB </br>
Third terminal</br>
$ (some ros node that will generate std_msgs)</br>
Forth terminal, see all the data from ros to moos(example: husky1) </br>
$ uXMS husky1/robot_pose/header/seq husky1/robot_pose/header/stamp/sec husky1/robot_pose/header/stamp/nsec husky1/robot_pose/header/frame_id husky1/robot_pose/pose/position/x husky1/robot_pose/pose/position/y husky1/robot_pose/pose/position/z husky1/robot_pose/pose/orientation/x husky1/robot_pose/pose/orientation/y husky1/robot_pose/pose/orientation/z husky1/robot_pose/pose/orientation/w  </br> 











