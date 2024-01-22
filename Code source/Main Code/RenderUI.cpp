#include <memory>
#include <cctype>
#include <sstream> 

#include "Headers/RenderUI.h"
#include "Headers/DBMaker.h"

#include "ImGui/imgui.h"
#include <iostream>

/// <summary>
/// Main UI Render
/// </summary>
void RenderMainUI::RenderUI()
{
	ImGui::Begin("Main Windos");

	if (ImGui::Button("Make SQL files", ImVec2(100, 150)))
		OpenMaker = true;

	if (OpenMaker)
		RenderUIMaker();

	ImGui::End();
}
// Data
DBMaker::DB* db;

char Buffor[65];
int IntBuffor;

char NameofTypeBuffor[15];
char NameofTablesBuffor[26];
char NameofColumnBuffor[65];

int AmmonTablesBuffor;
int AmmonColumnBuffor;
int MaxValuseBuffor;
int DecimalPoint = 0;
int Index = 0;

bool IsDecimal;
bool DoneTabls = true;
/// <summary>
/// Rendering UI for Make DB name & tables
/// </summary>
void RenderMainUI::RenderUIMaker()
{
	ImGui::Begin("Maker Files", &OpenMaker);

	ImGui::InputText("Name of Database", Buffor, sizeof(Buffor));

	ImGui::InputInt("Ammon Tables", &IntBuffor, sizeof(IntBuffor));

	ImGui::InputText("Name of Tables", NameofTablesBuffor, sizeof(NameofTablesBuffor));

	if (ImGui::Button("Done"))
	{
		NameDB = Buffor;

		if (NameDB != "")
		{
			AmountTables = IntBuffor;
			Index = 0;

			if (db == nullptr)
				db = new DBMaker::DB(NameDB, AmountTables);

			db->TablesMaker(NameofTablesBuffor);
		}
	}

	if(Index < AmountTables)
		if(ImGui::Button("Make Colums"))
		{
			RenderTablesMaker();
			DoneTabls = false;
		}
	
	if (DoneTabls == false)
		RenderTablesMaker();

	if (ImGui::Button("Save datebase"))
	{
		db->SaveFiles();
	}

	RenderTrees(ColumsBufforTrees);

	ImGui::End();
}

/// <summary>
/// render to to make column to tables 
/// </summary>
void RenderMainUI::RenderTablesMaker()
{
	if (Index >= AmountTables)
		return;

	std::stringstream be;
	be << "Tables # " << Index;
	ImGui::Begin(be.str().c_str());

	ImGui::InputText("Name of Column", NameofColumnBuffor, sizeof(NameofColumnBuffor));
	ImGui::InputInt("Give a max range of value", &MaxValuseBuffor, sizeof(MaxValuseBuffor));

	ImGui::InputText("Give Type Column", NameofTypeBuffor, sizeof(NameofTypeBuffor));
	std::string temp;

	IsDecimal = true;
	for (int x = 0; x < strlen(NameofTypeBuffor); x++)
		temp += toupper(NameofTypeBuffor[x]);

	if (temp == "DOUBLE" || temp == "FLOAT")
		ImGui::InputInt("Decimal Point", &DecimalPoint, sizeof(DecimalPoint));

	if (ImGui::Button("Done"))
	{
		DBMaker::Column cl = DBMaker::Column(NameofColumnBuffor, MaxValuseBuffor, NameofTypeBuffor, DecimalPoint);
		cl.SetColum(NameofColumnBuffor, MaxValuseBuffor, NameofTypeBuffor, DecimalPoint);
		DoneTabls = true;
		Index++;
	}
	ImGui::End();
}

void RenderMainUI::RenderTrees(std::vector<DBMaker::Column> ColumsBuffor)
{
	if (!std::empty(NameDB))
		if(ImGui::TreeNode(NameDB.c_str()))
		{
			if (ImGui::TreeNode(NameofTablesBuffor))
			{
				for (size_t i = 0; i < ColumsBuffor.size(); i++)
				{
					if (ImGui::TreeNode((void*)(intptr_t)i, ColumsBuffor[i].NameCl.c_str(), i))
					{
						ImGui::Text("Name: "); ImGui::SameLine();
						ImGui::Text(ColumsBuffor[i].NameCl.c_str());
						ImGui::Text("Max value: "); ImGui::SameLine();
						ImGui::Text(std::to_string(ColumsBuffor[i].MaxValue).c_str());
						ImGui::Text("Type value: "); ImGui::SameLine();
						ImGui::Text(ColumsBuffor[i].TypeValuse.c_str());
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
}