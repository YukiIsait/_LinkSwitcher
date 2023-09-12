#pragma once
#include "JunctionPoint.h"
#include <optional>
#include <string>
#include <map>

class LinkSwitcher {
private:
    std::wstring basePath;
    std::optional<JunctionPoint> link;
    std::optional<std::wstring> mappingFileContent;
    std::optional<JunctionPoint> InitLink(const std::wstring& linkName) noexcept;
    std::optional<std::wstring> InitMappingFileContent(const std::wstring& mappingFileName) noexcept;
    std::optional<std::wstring> GetLinkByKey(const std::wstring& key) const noexcept;

public:
    explicit LinkSwitcher(const std::wstring& basePath, const std::wstring& linkName, const std::wstring& mappingFileName) noexcept;
    explicit LinkSwitcher(const std::wstring&& basePath, const std::wstring& linkName, const std::wstring& mappingFileName) noexcept;
    bool SwitchTo(const std::wstring& key) const noexcept;
};
