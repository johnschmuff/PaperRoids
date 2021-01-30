/*
Copyright (c) 2010 John Schmuff (www.johnschmuff.com)

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

						**HOW TO USE THE FILE**
Firstly you will need to create the DATA object by calling this in your
code where needed "anything" being any name you choose and "myzip.zip"
being the zip file that you will be loading the data from.
CData anything("myzip.zip");

Next you will need to load the data from the zip file, mostly all the work
here is done for you in this wrapper, so in your main program you would call
the loadData function located in this wrapper class and the argument to pass
is the file to load into memory for SFML to read, in this case "myfile.jpg" can
be any of your files such as "character.png", "hitSound.wav", etc...
anything.loadData("myfile.jpg"); //(Case sensitive)

Next after the file is loaded into memory you will need to load that file into
SFML's image file, this will not show you how to create the image, but rather
load it into the image buffer.
if(!image.loadFromMemory(anything.returnData(), anything.returnSize())
	//Condition here

That is it all you have to do the wrapper class does the rest for cleaning up
and de-initializing PhysicsFS, have fun and happy coding.
*/

#ifndef _CDATA_H
#define _CDATA_H

#pragma once
#include "Physfs.h"
#include <string>

/*
Wrapper class using the Physfs library for reading a file located in an
archive, so that SFML can read the file from memory.
*/
class CData
{
public:
	//Empty contstructor for creating new CData classes
	CData();

	//Constructor to Initialize PhysicsFS and load the data file
	CData(const std::string& data);

	//Cleans up PhysicsFS and DATA class variables
	~CData();

	//Load specified zip file (Same as constructor, but used for multiple zip files)
	void LoadZip(const std::string& data);

	//Load the file into memory and get the size of the file
	bool LoadFile(const std::string& filename);

	//Return the data of the file loaded into memory
	char* ReturnData();

	//Return the size of the file in memory
	int ReturnSize();
private:
	PHYSFS_file* myFile;
	char* myBuf;
	std::string dataFile;
	PHYSFS_sint64 dataSize;
};

#endif