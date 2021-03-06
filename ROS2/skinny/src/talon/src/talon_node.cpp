#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <thread>
#include <chrono>
#include <linux/reboot.h>
#include <sys/reboot.h>


#include <rclcpp/rclcpp.hpp>
//#include <rclcpp/console.h>
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <std_msgs/msg/empty.hpp>

#define Phoenix_No_WPI // remove WPI dependencies
#include <ctre/Phoenix.h>
#include <ctre/phoenix/platform/Platform.h>
#include <ctre/phoenix/unmanaged/Unmanaged.h>

#include "messages/msg/talon_out.hpp"

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;


//bool GO=false;
bool GO = true;
void stopCallback(std_msgs::msg::Empty::SharedPtr empty){
	std::cout << "STOP" << std::endl;
	GO=false;
} 
void goCallback(std_msgs::msg::Empty::SharedPtr empty){
	std::cout << "GO" << std::endl;
	GO=true;
}

bool useVelocity=false;
int velocityMultiplier=0;
int testSpeed=0;
TalonSRX* talonSRX;
void speedCallback(const std_msgs::msg::Float32::SharedPtr speed){
	std::cout << "---------->>>  " << speed->data << std::endl;

	if(useVelocity){
        	talonSRX->Set(ControlMode::Velocity, int(speed->data*velocityMultiplier));
		//talonSRX->Set(ControlMode::Velocity, testSpeed);
	}else{
        	talonSRX->Set(ControlMode::PercentOutput, speed->data);
	}
}


