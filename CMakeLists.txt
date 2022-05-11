cmake_minimum_required(VERSION 3.21)
project(POA_Labo3)

set(CMAKE_CXX_STANDARD 11)

add_executable(POA_Labo3 main.cpp container/Container.hpp container/Container.cpp person/Person.hpp person/Person.cpp container/Boat.cpp container/Boat.hpp container/Bank.cpp container/Bank.hpp Controller.cpp Controller.hpp person/ConstrainedPerson.cpp person/ConstrainedPerson.hpp person/UnconstrainedPerson.cpp person/UnconstrainedPerson.hpp Constants.hpp)
