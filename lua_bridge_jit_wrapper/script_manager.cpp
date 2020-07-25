#include "script_manager.h"
#include <iostream>
#include <filesystem>

namespace lua_script
{
	ScriptManager::ScriptManager(const char* dir):dir_(dir)
	{
		state_ = luaL_newstate();
		luaL_openlibs(state_);

		lua_fun_.clear();
	}

	ScriptManager::~ScriptManager()
	{
		lua_fun_.clear();
		lua_close(state_);
	}

	bool ScriptManager::LoadScript()
	{
		std::vector<std::string> file_names;
		ScriptManager::BrowseFileName(dir_.c_str(), file_names);
		if (file_names.size() == 0)
		{
			return false;
		}

		for (const auto& name : file_names)
		{
			int result = luaL_dofile(state_, name.c_str());
			if (result != 0)
			{
				std::cout <<"load and do failed,file name:"<<name.c_str() << std::endl;
				continue;
			}

			std::string table_name = luabridge::LuaRef_cast<std::string>(luabridge::LuaRef::fromStack(state_));
			if (table_name.size() == 0)
			{
				std::cout << "Dnt return table name,file name:" << name.c_str() << std::endl;
				continue;
			}

			luabridge::LuaRef table = luabridge::getGlobal(state_, table_name.c_str());
			if (!table.isTable())
			{
				std::cout << "it isnt table,file name:" << name.c_str() << " table name:" << table_name.c_str() << std::endl;
				continue;
			}
			if (!table["module"].isNumber())
			{
				std::cout << "it isnt table,file name:" << name.c_str() << " ,module isnt number"<< std::endl;
				continue;
			}

			int module_id = table["module"].cast<int>();

			TypeFuncMap module_fun;

			table.push(state_);
			lua_pushnil(state_);
			while (lua_next(state_, -2))
			{
				luabridge::LuaRef key = luabridge::LuaRef::fromStack(state_, -2);
				luabridge::LuaRef val = luabridge::LuaRef::fromStack(state_, -1);
				if (val.isFunction())
				{
					auto&& func_name = luabridge::LuaRef_cast<std::string>(key);
					module_fun[func_name] = std::make_shared<luabridge::LuaRef>(val);
				}
				std::cout << "[" << key << "] = " << val << std::endl;
				lua_pop(state_, 1);
			}

			if (module_fun.size() == 0)
			{
				std::cout << "it isnt table,file name:" << name.c_str() << " dont define any function" << std::endl;
				continue;
			}

			lua_fun_.emplace(std::pair<int, TypeFuncMap>(module_id,module_fun));
		}

		return true;
	}

	void ScriptManager::BrowseFileName(const char* dir, std::vector<std::string>& out)
	{
		const std::filesystem::path p{ dir };

		for (const auto& entry : std::filesystem::directory_iterator(p))
		{
			const auto file_name = entry.path().string();

			if (entry.is_directory())
			{
				continue;
			}

			if (entry.is_regular_file())
			{
				out.emplace_back(file_name);
			}
		}
	}
}
