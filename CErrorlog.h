/*
Copyright(c) 2010 John Schmuff (www.johnschmuff.com)

MIT License:
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _CERRORLOG_H
#define _CERRORLOG_H

#pragma once
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>

/*
Simple error logging class, that will output the error message to a Errorlog.txt file
in the specific format of date:time:error.
*/
class CErrorlog
{
public:
	//Constructor to initialize the logging parameters for time and filename
	CErrorlog()
	{
		this->m_filename = "Errorlog.txt";
		time(&this->m_rawTime);
		this->m_pTM = new tm(*localtime(&this->m_rawTime));
	}

	//Deconstructor to clean up the class pointers
	~CErrorlog()
	{
		delete this->m_pTM;
	}

	//Simple function to open the log file and write the error to the file
	//than close it after error has been written.
	void Error(const std::string& error)
	{
		this->m_outFile.open(this->m_filename, std::ios::app);
		if(this->m_outFile)
		{
			int hour = 0;
			std::string flag = "";
			if(this->m_pTM->tm_hour % 24 > 12)
			{
				hour = this->m_pTM->tm_hour - 12;
				flag = "pm";
				if(hour == 12)
				{
					flag = "am";
				}
			}
			else
			{
				flag = "am";
				if(this->m_pTM->tm_hour == 12)
				{
					flag = "pm";
				}
			}

			this->m_outFile << this->m_pTM->tm_mon + 1 << "/" << this->m_pTM->tm_mday <<  "/" << this->m_pTM->tm_year + 1900 << "::";
			this->m_outFile << hour; 
			if(this->m_pTM->tm_min < 10)
			{
				this->m_outFile << ":" << "0" << this->m_pTM->tm_min;
			}
			else
			{
				this->m_outFile << ":" << this->m_pTM->tm_min;
			}
			this->m_outFile << "." << this->m_pTM->tm_sec << flag << "::";
			this->m_outFile << error << std::endl;

			this->m_outFile.close();
		}
	}
private:
	std::ofstream m_outFile;
	std::string m_filename;
	time_t m_rawTime;
	tm* m_pTM;
};

#endif