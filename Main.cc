#include "LinkSwitcher.h"
#include "PathUtil.h"
#include <cstdio>

int wmain(int argc, wchar_t** argv) {
     if (argc != 2) {
         wprintf_s(L"Usage: %s <key>\n", argv[0]);
         return 1;
     }
    std::optional<std::wstring> programPath = PathUtil::GetProgramFileName();
    if (!programPath) {
        return 1;
    }
    std::wstring mappingFilePath(std::move(programPath->replace(PathUtil::FindExtension(*programPath).value_or(programPath->size()), 4, L".txt")));
    LinkSwitcher linkSwitcher(PathUtil::GetParent(mappingFilePath), L"Current", mappingFilePath);
    if (!linkSwitcher.SwitchTo(argv[1])) {
        wprintf_s(L"Failed to switch to %s\n", argv[1]);
        return 1;
    }
    return 0;
}
