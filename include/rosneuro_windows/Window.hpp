#ifndef ROSNEURO_WINDOWS_HPP
#define ROSNEURO_WINDOWS_HPP

#include <ros/ros.h>
#include <Eigen/Dense>
#include <rosneuro_filters/Filter.hpp>
#include <gtest/gtest_prod.h>

namespace rosneuro {

template <typename T>
class Window : public Filter<T> {
	public:
		Window(void);
		~Window(void) {};
		virtual bool configure(void) = 0;
		virtual DynamicMatrix<T> apply(const DynamicMatrix<T>& in) = 0;
		T GetWindowNorm();

	protected:
		bool is_window_set_;
		T wnorm_;

        FRIEND_TEST(WindowTestSuite, Constructor);
};

template<typename T>
Window<T>::Window(void) {
	this->name_ 	     = "Window";
	this->is_window_set_ = false;
}

template<typename T>
T Window<T>::GetWindowNorm(){
	return this->wnorm_;
}

}

#endif