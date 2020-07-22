#include <iostream>
#include "script_manager.h"

int main()
{
	{
		lua_script::ScriptManager sm("../script/src");

		if (!sm.LoadScript())
		{
			std::cout << "load faild" << std::endl;
		}

		sm.CallScriptFun(1, "test_func_1",10,"joey");
	}

	system("pause");
	return 0;
}