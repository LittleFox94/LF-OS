#include <lf_ffs.h>

LF_FFS::LF_FFS(char *buffer)
{
	_buffer = buffer;

	_header = *((LF_FFS_HEADER_T*)buffer);
	
	if(_header.magic != LF_FFS_MagicNumber)
	{
		//cout << (char*)"The given file is not a valid LF FFS File!\n";
		_isValid = false;
		return;
	}
	
	if(_header.countFiles > 1024)
	{
		/*cout << (char*)"The given file contains more than 1024 files.\n"
				"Because of limitations in memory management LF OS RC can't handle them ...\n"
				"Only the first 1024 files will be accessible. Sorry.\n";*/
	}
	
	for(uint64_t i = 0; i < _header.countFiles && i < 1024; i++)
	{
		_files[i] = *((LF_FFS_ENTRY_T*)(buffer + sizeof(_header) + (i * sizeof(LF_FFS_ENTRY_T))));
	}
	
	_isValid = true;
}

uint64_t LF_FFS::get_CountFiles()
{
	return _header.countFiles;
}

LF_FFS_ENTRY_T *LF_FFS::get_Files()
{
	return _files;
}

bool LF_FFS::get_Valid()
{
	return _isValid;
}

void *LF_FFS::getFileBufferAddr(char *fileName)
{
	bool found = false;

	unsigned int i;
	for(i = 0; i < _header.countFiles && i < 1023; i++)
	{
		char temp[256];
		memcpy(temp, (char*)_files[i].filename, 255);
		temp[255] = 0;
		
		if(strcmp(temp, fileName) == 0)
		{
			found = true;
			break;
		}
	}
	
	if(found)
		return (char*)(_buffer + _files[i].offset);
	else
		return 0;
}

int LF_FFS::getFileSize(char *fileName)
{
	bool found = false;

	unsigned int i;
	for(i = 0; i < _header.countFiles && i < 1023; i++)
	{
		char temp[256];
		memcpy(temp, (char*)_files[i].filename, 255);
		temp[255] = 0;
		
		if(strcmp(temp, fileName) == 0)
		{
			found = true;
			break;
		}
	}
	
	if(found)
		return (int)_files[i].size;
	else
		return 0;
}
