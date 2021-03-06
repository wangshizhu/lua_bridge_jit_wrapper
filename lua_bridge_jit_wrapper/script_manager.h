#ifndef SCRIPT_MANAGER_H_
#define SCRIPT_MANAGER_H_

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include "lua/lua.hpp"
#include "LuaBridge/LuaBridge.h"

extern "C"
{
#include "lua/lua.h"  
#include "lua/lualib.h"
}

#define TRY try{

#define CATCH }catch (luabridge::LuaException const& e){ \
std::cout<<"file:"<<__FILE__<<",line:"<<__LINE__<<",function:"<<__FUNCTION__<<",what:"<<e.what()<<std::endl; \
} \
catch (std::exception& e){ \
std::cout<<"file:"<<__FILE__<<",line:"<<__LINE__<<",function:"<<__FUNCTION__<<",what:"<<e.what()<<std::endl; \
} \
catch (...){ \
std::cout<<"file:"<<__FILE__<<",line:"<<__LINE__<<",function:"<<__FUNCTION__<<std::endl; \
}


namespace lua_script
{
	using TypeLuaRef = std::shared_ptr<luabridge::LuaRef>;
	using TypeFuncMap = std::map<std::string, TypeLuaRef>;

	class ScriptManager
	{
	public:
		explicit ScriptManager(const char* dir);
		~ScriptManager();

		ScriptManager(const ScriptManager&) = delete;
		ScriptManager& operator=(const ScriptManager&) = delete;

	public:
		bool LoadScript();

		template<typename... Args>
		void CallScriptFun(int module_id, const char* func_name, Args&&... args)
		{
			TRY

			auto&& iter = lua_fun_.find(module_id);
			if (iter == lua_fun_.cend())
			{
				return;
			}

			auto&& func_iter = iter->second.find(std::string(func_name));
			if (func_iter == iter->second.cend())
			{
				return;
			}

			(*func_iter->second)(std::forward<decltype(args)>(args)...);

			CATCH
		}

		static void BrowseFileName(const char* dir, std::vector<std::string>& out);

	private:
		std::string dir_;
		lua_State* state_;
		std::map<int, TypeFuncMap> lua_fun_;
	};
}

#endif // !SCRIPT_MANAGER_H_

