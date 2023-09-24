#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace mk {
	class JsonBridge {
		std::string m_file_path;

	public:
		nlohmann::json data;

		bool        load(const std::string &filePath);
		bool        saveCurrentState();
		std::string getFilePath() const;
	};
}  // namespace mk
