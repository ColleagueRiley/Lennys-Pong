const char* font_ttfs[] = {    
    "DejaVuSans.ttf",
    "LiberationSans-Regular.ttf",
    "DroidSans.ttf",
    "Roboto-Regular.ttf",
    "Ubuntu-Regular.ttf",
    "NotoSans-Regular.ttf",
    "NotoSansNerdFontPropo-Regular.ttf",

    "/usr/share/fonts/TTF/DejaVuSans.ttf",
    "/usr/share/fonts/TTF/LiberationSans-Regular.ttf",
    "/usr/share/fonts/TTF/DroidSans.ttf",
    "/usr/share/fonts/TTF/Roboto-Regular.ttf",
    "/usr/share/fonts/TTF/Ubuntu-Regular.ttf",
    "/usr/share/fonts/TTF/NotoSans-Regular.ttf",
    "/usr/share/fonts/TTF/NotoSansNerdFontPropo-Regular.ttf",

    "~/.fonts/DejaVuSans.ttf",
    "~/.fonts/LiberationSans-Regular.ttf",
    "~/.fonts/DroidSans.ttf",
    "~/.fonts/Roboto-Regular.ttf",
    "~/.fonts/Ubuntu-Regular.ttf",
    "~/.fonts/NotoSans-Regular.ttf",
    "~/.fonts/NotoSansNerdFontPropo-Regular.ttf"
};

#if defined(__unix__) && !defined(_WIN32)
#include <sys/stat.h>
#endif

inline bool si_path_exists(char* path);
bool si_path_exists(char* path) {
	#if defined(_WIN32)
		DWORD file_attrib = GetFileAttributes(path);
		return file_attrib != INVALID_FILE_ATTRIBUTES;
	#else

		struct stat tmp;
		return (stat(path, &tmp) == 0);

	#endif
}