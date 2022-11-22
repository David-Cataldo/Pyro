#pragma once

#include <fstream>
#include <string>

#include "Pyro/Log.h"

namespace Pyro
{
    inline std::string ReadFile(std::string loc)
    {
        std::string content;
        std::ifstream fileStream(loc, std::ios::in);

        if (!fileStream.is_open())
        {
            PY_ERROR("Failed to read %s! File doesn't exist.", loc);
            return "";
        }

        std::string line = "";
        while (!fileStream.eof())
        {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }
}