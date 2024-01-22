#include "Headers/DBMaker.h"
#include "Headers/RenderUI.h"
#include "Headers/SaveToFiles.h"

#include <string>


DBMaker::Tables tb;
/// <summary>
/// Constructor DB
/// </summary>
/// <param name="Name"></param>
/// <param name="amount"></param>
DBMaker::DB::DB(std::string Name, uint64_t amount)
{
	this->m_AmountTables = amount;
	this->m_NameBD = Name;
	LoginDebug();
}
/// <summary>
/// Push to vector new tables name 
/// </summary>
/// <param name="Name"></param>
void DBMaker::DB::TablesMaker(std::string Name)
{
	tb.NameTables = Name;
	Tabs.push_back(tb);
}
/// <summary>
/// Start Saveing files 
/// </summary>
void DBMaker::DB::SaveFiles()
{
	SaveFile::SaveFiles sf;
	sf.GetAllAttribute(tb.Columns,Tabs,m_NameBD);
}
/// <summary>
/// Debug log 
/// </summary>
void DBMaker::DB::LoginDebug()
{
	auto a = m_AmountTables;
	auto b = "Name :" + m_NameBD;
	
	auto c = std::to_string(a);
	c += '\n';
	printf_s(c.c_str());
	printf_s(b.c_str());
}
/// <summary>
/// Set columns to vector 
/// </summary>
/// <returns></returns>
std::vector<DBMaker::Column> DBMaker::Tables::GetColumns()
{
	for (size_t i = 0; i < Columns.size(); i++)
	{
		auto a = Columns[i].NameCl;
		printf_s(a.c_str());
	}
	ColumnsBuffor = Columns;
	RenderMainUI::ColumsBufforTrees = ColumnsBuffor;
	return Columns;
}
/// <summary>
/// Constructor Columns 
/// </summary>
/// <param name="Name"></param>
/// <param name="maxValue"></param>
/// <param name="mypeValues"></param>
/// <param name="maxDec"></param>
DBMaker::Column::Column(std::string Name, uint32_t maxValue, std::string mypeValues, int maxDec)
{
	this->NameCl = Name;
	this->MaxDec = maxDec;
	this->TypeValuse = mypeValues;
	this->MaxValue = maxValue;
}

void DBMaker::Column::SetColum(std::string Name, uint32_t maxValue, std::string mypeValues, int maxDec)
{
	tb.Columns.push_back(Column(Name,maxValue,mypeValues,maxDec));
	tb.GetColumns();
}