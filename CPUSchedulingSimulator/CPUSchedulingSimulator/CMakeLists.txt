cmake_minimum_required(VERSION 3.26)
project(CPUSchedulingSimulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPUSchedulingSimulator
        Main.cpp
        PrioritySchedulerP.cpp
        CSVReader.h
        FCFS.h
        MLFQ.h
        MLQ.h
        PrioritySchedulerNP.h
        PrioritySchedulerP.h
        Process.h
        RoundRobin.h
        SJF.h
        PrioritySchedulerP.h
)
