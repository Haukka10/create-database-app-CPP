#pragma once

#include <string>
#include "Headers/DBMaker.h"

namespace RenderMainUI
{
	void RenderUI();

	void RenderUIMaker();

	void RenderTablesMaker();

	void RenderTrees(std::vector<DBMaker::Column> ColumsBuffor);
	
	inline bool OpenMaker = false;
	inline std::string NameDB;
	inline uint64_t AmountTables = 0;
	inline std::vector<DBMaker::Column> ColumsBufforTrees;
	inline bool IsStartSaveing = false;
	
}