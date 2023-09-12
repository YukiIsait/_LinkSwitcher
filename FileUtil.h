#pragma once
#include <optional>
#include <string>

class FileUtil {
public:
    static std::optional<std::wstring> ReadAllText(const std::wstring& fileName) noexcept;
};
