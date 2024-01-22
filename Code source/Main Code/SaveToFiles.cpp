#include "Headers/SaveToFiles.h"
#include "Headers/DBMaker.h"

#include <filesystem>
#include <fstream>

SaveFile::SaveFiles::SaveFiles()
{
	printf_s("Start Saveing to files \n");
	auto p = GetCurrentPath();
	p += "\\Server";
	if (!std::filesystem::exists(p)) // check if dir is exists or not create 
		std::filesystem::create_directories(p);

}

SaveFile::SaveFiles::~SaveFiles()
{
	printf_s("Ending Saveing to files \n");
}
/// <summary>
/// Get all vectors 
/// </summary>
/// <param name="Col"></param>
/// <param name="Tabs"></param>
/// <param name="Name"></param>
void SaveFile::SaveFiles::GetAllAttribute(std::vector<DBMaker::Column> Col, std::vector<DBMaker::Tables> Tabs, std::string Name)
{
	m_Col = Col;
	m_Tabs = Tabs;
	m_Name = Name;
	m_PathFiles = GetCurrentPath();
	m_PathFiles += "Server";

	if (!std::filesystem::exists(m_PathFiles))
		printf_s("Error: No dir to save !");

	MakeFilesDB(m_PathFiles);
}

std::filesystem::path SaveFile::SaveFiles::GetCurrentPath()
{
	return std::filesystem::current_path().root_path();
}
/// <summary>
/// create files and open them to load content 
/// </summary>
/// <param name="path"></param>
void SaveFile::SaveFiles::MakeFilesDB(std::filesystem::path path)
{
	intx += intx * rand() % 10 + 2;
	auto a = "\\Server " + std::to_string(intx)+".sql";
	path += a;

	std::ofstream fs(path);

	fs << "CREATE DATABASE " + m_Name + ";" + '\n';
	fs << "USE " + m_Name + ";" + '\n';

	LoadingContent(fs);

	fs.close();
}
/// <summary>
/// Loading Centent to files nad set it 
/// </summary>
/// <param name="of"></param>
void SaveFile::SaveFiles::LoadingContent(std::ofstream& of)
{
	for (size_t i = 0; i < m_Tabs.size(); i++)
	{
		if (m_Tabs[i].NameTables != "")
		{
			of << "CREATE TABLE " + m_Tabs[i].NameTables + " ( " + '\n';
		}

		of << "ID INT NOT NULL ";
		of << "PRIMARY KEY ";
		of << "AUTO_INCREMENT,";
		of << "\n";

		for (size_t j = 0; j < m_Col.size(); j++)
		{
			auto temp = "";

			for (int x = 0; x < m_Col[j].TypeValuse.size(); x++)
				temp += toupper(m_Col[j].TypeValuse[x]);

			if (temp == "FLOAT" || temp == "DOUBLE")
			{
				of << m_Col[j].NameCl + " " + m_Col[j].TypeValuse + "(";
				of << std::to_string(m_Col[j].MaxValue) + std::to_string(m_Col[j].MaxDec) + "),";
				of << "\n";
				continue;
			}
			else if (temp == "BOOL" || temp == "BOOLEAN")
			{
				of << m_Col[j].NameCl + " " + m_Col[j].TypeValuse + ",";
				of << "\n";
				continue;
			}
			if (j == m_Col.size() -1)
			{
				of << m_Col[j].NameCl + " " + m_Col[j].TypeValuse + "(";
				of << std::to_string(m_Col[j].MaxValue) + ")";
				of << "\n";
			}
			else
			{
				of << m_Col[j].NameCl + " " + m_Col[j].TypeValuse + "(";
				of << std::to_string(m_Col[j].MaxValue) + ")," + "\n";
			}
		}
		of << ");";
		of << "\n";
	}
}