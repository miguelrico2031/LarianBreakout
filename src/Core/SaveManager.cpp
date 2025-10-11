#include <Core/SaveManager.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iostream>

namespace Core
{
	void SaveManager::loadFromDisk()
	{
		m_data.clear();
		std::ifstream file(SAVE_PATH);
		if (!file.is_open())
		{
			std::cout << "No save file found.\n";
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				continue;
			}
			auto delimiterPos = line.find(DELIMITER);
			if (delimiterPos == std::string::npos)
			{
				continue;
			}
			auto key = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);
			m_data[key] = value;
		}
		file.close();
		std::cout << "Save file loaded.\n";
	}

	void SaveManager::saveToDisk()
	{
		std::ofstream file(SAVE_PATH);
		if (!file.is_open())
		{
			std::cout << "Error opening save file for writing.\n";
			return;
		}
		for (const auto& [k, v] : m_data)
		{
			file << k << DELIMITER << v << '\n';
		}
		file.close();
		std::cout << "Save file saved.\n";
	}

	void SaveManager::deleteSave()
	{
		m_data.clear();
		std::remove(SAVE_PATH.c_str()); //delete the file
	}

	void SaveManager::set(const std::string& key, const std::string& value)
	{
		m_data[key] = value;
	}

	const std::string& SaveManager::get(const std::string& key, const std::string& defaultValue)
	{
		auto it = m_data.find(key);
		return it != m_data.end()
			? it->second
			: defaultValue;
	}


}