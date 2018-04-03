/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include "std_msgs/String.h"
#include <ros/ros.h>
#include <termios.h>
#include "homework1/myMsg.h"
#include <signal.h>

ros::Publisher filtered_pub;
int kfd = 0;
struct termios cooked, raw;
int count=0;



void chatterCallback(const homework1::myMsg& msg)
{ 
	
       char c;

  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  
 homework1::myMsg msgf;
    // get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    ROS_DEBUG("value: 0x%02X\n", c);
  
    switch(c)
    {

      case 'a':
	{ 
        msgf.name=msg.name;
	msgf.age=msg.age;
	msgf.course=msg.course;        
        break;
	}
      case 'n':
  	{
	
	msgf.name=msg.name;
	//msgf.age=NULL;	
        break;
	}
      case 'e':
	{        
        msgf.age=msg.age;        
        break;
	}
      case 'c':
	{        
        msgf.course=msg.course;
	}
        break;
	default:
	puts("invalid command!");
	
    }
    filtered_pub.publish(msgf);
  }

 void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}  




int main(int argc, char **argv)
{
 
   ros::init(argc, argv, "filter");
  
   ros::NodeHandle n;
 
   puts("Reading from keyboard");
   puts("---------------------------");
   puts("a : to show all the message");
   puts("n : to show the name");
   puts("e : to show the age");
   puts("c : to show the course");
   ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);	

   filtered_pub= n.advertise<homework1::myMsg>("filtered", 1000);
signal(SIGINT,quit);
   ros::spin();

   return 0;
}


