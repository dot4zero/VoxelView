// определение параметров сборки библиотеки service
// этот файл должен подключатся первым
#ifndef DEFINE_SERVICE_DLL_INC
#define DEFINE_SERVICE_DLL_INC

// для UNIX или для статической сборки под WINDOWS
#define PARAMETR_IMPORT_DLL
// для динамической сборки под WINDOWS
//#define PARAMETR_IMPORT_DLL __declspec(dllimport)

#ifndef PRIZNAK_SERVICE_DLL
#define PRIZNAK_SERVICE_DLL PARAMETR_IMPORT_DLL
#endif
#ifndef PRIZNAK_EXTERNAL_DLL
#define PRIZNAK_EXTERNAL_DLL PARAMETR_IMPORT_DLL
#endif

#endif
