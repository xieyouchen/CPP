cmake_minimum_required(VERSION 3.10.0)
project(CPP VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)  # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 确保使用指定的标准

add_executable(Singleton DesignMode/Singleton.cpp)
add_executable(Observer DesignMode/Observer.cpp)
add_executable(Factory DesignMode/Factory.cpp)
add_executable(Strategy DesignMode/Strategy.cpp)

add_executable(main main.cpp)
add_executable(Template Template.cpp)
add_executable(Ununiversal_References Ununiversal_References.cpp)
add_executable(Polymorphism Polymorphism_static.cpp)
add_executable(EventDispatcher EventDispatcher.cpp)
add_executable(EventDispatcher_Observer EventDispatcher_Observer.cpp)
add_executable(Vector Vector.cpp)
add_executable(VectorBool VectorBool.cpp)
add_executable(Emplace Emplace.cpp)
add_executable(Hash Hash_TemplateSpecialize.cpp)
add_executable(Sort Sort.cpp)
add_executable(UniquePtr UniquePtr.cpp)
add_executable(CPP_Grammar CPP_Grammar.cpp)
add_executable(TimerManager TimerManager.cpp)
# add_executable(tmp tmp.cpp)
add_executable(SharedPtr SharedPtr.cpp)
add_executable(SharedPtr_WeakPtr SharedPtr_WeakPtr.cpp)

############## C ##############

add_executable(C_Pointer C/Pointer.cpp)
add_executable(C_VirtualTable C/VirtualTable.cpp)

########## DEMO 
add_executable(DEMO_MyThreadPool DEMO/MyThreadPool.cpp)
target_link_libraries(DEMO_MyThreadPool pthread) # ThreadPool 专属，因为调用了 Linux 的 POSIX 底层API



