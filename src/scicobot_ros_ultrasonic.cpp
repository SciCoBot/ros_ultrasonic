/***********************************************************************************
 *  @file       scicobot_ros_ultrasonic.cpp
 *  Project     scicobot_hardware
 *  @brief      *****
 *
 *  @author     Otávio Augusto Rocha da Cruz
 *  @bug 		 No known bugs.
 *  License     MIT
 *
 *  @section License
 *
 * Copyright (c) 2021 SciCoBot
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**********************************************************************************/
#include "scicobot_ros_ultrasonic.h"
#include <led_debug.h>
#include <Arduino.h>

void ScicobotRosUltrasonic::initPublisherAndTimerUltrasonic(ScicobotRos* scicobotRos, void (*timerCallbackUltrasonic)(rcl_timer_t*, int64_t), char* topicName, int16_t timerPeriod)
{    
  #if SCICOBOT_ROS_ULTRASONIC_BEST_EFFORT == 0
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_default(
    &publisherUltrasonic,
    scicobotRos->get_rcl_node(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    topicName));
   #else
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_best_effort(
    &publisherUltrasonic,
    scicobotRos->get_rcl_node(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    topicName));   
   #endif
  
  DEBUG_ERROR_MICR0_ROS(rclc_timer_init_default(
    &timerUltrasonic,
    scicobotRos->get_rclc_support(),
    RCL_MS_TO_NS(timerPeriod),
    timerCallbackUltrasonic));
}
void ScicobotRosUltrasonic::initExecutorUltrasonic(ScicobotRos* scicobotRos, int numberHandles)
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_init(&executorUltrasonic, 
  	 &(*scicobotRos->get_rclc_support()).context,
  	 numberHandles, 
  	 scicobotRos->get_rcl_allocator()));
    
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
  debugObj.DEBUGLN("initExecutorMotor() sucess...");  
  #endif
}
void ScicobotRosUltrasonic::addExecutorsUltrasonic()
{
 
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_timer(&executorUltrasonic, &timerUltrasonic));
  
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
    debugObj.DEBUGLN("addExecutorsUltrasonic() sucess...");  
  #endif
}

void ScicobotRosUltrasonic::initRosUltrasonicPublisher(ScicobotRos* scicobotRos, void (*timerCallbackUltrasonic)(rcl_timer_t*, int64_t))
{

  this->initPublisherAndTimerUltrasonic(scicobotRos, timerCallbackUltrasonic, "/frontal_ultrasonic", 500);
  
  this->initExecutorUltrasonic(scicobotRos, 1);
  
  this->addExecutorsUltrasonic();
  
  
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
    debugObj.DEBUGLN("initRosUltrasonicPublisher() sucess...");  
  #endif
}
rclc_executor_t* ScicobotRosUltrasonic::get_rclc_executor()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of executorUltrasonic is: "); 
		debugObj.DEBUGLN(&executorUltrasonic); 
	#endif
	
	return &executorUltrasonic;
}

rcl_publisher_t* ScicobotRosUltrasonic::get_rclc_publisher()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of publisherUltrasonic is: "); 
		debugObj.DEBUGLN(&publisherUltrasonic); 
	#endif
	
	return &publisherUltrasonic;
}

std_msgs__msg__Float32* ScicobotRosUltrasonic::get_rclc_msg()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of msgUltrasonic is: "); 
		debugObj.DEBUGLN(&msgUltrasonic); 
	#endif
	
	return &msgUltrasonic;
}
