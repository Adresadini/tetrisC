#include "Logger.h"

Logger::Logger(std::ostream& os, Level minimumLevel)
	: os(os), minimumLevel(minimumLevel)
{
}

void Logger::log(const std::string& message, Level level)
{
	if (level >= minimumLevel)
		os << message << std::endl;
}

void Logger::setMinimumLogLevel(Level minimumLevel)
{
	this->minimumLevel = minimumLevel;
}