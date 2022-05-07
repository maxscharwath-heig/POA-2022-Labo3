cmake_minimum_required(VERSION 3.21)
project(POA_Labo3)

set(CMAKE_CXX_STANDARD 11)

add_executable(POA_Labo3 main.cpp Container.hpp Container.cpp person/Person.hpp person/Person.cpp Boat.cpp Boat.hpp Bank.cpp Bank.hpp Controller.cpp Controller.hpp person/ConstrainedPerson.cpp person/ConstrainedPerson.h person/UnconstrainedPerson.cpp person/UnconstrainedPerson.h)
