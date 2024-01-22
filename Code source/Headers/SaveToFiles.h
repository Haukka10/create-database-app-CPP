#pragma once
#include <filesystem>
#include <string>
#include "Headers/DBMaker.h"

namespace SaveFile
{
	class SaveFiles
	{
	public:
		SaveFiles();
		~SaveFiles();
		void GetAllAttribute(std::vector<DBMaker::Column> Col, std::vector<DBMaker::Tables> Tabs, std::string Name);

	private:
		uint16_t index = 0;
		uint16_t intx = rand() % 100;
		std::filesystem::path m_PathFiles;
		std::string m_Name;

		std::filesystem::path GetCurrentPath();

		void MakeFilesDB(std::filesystem::path path);

		void LoadingContent(std::ofstream& of);

		std::vector<DBMaker::Column> m_Col;
		std::vector<DBMaker::Tables> m_Tabs;

	};

}