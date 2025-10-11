#pragma once
#include <Core/Manager.h>
#include <unordered_map>
#include <string>

namespace Core
{
	class SaveManager : public Manager
	{
	public:
		SaveManager(Scene* scene) : Manager(scene) {}
		void loadFromDisk();
		void saveToDisk();
		void deleteSave();

		void set(const std::string& key, const std::string& value);
		const std::string& get(const std::string& key, const std::string& defaultValue);
	private:
		const std::string SAVE_PATH = "save.txt";
		const char DELIMITER = '=';
		std::unordered_map< std::string, std::string> m_data;
	};
}