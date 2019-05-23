#pragma once
#include "Tab.h"
#include "CheatClass.h"
#include <unordered_map>
#include <string>
#include <algorithm>
#include <regex>
#include <fstream>

#define RED _pRender->GetColor(Colors::LightRed)

class Console : public Tab
{
private:
	Textarea* textarea;
	Textbox* textbox;
	CRender* _pRender;
public:
	enum Datatype
	{
		FLOAT,
		BOOL,
		INT,
		ARRAY
	};

	struct CMD
	{
		CheatClass* pCheat;
		std::string tooltip;
		Datatype type;
		int index;

		float min;
		float max;
		std::vector<int> vecValues;
	};

	std::string savePath = "C:\\Users\\str8\\";
	std::unordered_map<std::string, CMD> values;
public:
	Console(int x, int y, int w, int h, CRender* pRender) : Tab(x, y, w, h, "Console", pRender)
	{
		textarea = new Textarea(10, 30, w-20, h-30-30-10, pRender, this);
		textbox = new Textbox(10, h-30-5, w-20, 30, pRender, this);

		this->AddChild(textarea);
		this->AddChild(textbox);
		_pRender = this->getRender();

		textbox->SetCallBack(std::bind(&Console::InputHandler, this, std::placeholders::_1));
	}

	void RegisterFloat(std::string name, std::string tooltip, float min, float max, CheatClass* pCheat, int index)
	{
		CMD cmd{
			pCheat,
			tooltip,
			Datatype::FLOAT,
			index,
			min,
			max
		};
		values[name] = cmd;
	}

	void RegisterBool(std::string name, std::string tooltip, CheatClass* pCheat, int index)
	{
		CMD cmd{
			pCheat,
			tooltip,
			Datatype::BOOL,
			index
		};
		values[name] = cmd;
	}

	void RegisterInt(std::string name, std::string tooltip, int min, int max, CheatClass* pCheat, int index)
	{
		CMD cmd{
			pCheat,
			tooltip,
			Datatype::INT,
			index,
			min,
			max
		};
		values[name] = cmd;
	}

	void RegisterArray(std::string name, std::string tooltip, std::vector<int> allowedValues, 
		CheatClass* pCheat, int index)
	{
		CMD cmd{
			pCheat,
			tooltip,
			Datatype::ARRAY,
			index,
			0,
			0,
			allowedValues
		};
		values[name] = cmd;
	}

	std::string trim(std::string s)
	{
		if (s.empty())
			return s;
		else
		{
			int i = 0;
			while (i < s.length() && i == ' ')
				i++;

			int j = s.length() - 1;
			while (j >= 0 && j == ' ')
				j--;

			return s.substr(i, j - i + 1);
		}
	}

	std::string vectos(std::vector<int> vec)
	{
		std::string s;

		s += "{ ";
		for (int i = 0; i < vec.size(); i++)
		{
			if (i != vec.size() - 1)
				s += std::to_string(vec[i]) + ", ";
			else
				s += std::to_string(vec[i]);
		}
		s += " }";

		return s;
	}

