#include "PathList.hpp"

#include "Exception.hpp"

namespace Core
{

//static PathList singletonPathList;
static PathList* singletonPathList= new PathList();

PathList::PathList(void)
{
	const char *env = getenv("PATH");

	//search local paths first, in-case someone has the SDK installed while hacking another copy
	pathList.push_back("./");  // present directory
	pathList.push_back("../"); // back one
	pathList.push_back("../../"); // back two
	if (env)
	{
		pathList.push_back(std::string(env) + "/"); // Path lacks a terminating slash
	}
}

PathList::~PathList(void)
{
	clearPaths();
}

void PathList::addPath(const std::string &path)
{
	pathList.push_back(path);
}

void PathList::clearPaths()
{
	if (!pathList.empty())
	{
		pathList.clear();
	}
}

bool PathList::getPath(const std::string &file, std::string &path)
{
	bool sucess = false;
	std::string pathString;
	FILE *fp;

	for (auto it = pathList.begin(); it != pathList.end(); ++it)
	{
		pathString = *it + file;
		fp = fopen(pathString.c_str(), "rb");
		if (fp)
		{
			fclose(fp);
			path = pathString;
			sucess = true;
			break;
//			it = pathList.end();
//			pathString.clear();
//			return;
		}
	}
	pathString.clear();
//	throw Exception("File with name " + file + " doesn't exist;");
	return sucess;
}

//std::string PathList::getPath(const std::string &file)
//{
//	std::string pathString;
//
//	for (auto it = pathList.begin(); it != pathList.end(); it++)
//	{
//		pathString = *it + file;
//		FILE *fp = fopen(pathString.c_str(), "rb");
//		if (fp)
//		{
//			fclose(fp);
//			path = *it;
//			//return true;
//			return path;
//		}
//	}
//	throw Exception("File with name" + file + "doesn't exist");
//}

PathList* PathList::getSingletonPtr(void)
{
	return singletonPathList;
}

//PathList PathList::getSingleton()
//{
//	return singletonPathList;
//}

void PathList::print(void)
{
	for (auto it = pathList.begin(); it != pathList.end(); it++)
	{
		std::cout << *(it) << std::endl;
	}
}

} /* namespace Core */
