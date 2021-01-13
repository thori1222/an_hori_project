#pragma once


#include <vector>
#include <fstream>
#include <string>

namespace RTCLib {

	/// CSV loader for double matrix
	/// Only clean formatted CSV file can be loaded.
	class SimpleCSVLoader
	{
	public:

		static const size_t buffer_size = 32 * 1024;
		bool isPathLooping = false;
		std::vector<std::string> tags;
		std::vector<std::vector<double> > data;

	public:
		void LoadPathFromCSV(std::string fn, bool tag_exist = true, size_t skipline_before_tag = 0)
		{
			std::ifstream ifs(fn, std::ios::in);

			//if (ifs.fail())throw std::exception("File is not found");
			if (ifs.fail())throw std::runtime_error("File is not found");
			
			size_t i = skipline_before_tag;
			std::string tmp;
			while (i > 0)
			{	// read and discard skipping lines
				std::getline(ifs, tmp);
			}

			// load tag
			if (tag_exist)
				LoadTagLine(ifs);

			LoadBodyLine(ifs);
		}

		void LoadTagLine(std::ifstream& ifs)
		{
			// load header line
			char buf[buffer_size];
			ifs.getline(buf, buffer_size - 1);
			if (tags.size() > 0)
			{
				tags.clear();
			}

			char* ctx = nullptr;
			char delim[] = ",";
			char *next = strtok_r(buf, delim, &ctx);

			while (next) {
				std::string tmp(next);
				tags.push_back(tmp);

				next = strtok_r(NULL, delim, &ctx);
			}
		}

		void LoadBodyLine(std::ifstream& ifs)
		{
			// load line
			char buf[buffer_size];
			size_t nline = 0;
			while (ifs.getline(buf, buffer_size - 1))
			{
				//if (strcmpi(buf, "loop")==0)
				//{
				//	isPathLooping = true;
				//	break;
				//}
				ParseLine(buf);
				nline++;
				//if (_strcmpi(buf, "") == 0)break;
			}

		}

		void ParseLine(char buf[])
		{
			std::vector<double>	data_line;

			char* ctx = nullptr;
			char delim[] = ",";
			char *next = strtok_r(buf, delim, &ctx);

			while (next) {
				double tmp_data = 0;
				//try {
				tmp_data = atof(next);
				//}
				//catch (...) {
				//	if (strcmpi(next, "loop")==0)
				//	{
				//		isPathLooping = true;
				//		break;
				//	}
				//	throw;
				//}
				data_line.push_back(tmp_data);

				next = strtok_r(NULL, delim, &ctx);
			}
			if (data_line.size() >= 6)
				data.push_back(data_line);
		}
	};
}
