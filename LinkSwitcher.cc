#include "LinkSwitcher.h"
#include "JunctionPoint.h"
#include "FileUtil.h"
#include "PathUtil.h"
#include "StringUtil.hh"

std::optional<JunctionPoint> LinkSwitcher::InitLink(const std::wstring& linkName) noexcept {
    std::optional<std::wstring> linkFullPath = PathUtil::Combine(basePath, linkName);
    if (!linkFullPath) {
        return std::nullopt;
    }
    JunctionPoint link(std::move(*linkFullPath));
    return link;
}

std::optional<std::wstring> LinkSwitcher::InitMappingFileContent(const std::wstring& mappingFileName) noexcept {
    std::optional<std::wstring> mappingFileFullPath = PathUtil::Combine(basePath, mappingFileName);
    if (!mappingFileFullPath) {
        return std::nullopt;
    }
    return FileUtil::ReadAllText(*mappingFileFullPath);
}

std::optional<std::wstring> LinkSwitcher::GetLinkByKey(const std::wstring& k) const noexcept {
    if (!mappingFileContent) {
        return std::nullopt;
    }
    for (size_t index = 0;; index++) {
        std::optional<std::wstring> line = StringUtil::SplitAndGet(*mappingFileContent, L"\r\n", index);
        if (!line) {
            break;
        }
        StringUtil::Trim(*line);
        if (line->empty() || (*line)[0] == L':') {
            continue;
        }
        std::optional<std::wstring> key = StringUtil::SplitAndGet(*line, L':', 0);
        std::optional<std::wstring> value = StringUtil::SplitAndGet(*line, L':', 1);
        if (!key || !value) {
            continue;
        }
        StringUtil::Trim(*key);
        StringUtil::Trim(*value);
        if (key->empty() || value->empty()) {
            continue;
        }
        if (*key == k) {
            return value;
        }
    }
    return std::nullopt;
}

LinkSwitcher::LinkSwitcher(const std::wstring& basePath, const std::wstring& linkName, const std::wstring& mappingFileName) noexcept
    : basePath(basePath), link(InitLink(linkName)), mappingFileContent(InitMappingFileContent(mappingFileName)) {}

LinkSwitcher::LinkSwitcher(const std::wstring&& basePath, const std::wstring& linkName, const std::wstring& mappingFileName) noexcept
    : basePath(std::move(basePath)), link(InitLink(linkName)), mappingFileContent(InitMappingFileContent(mappingFileName)) {}

bool LinkSwitcher::SwitchTo(const std::wstring& key) const noexcept {
    if (!mappingFileContent || !link) {
        return false;
    }
    std::optional<std::wstring> target = GetLinkByKey(key);
    if (!target) {
        return false;
    }
    std::optional<std::wstring> targetFullPath = PathUtil::Combine(basePath, *target);
    if (!targetFullPath) {
        return false;
    }
    if (!link->RemountFor(*targetFullPath)) {
        return link->CreateFor(*targetFullPath);
    }
    return true;
}
