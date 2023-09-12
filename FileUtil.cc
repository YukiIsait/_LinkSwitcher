#include "FileUtil.h"
#include <Windows.h>

std::optional<std::wstring> FileUtil::ReadAllText(const std::wstring& fileName) noexcept {
    HANDLE hFile = ::CreateFileW(fileName.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        return std::nullopt;
    }
    DWORD readSize = 0;
    DWORD magic = 0;
    std::optional<std::wstring> result = std::nullopt;
    if (::ReadFile(hFile, &magic, 2, &readSize, nullptr) && readSize == 2 && magic == 0xFEFF) {
        DWORD fileSize = ::GetFileSize(hFile, nullptr);
        if (fileSize != INVALID_FILE_SIZE) {
            fileSize -= 2;
            std::wstring buffer(fileSize / sizeof(wchar_t), 0);
            if (::ReadFile(hFile, buffer.data(), fileSize, &readSize, nullptr) && fileSize == readSize) {
                result = std::move(buffer);
            }
        }
    }
    ::CloseHandle(hFile);
    return result;
}
