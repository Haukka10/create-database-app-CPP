#pragma once

#include <string>
#include <vector>

namespace DBMaker
{
	class Column
	{
		public:
			Column(std::string Name, uint32_t maxValue, std::string mypeValues, int maxDec = 0);
			void SetColum(std::string Name, uint32_t maxValue, std::string mypeValues, int maxDec);
			std::string NameCl;
			uint32_t MaxValue;
			std::string TypeValuse;
			uint32_t MaxDec;
		private:
	};

	class Tables
	{
		public:
			std::vector<DBMaker::Column> GetColumns();
			std::vector<Column> Columns;
			std::string NameTables;
		private:
			std::vector<Column> ColumnsBuffor;
	};

	class DB
	{
		public:
			DB(std::string Name, uint64_t amount);
			void TablesMaker(std::string Name);
			std::vector<Tables> Tabs;
			void SaveFiles();
			std::string m_NameBD;
			uint64_t m_AmountTables;

		private:
			void LoginDebug();
	};
}