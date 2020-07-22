
[luajit2]:https://github.com/openresty/luajit2
[luabridge]:https://github.com/vinniefalco/LuaBridge
### 概述
--------------------------------------------------

本源码使用Openresty维护的[Luajit2][Luajit2]，同时使用[LuaBridge][luabridge]，宿主语言使用C++

### 版本要求
--------------------------------------------------

Luajit2版本：v2.1-agentzh
LuaBridge版本：2.5

使用了C++17的特性，编译器至少支持到C++17

Linux使用了CMake构建，要求CMake最低版本3.16
	