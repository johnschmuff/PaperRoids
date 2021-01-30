#include "CData.h"

CData::CData()
{
}

CData::CData(const std::string& data)
{
	//Initialize PhysFS
	PHYSFS_init(NULL);
	this->dataSize = 0;
	this->dataFile = "";
	this->myBuf = "";

	//Set the data file to be opened
	this->dataFile = data;

	//Add the data file in the search path and set to 0 to be read first
	PHYSFS_addToSearchPath(this->dataFile.c_str(), 0);
}

CData::~CData()
{
	//Clean up specific files and deinitialize PhysicsFS
	PHYSFS_deinit();
	delete myBuf;
}

void CData::LoadZip(const std::string& data)
{
	//Set the data file to be opened
	this->dataFile = data;

	//Add the data file in the search path and set to 0 to be read first
	PHYSFS_addToSearchPath(this->dataFile.c_str(), 0);
}

bool CData::LoadFile(const std::string& filename)
{
	//Check whether file exist
	if(!PHYSFS_exists(filename.c_str()))
	{
		return false;
	}
	else
	{
		//Read the file
		this->myFile = PHYSFS_openRead(filename.c_str());

		//Read the file into memory
		this->myBuf = new char[PHYSFS_fileLength(this->myFile)];

		//Get the size of the file in memory
		this->dataSize = PHYSFS_read(this->myFile, this->myBuf, 1, PHYSFS_fileLength(this->myFile));

		//Close the file
		PHYSFS_close(this->myFile);
	}

	return true;
}

char* CData::ReturnData()
{
	//Return the data of the file in memory
	return this->myBuf;
}

int CData::ReturnSize()
{
	//Return the size of the file loaded
	return this->dataSize;
}