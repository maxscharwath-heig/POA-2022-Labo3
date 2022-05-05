cmake_minimum_required(VERSION 3.21)
project(POA_Labo3)

set(CMAKE_CXX_STANDARD 11)

add_executable(POA_Labo3 main.cpp Container.hpp Container.cpp person/Person.hpp person/Person.cpp Boat.cpp Boat.hpp Bank.cpp Bank.hpp Controller.cpp Controller.hpp person/Child.cpp person/Child.hpp person/GenderedPerson.cpp person/GenderedPerson.hpp person/Thief.cpp person/Thief.hpp person/Police.cpp person/Police.hpp person/Parent.cpp person/Parent.hpp constraint/Constraint.cpp constraint/Constraint.hpp constraint/ChildConstraint.cpp constraint/ChildConstraint.hpp constraint/ThiefConstraint.cpp constraint/ThiefConstraint.hpp)
