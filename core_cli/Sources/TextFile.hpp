#ifndef _File_h_
#define _File_h_

#include "Common.hpp"

namespace Core
{

//class Library;

template<class T>
extern std::string atos(T _t);

class TextFile
{
public:
	explicit TextFile();

	explicit TextFile(std::string fileName);

	virtual ~TextFile();

public:
	void print();

	virtual void write(std::string text);

	virtual void clear();

	static void write(std::string text, std::string name);

	static void clear(std::string name);

	void copyByStrokes();

	void copyByStrokes(std::string name);

//	void copyByWords();

//	void copyByWords(std::string fileName);

	virtual void setName(std::string name);

protected:
	std::string fileName;
	std::string fullPath;
	std::string mode;
	std::vector<std::string> fileCopy;

};
// class File;
} /* namespace Core */

#endif // #ifndef _TextFile_h_

