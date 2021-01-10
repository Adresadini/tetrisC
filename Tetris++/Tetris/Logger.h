#pragma once

#include <string>
#include <iostream>

#ifdef LOGGING_EXPORTS
#define LOGGING_API _declspec(dllexport)
#else
#define LOGGING_API _declspec(dllimport)
#endif


class LOGGING_API Logger
{
public:
	enum class Level
	{
		Info,
		Warning,
		Error
	};

public:
	Logger(std::ostream& os, Level minimumLevel = Level::Info);

	void log(const std::string& message, Level level);

	void setMinimumLogLevel(Level minimumLevel);

private:
	std::ostream& os;
	Level minimumLevel;
};