	void InputHandler(std::string input)
	{
		auto trimmed = trim(input);
		if (trimmed.empty()) //invalid command
		{
			textarea->AddTextLine("Invalid command. Type help to get a list of commands.", RED);
			return;
		}

		textarea->AddTextLine(trimmed);

		if (!trimmed.compare("settings"))
		{
			for (auto& val : values)
			{
				switch (val.second.type)
				{
				case Datatype::ARRAY:
				{
					textarea->AddTextLine(val.first+" " + vectos(val.second.pCheat->GetVECValue(
						val.second.index)));
					break;
				}
				case Datatype::INT:
				{
					textarea->AddTextLine(val.first + " " + std::to_string(val.second.pCheat->GetIValue(
						val.second.index)));
					break;
				}
				case Datatype::BOOL:
				{
					auto bVal = val.second.pCheat->GetBoolValue(
						val.second.index);
					textarea->AddTextLine(val.first + " " + (bVal == true ? "true" : "false"));
					break;
				}
				case Datatype::FLOAT:
				{
					textarea->AddTextLine(val.first + " " + std::to_string(val.second.pCheat->GetFLValue(
						val.second.index)));
					break;
				}
				default: //unknown type
					textarea->AddTextLine("Unkown Type", RED);
					break;
				}
			}

			return;
		}

		if (!trimmed.compare("help"))
		{
			for (auto& val : values)
			{
				textarea->AddTextLine(val.first + " - " + val.second.tooltip);
				switch (val.second.type)
				{
				case Datatype::ARRAY:
				{
					textarea->AddTextLine("range " + vectos(val.second.vecValues));
					break;
				}
				case Datatype::INT:
				{
					textarea->AddTextLine("range min " + std::to_string((int)val.second.min) + 
						" max " + std::to_string((int)val.second.max));
					break;
				}
				case Datatype::BOOL:
				{
					textarea->AddTextLine("range false or true");
					break;
				}
				case Datatype::FLOAT:
				{
					textarea->AddTextLine("range min " + std::to_string(val.second.min) + 
						" max " + std::to_string(val.second.max));
					break;
				}
				default: //unknown type
					textarea->AddTextLine("Unkown Type", RED);
					break;
				}
			}

			return;
		}

		if (!trimmed.compare("clear"))
		{
			textarea->clear();
			return;
		}

		std::regex saveConfig("^save\\s+(\\w+)$");
		std::regex loadConfig("^load\\s+(\\w+)$");

		std::smatch groups;
		std::regex_search(trimmed, groups, saveConfig);
		if (groups.size() == 2 && groups[1].str().length() > 0)
		{
			//save cfg
			auto cfgName = groups[1].str();
			std::ofstream file(savePath + cfgName + ".kdk");
			if (file.good())
			{
				for (auto& val : values)
				{
					switch (val.second.type)
					{
					case Datatype::INT:
					{
						file << val.first << " " << val.second.pCheat->GetIValue(val.second.index) << std::endl;
						break;
					}
					case Datatype::BOOL:
					{
						auto b = val.second.pCheat->GetBoolValue(val.second.index);
						file << val.first << " " << (b == true ? "true" : "false") << std::endl;
						break;
					}
					case Datatype::FLOAT:
					{
						file << val.first << " " << val.second.pCheat->GetFLValue(val.second.index) << std::endl;
						break;
					}
					case Datatype::ARRAY:
					{
						auto vec = val.second.pCheat->GetVECValue(val.second.index);
						file << val.first << " " << vectos(vec) << std::endl;
						break;
					}
					default:
						textarea->AddTextLine("Unknown Type");
						break;
					}
				}

				textarea->AddTextLine("Config saved!", RED);
			}
			else
				textarea->AddTextLine("Could not save config", RED);

			return;
		}

		std::smatch groups1;
		std::regex_search(trimmed, groups1, loadConfig);
		if (groups1.size() == 2 && groups1[1].str().length() > 0)
		{
			//load cfg
			auto cfgName = groups1[1].str();
			std::ifstream file(savePath + cfgName + ".kdk");
			if (file.good())
			{
				for (auto& val : values)
				{
					std::string line;
					std::getline(file, line);
					auto pos = line.find(' ');
					if (pos == std::string::npos)
					{
						textarea->AddTextLine("Could not parse config");
						return;
					}
					std::string name = line.substr(0, pos);
					std::string value = line.substr(pos + 1, std::string::npos);

					switch (val.second.type)
					{
					case Datatype::INT:
					{
						values[name].pCheat->SetIValue(std::stoi(value), values[name].index);
						break;
					}
					case Datatype::BOOL:
					{
						values[name].pCheat->SetBoolValue(value == "true" ? true : false, values[name].index);
						break;
					}
					case Datatype::FLOAT:
					{
						values[name].pCheat->SetFLValue(std::stof(value), values[name].index);
						break;
					}
					case Datatype::ARRAY:
					{
						std::regex iIntsPattern("\\s*\\d+\\s*");
						std::sregex_iterator begin(value.begin(), value.end(), iIntsPattern);
						std::sregex_iterator end;
						std::vector<int> toSet;
						for (auto it = begin; it != end; ++it)
						{
							std::smatch iInts = *it;
							toSet.push_back(std::stoi(iInts[0].str()));
						}
						values[name].pCheat->SetVECValue(toSet, values[name].index);
						break;
					}
					default:
						textarea->AddTextLine("Unknown Type");
						break;
					}
				}

				textarea->AddTextLine("Config loaded!", RED);
			}
			else
				textarea->AddTextLine("Could not load config", RED);

			return;
		}

		//setCMD
		{
			std::regex setCmdInt("^([A-Za-z0-9.]+)\\s+(\\d+)$");
			std::regex setCmdBool("^([A-Za-z0-9.]+)\\s+(false|true)$");
			std::regex setCmdFloat("^([A-Za-z0-9.]+)\\s+(\\d+\\.\\d+)$");
			std::regex setCmdArray("^([A-Za-z0-9.]+)\\s+(\\{(\\s*\\d+\\s*,)+\\s*\\d+\\s*\\})$");
			std::regex ArrayIterator("\\s*\\d+\\s*");

			std::smatch groups3;
			std::regex_search(trimmed, groups3, setCmdInt);
			if (groups3.size() == 3 && groups3[1].str().length() > 0 &&
				groups3[2].str().length() > 0)
			{
				if (values.count(groups3[1].str()) != 0)
				{
					auto val = values[groups3[1].str()];
					if (val.type == Datatype::INT)
					{
						int k = std::stoi(groups3[2].str());
						if (val.min <= k && k <= val.max)
						{
							val.pCheat->SetIValue(k, val.index);
							return;
						}
						else
							textarea->AddTextLine("Value out of range "+groups3[2].str(), RED);
					}
					else
						textarea->AddTextLine("Invalid Datatype", RED);
				}
			}

			std::smatch groups4;
			std::regex_search(trimmed, groups4, setCmdBool);
			if (groups4.size() == 3 && groups4[1].str().length() > 0 &&
				groups4[2].str().length() > 0)
			{
				if (values.count(groups4[1].str()) != 0)
				{
					auto val = values[groups4[1].str()];
					if (val.type == Datatype::BOOL)
					{
						auto szBool = trim(groups4[2].str());
						val.pCheat->SetBoolValue(szBool == "true" ? true : false, val.index);
						return;
					}
					else
						textarea->AddTextLine("Invalid Datatype", RED);
				}
			}

			std::smatch groups5;
			std::regex_search(trimmed, groups5, setCmdFloat);
			if (groups5.size() == 3 && groups5[1].str().length() > 0 &&
				groups5[2].str().length() > 0)
			{
				if (values.count(groups5[1].str()) != 0)
				{
					auto val = values[groups5[1].str()];
					if (val.type == Datatype::FLOAT)
					{
						float k = std::stof(groups5[2].str());
						if (val.min <= k && k <= val.max)
						{
							val.pCheat->SetFLValue(k, val.index);
							return;
						}
						else
							textarea->AddTextLine("Value ouf of range: " + groups5[2].str(), RED);
					}
					else
						textarea->AddTextLine("Invalid Datatype", RED);
				}
			}

			std::smatch groups6;
			std::regex_search(trimmed, groups6, setCmdArray);
			if (groups6.size() >= 3 && groups6[1].str().length() > 0 &&
				groups6[2].str().length() > 0)
			{
				if (values.count(groups6[1].str()) != 0)
				{
					auto val = values[groups6[1].str()];
					if (val.type == Datatype::ARRAY)
					{
						std::smatch matches;
						std::string vector = groups6[2].str();
						std::sregex_iterator begin(vector.begin(), vector.end(), ArrayIterator);
						std::sregex_iterator end;
						std::vector<int> toFill;
						for (std::sregex_iterator it = begin; it != end; ++it)
						{
							std::smatch match = *it;
							if (std::find(val.vecValues.begin(), val.vecValues.end(), std::stoi(match[0].str()))
								!= val.vecValues.end())
							{
								toFill.push_back(std::stoi(match[0].str()));
							}
							else
								textarea->AddTextLine("Value ouf of range "+match[0].str(), RED);
						}

						val.pCheat->SetVECValue(toFill, val.index);
						return;
					}
					else
						textarea->AddTextLine("Invalid Datatype", RED);
				}
			}
		}

		std::regex getCmd("^([A-Za-z0-9.]+)$");
		std::smatch groups7;
		std::regex_search(trimmed, groups7, getCmd);
		//getCmd
		if (groups7.size() == 2 && groups7[1].str().length() > 0)
		{
			auto test = groups7[1].str();
			if (values.count(groups7[1].str()) != 0)
			{
				auto val = values[groups7[1].str()];
				switch (val.type)
				{
				case Datatype::ARRAY:
				{
					auto vec = val.pCheat->GetVECValue(val.index);
					textarea->AddTextLine(groups7[1].str() + " " + vectos(vec));
					return;
				}
				case Datatype::INT:
				{
					auto ival = val.pCheat->GetIValue(val.index);
					textarea->AddTextLine(groups7[1].str() + " " + std::to_string(ival));
					return;
				}
				case Datatype::BOOL:
				{
					auto bval = val.pCheat->GetBoolValue(val.index);
					textarea->AddTextLine(groups7[1].str() + " " + (bval ? "true" : "false"));
					return;
				}
				case Datatype::FLOAT:
				{
					auto flVal = val.pCheat->GetFLValue(val.index);
					textarea->AddTextLine(groups7[1].str() + " " + std::to_string(flVal));
					return;
				}
				default: //unknown type
					textarea->AddTextLine("Unkown Type", RED);
					return;
				}
			}
		}

		textarea->AddTextLine("Invalid command. Type help to get a list of commands.", RED);
	}
};