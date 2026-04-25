#pragma once

#include <iostream>
#include <string>

#include "istack/istack.h"

namespace compiler
{
	std::string n_lastAguments = "";

	bool DataParse(char* string, unsigned int stringLength, ist::IstackUnit* unit)
	{
		std::string stringName = "";
		std::string stringArg = "";
		int parsingMode = 0; //parse mode 0 = parseing module name, parse mode 1 = parsing argument, parse mode 2 = null

		for (size_t i = 0; i < stringLength; i++)
		{
			if (string[i] == ')') { parsingMode = 2; }

			if (parsingMode == 1)
			{
				stringArg = stringArg + string[i];
			}

			if (string[i] == '(') { parsingMode = 1; }

			if (parsingMode == 0 && string[i] != ';')
			{
				stringName = stringName + string[i];
			}
		}

		n_lastAguments = stringArg;

		if (parsingMode == 1)
		{
			return false;
		}

		if ((stringArg[0] == '"' && stringArg[stringArg.length() - 1] == '"') || (stringArg[0] == '\'' && stringArg[stringArg.length() - 1] == '\''))
		{
			if (stringName == "Byte" || stringName == "FourByte")
			{
				return false;
			}

			unit->m_data = new std::string();
			(*((std::string*)unit->m_data)) = stringArg.substr(1, stringArg.length() - 2);
			return true;
		}



		if (stringArg == "")
		{
			return true;
		}

		if (stringArg == "true")
		{
			if (stringName == "FourByte" || stringName == "String")
			{
				return false;
			}

			unit->m_data = new bool;
			(*((bool*)unit->m_data)) = true;
			return true;
		}

		if (stringArg == "false")
		{
			if (stringName == "FourByte" || stringName == "String")
			{
				return false;
			}

			unit->m_data = new bool;
			(*((bool*)unit->m_data)) = false;
			return true;
		}

		try
		{
			int data = std::stoi(stringArg);

			unit->m_data = new int();
			(*((int*)unit->m_data)) = data;

			if (stringName == "Byte" || stringName == "String")
			{
				return false;
			}
		}
		catch (...)
		{
			try
			{
				float data = std::stof(stringArg);

				unit->m_data = new float();
				(*((float*)unit->m_data)) = data;

				if (stringName == "Byte" || stringName == "String")
				{
					return false;
				}
			}
			catch (...)
			{
				return false;
			}
		}

		return true;
	}
}