int main(int argc,char** argv){
	rclcpp::init(argc,argv);
	rclcpp::Node::SharedPtr nodeHandle = rclcpp::Node::make_shared("talon");

	RCLCPP_INFO(nodeHandle->get_logger(),"Starting talon");
	//int success;

	//int motorNumber=0;
	//success=nodeHandleP.getParam("motor_number", motorNumber);
	nodeHandle->declare_parameter<int>("motor_number",1);
	rclcpp::Parameter motorNumberParameter = nodeHandle->get_parameter("motor_number");
	int motorNumber = motorNumberParameter.as_int();
	std::cout << "motor_number: " << motorNumber << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"motorNumber: %d", motorNumber);
	
	//std::string infoTopic;
	//success=nodeHandleP.getParam("info_topic", infoTopic);
	nodeHandle->declare_parameter<std::string>("info_topic","unset");
        rclcpp::Parameter infoTopicParameter = nodeHandle->get_parameter("info_topic");
        std::string infoTopic = infoTopicParameter.as_string();
	std::cout << "info_topic: " << infoTopic << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"infoTopic: %s",infoTopic.c_str());

	//std::string speedTopic;
	//success=nodeHandleP.getParam("speed_topic", speedTopic);
	nodeHandle->declare_parameter<std::string>("speed_topic","unset");
        rclcpp::Parameter speedTopicParameter = nodeHandle->get_parameter("speed_topic");
        std::string speedTopic = speedTopicParameter.as_string();
	std::cout << "speed_topic: " << speedTopic << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"speedTopic: %s",speedTopic.c_str());

	//bool invertMotor=false;
	//success=nodeHandleP.getParam("invert_motor", invertMotor);
	nodeHandle->declare_parameter<bool>("invert_motor",false);
        rclcpp::Parameter invertMotorParameter = nodeHandle->get_parameter("invert_motor");
        bool invertMotor = invertMotorParameter.as_bool();
	std::cout << "invert_motor: " << invertMotor << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"invertMotor: %d",invertMotor);

	//success=nodeHandleP.getParam("use_velocity", useVelocity);
	nodeHandle->declare_parameter<bool>("use_velocity",false);
        rclcpp::Parameter useVelocityParameter = nodeHandle->get_parameter("use_velocity");
        useVelocity = useVelocityParameter.as_bool();
	std::cout << "use_velocity: " << useVelocity << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"useVelocity: %d",useVelocity);

	//success=nodeHandleP.getParam("velocity_multiplier", velocityMultiplier);
	nodeHandle->declare_parameter<int>("velocity_multiplier",0);
        rclcpp::Parameter velocityMultiplierParameter = nodeHandle->get_parameter("velocity_multiplier");
        velocityMultiplier = velocityMultiplierParameter.as_int();
	std::cout << "velocity_multiplier: " << velocityMultiplier << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"velocityMultiplier: %d",velocityMultiplier);

	//success=nodeHandleP.getParam("test_speed", testSpeed);
	nodeHandle->declare_parameter<int>("test_speed",0);
        rclcpp::Parameter testSpeedParameter = nodeHandle->get_parameter("test_speed");
        testSpeed = testSpeedParameter.as_int();
	std::cout << "test_speed: " << testSpeed << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"testSpeed: %d",testSpeed);

	//double kP=0;
	//success=nodeHandleP.getParam("kP", kP);
	nodeHandle->declare_parameter<double>("kP",1);
        rclcpp::Parameter kPParameter = nodeHandle->get_parameter("kP");
        double kP= kPParameter.as_double();
	std::cout << "kP: " << kP << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"kP: %f",kP);

	//double kI=0;
	//success=nodeHandleP.getParam("kI", kI);
	nodeHandle->declare_parameter<double>("kI",0);
        rclcpp::Parameter kIParameter = nodeHandle->get_parameter("kI");
        double kI= kIParameter.as_double();
	std::cout << "kI: " << kI << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"kI: %f",kI);

	//double kD=0;
	//success=nodeHandleP.getParam("kD", kD);
	nodeHandle->declare_parameter<double>("kD",0);
        rclcpp::Parameter kDParameter = nodeHandle->get_parameter("kD");
        double kD= kDParameter.as_double();
	std::cout << "kD: " << kD << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"kD: %f",kD);

	//double kF=0;
	//success=nodeHandleP.getParam("kF", kF);
	nodeHandle->declare_parameter<double>("kF",0);
        rclcpp::Parameter kFParameter = nodeHandle->get_parameter("kF");
        double kF= kFParameter.as_double();
	std::cout << "kF: " << kF << std::endl;
	RCLCPP_INFO(nodeHandle->get_logger(),"kF: %f",kF);

        ctre::phoenix::platform::can::SetCANInterface("can0");
	RCLCPP_INFO(nodeHandle->get_logger(),"Opened CAN interface");

	int kTimeoutMs=30;
	int kPIDLoopIdx=0;
	//int kSlotIdx=0;
	talonSRX=new TalonSRX(motorNumber);
	RCLCPP_INFO(nodeHandle->get_logger(),"created talon instance");

	talonSRX->SetInverted(invertMotor);
	RCLCPP_INFO(nodeHandle->get_logger(),"here 1");

	talonSRX->SelectProfileSlot(0,0);
	talonSRX->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeoutMs);
	//talonSRX->SetSensorPhase(false);
	talonSRX->ConfigClosedloopRamp(2);
	talonSRX->ConfigNominalOutputForward(0, kTimeoutMs);
	talonSRX->ConfigNominalOutputReverse(0, kTimeoutMs);
	talonSRX->ConfigPeakOutputForward(1, kTimeoutMs);
	talonSRX->ConfigPeakOutputReverse(-1, kTimeoutMs);
	talonSRX->Config_kF(kPIDLoopIdx, kF, kTimeoutMs);
	talonSRX->Config_kP(kPIDLoopIdx, kP, kTimeoutMs);
	talonSRX->Config_kI(kPIDLoopIdx, kI, kTimeoutMs);
	talonSRX->Config_kD(kPIDLoopIdx, kD, kTimeoutMs);
	talonSRX->ConfigAllowableClosedloopError(kPIDLoopIdx,0,kTimeoutMs);

        talonSRX->Set(ControlMode::PercentOutput, 0);
        talonSRX->Set(ControlMode::Velocity, 0);

	RCLCPP_INFO(nodeHandle->get_logger(),"configured talon");

	TalonSRXPIDSetConfiguration pid;
	TalonSRXConfiguration allConfigs;
	//StatusFrame statusFrame;

	messages::msg::TalonOut talonOut;
	//ros::Publisher talonOutPublisher=nodeHandle.advertise<messages::TalonOut>(infoTopic.c_str(),1);
	auto talonOutPublisher=nodeHandle->create_publisher<messages::msg::TalonOut>(infoTopic.c_str(),1);
	//ros::Subscriber speedSubscriber=nodeHandle.subscribe(speedTopic.c_str(),1,speedCallback);
	auto speedSubscriber=nodeHandle->create_subscription<std_msgs::msg::Float32>(speedTopic.c_str(),1,speedCallback);

	//ros::Subscriber stopSubscriber=nodeHandle.subscribe("STOP",1,stopCallback); 
	auto stopSubscriber=nodeHandle->create_subscription<std_msgs::msg::Empty>("STOP",1,stopCallback);
	//ros::Subscriber goSubscriber=nodeHandle.subscribe("GO",1,goCallback); 
	auto goSubscriber=nodeHandle->create_subscription<std_msgs::msg::Empty>("GO",1,goCallback);
	RCLCPP_INFO(nodeHandle->get_logger(),"set subscribers");


	int count=0;
        auto start = std::chrono::high_resolution_clock::now();
        while(rclcpp::ok()){
		if(GO)ctre::phoenix::unmanaged::FeedEnable(100);
		auto finish = std::chrono::high_resolution_clock::now();

		if(std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() > 250000000){
			int deviceID=talonSRX->GetDeviceID();
			double busVoltage=talonSRX->GetBusVoltage();
			double outputCurrent=talonSRX->GetOutputCurrent();
			bool isInverted=talonSRX->GetInverted();
			double motorOutputVoltage=talonSRX->GetMotorOutputVoltage();
			double motorOutputPercent=talonSRX->GetMotorOutputPercent();
			double temperature=talonSRX->GetTemperature();
			int sensorPosition0=talonSRX->GetSelectedSensorPosition(0);
			int sensorVelocity0=talonSRX->GetSelectedSensorVelocity(0);
			int closedLoopError0=talonSRX->GetClosedLoopError(0);
			double integralAccumulator0=talonSRX->GetIntegralAccumulator(0);
			double errorDerivative0=talonSRX->GetErrorDerivative(0);
		
			talonOut.device_id=deviceID;	
			talonOut.bus_voltage=busVoltage;
			talonOut.output_current=outputCurrent;
			talonOut.output_voltage=motorOutputVoltage;
			talonOut.output_percent=motorOutputPercent;
			talonOut.temperature=temperature;
			talonOut.sensor_position=sensorPosition0;
			talonOut.sensor_velocity=sensorVelocity0;
			talonOut.closed_loop_error=closedLoopError0;
			talonOut.integral_accumulator=integralAccumulator0;
			talonOut.error_derivative=errorDerivative0;

			talonOutPublisher->publish(talonOut);
        		start = std::chrono::high_resolution_clock::now();
		}

		if(count++>200 && GO){
			std::cout <<"V=" << talonSRX->GetSelectedSensorVelocity(kPIDLoopIdx) <<"  "
				<< "  E=" << talonSRX->GetClosedLoopError(kPIDLoopIdx) 
				<< "  IA=" << talonSRX->GetIntegralAccumulator(kPIDLoopIdx)
				<< "  ED=" << talonSRX->GetErrorDerivative(kPIDLoopIdx) 
				<< std::endl;
			count=0;
		}
		 	
/*
		talonSRX->GetPIDConfigs(pid, 0,0);
		talonSRX->GetAllConfigs(allConfigs);

		int id=talonSRX->GetDeviceID();
		double voltage=talonSRX->GetBusVoltage();
		double outputCurrent=talonSRX->GetOutputCurrent();
		bool isInverted=talonSRX->GetInverted();
		double motorOutputPercent=talonSRX->GetMotorOutputPercent();
		double motorOutputVoltage=talonSRX->GetMotorOutputVoltage();
		double temperature=talonSRX->GetTemperature();
		int sensorPosition0=talonSRX->GetSelectedSensorPosition(0);
		int sensorVelocity0=talonSRX->GetSelectedSensorVelocity(0);
		int cloosedLoopError0=talonSRX->GetClosedLoopError(0);
		double integralAccumulator0=talonSRX->GetIntegralAccumulator(0);
		double errorDerivative0=talonSRX->GetErrorDerivative(0);
		double closedLoopTargeti0=talonSRX->GetClosedLoopTarget(0);
		int activeTrajectoryPosition0=talonSRX->GetActiveTrajectoryPosition(0);
		int activeTrajectoryVelocity0=talonSRX->GetActiveTrajectoryVelocity(0);
		double activeTrajectoryArbFeedFwd0=talonSRX->GetActiveTrajectoryArbFeedFwd(0);
		bool isMotionProfileFinished=talonSRX->IsMotionProfileFinished();
		bool isMotionProfileTopLevelBufferFull=talonSRX->IsMotionProfileTopLevelBufferFull();
		ctre::phoenix::ErrorCode errorCode=talonSRX->GetLastError();
		int firmwareVersion=talonSRX->GetFirmwareVersion();
		bool hasRestOccured=talonSRX->HasResetOccurred();
*/
                usleep(20);
		rclcpp::spin_some(nodeHandle);
        }
}

