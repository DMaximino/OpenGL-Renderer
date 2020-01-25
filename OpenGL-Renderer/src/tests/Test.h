#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include "Events/Event.h"

namespace test
{
	class Test 
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(GLCore::Event& e) {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& test);
		virtual void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string& name) 
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

		template <typename T, typename A>
		void RegisterTest(const std::string& name, const A& argument)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, [&argument]() { return new T(argument); }));
		}

	private:
		// The list has to have function because we need to return a new instance that can be cleared once it goes out of scope
		// If we pass a pointer the destructor of the test won't be called when we close the test
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
		Test*& m_CurrentTest;
	};
}