#include "Global.hpp"

#include "Exception.h"
#include "Application.hpp"

int main(int argc, char* args[]) {
	try {
		Core::Application* app = new Core::Application("path.sc", "config.sc");
		app->go();
	} catch (Core::Exception& e) {
		Core::Exception::die(e.getDescription(), std::string("error.log"));
		return 1;
	}
	return 0;
}

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#if defined __WIN32__ || _WIN32 && defined _MSC_VER
//#include <Windows.h>
//#include <locale>
//#define WIN32_LEAN_AND_MEAN
//INT WINAPI WinMain
//(
//		_In_ HINSTANCE hInstance,
//		_In_opt_ HINSTANCE hPrevInstance,
//		_In_ LPSTR lpCmdLine,
//		_In_ int nShowCmd
//) {
//#else
//int main(int argc, char* args[]) {
//#endif
//	return _main(argc, args);
//}
//
//#ifdef __cplusplus
//}
//#endif
