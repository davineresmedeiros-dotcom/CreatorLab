#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/utils/file.hpp>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <functional>
#include <fstream>
#include <regex>
#include <sstream>
#include <vector>

using namespace geode::prelude;

// CreatorLab editor entry points and first Stamp Capture prototype.
class $modify(CreatorLabEditorUI, EditorUI) {
    std::string m_selectedStampFile;

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) {
            return false;
        }

        auto menu = this->getChildByID("playback-menu");
        if (!menu) {
            log::warn("CreatorLab: editor playback menu was not found.");
            return true;
        }

        auto sprite = ButtonSprite::create("CreatorLab", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        if (!sprite) {
            log::warn("CreatorLab: failed to create editor button sprite.");
            return true;
        }

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(CreatorLabEditorUI::onCreatorLab)
        );
        button->setID("creatorlab-open-button");
        menu->addChild(button);
        if (m_uiItems) {
            m_uiItems->addObject(button);
        }

        auto captureSprite = ButtonSprite::create("Stamp", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        if (captureSprite) {
            auto captureButton = CCMenuItemSpriteExtra::create(
                captureSprite,
                this,
                menu_selector(CreatorLabEditorUI::onCaptureStamp)
            );
            captureButton->setID("creatorlab-capture-stamp-button");
            menu->addChild(captureButton);
            if (m_uiItems) {
                m_uiItems->addObject(captureButton);
            }
        }

        auto stampsSprite = ButtonSprite::create("Stamps", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        if (stampsSprite) {
            auto stampsButton = CCMenuItemSpriteExtra::create(
                stampsSprite,
                this,
                menu_selector(CreatorLabEditorUI::onBrowseStamps)
            );
            stampsButton->setID("creatorlab-browse-stamps-button");
            menu->addChild(stampsButton);
            if (m_uiItems) {
                m_uiItems->addObject(stampsButton);
            }
        }

        auto previewSprite = ButtonSprite::create("Preview", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        if (previewSprite) {
            auto previewButton = CCMenuItemSpriteExtra::create(
                previewSprite,
                this,
                menu_selector(CreatorLabEditorUI::onPreviewStamp)
            );
            previewButton->setID("creatorlab-preview-stamp-button");
            menu->addChild(previewButton);
            if (m_uiItems) {
                m_uiItems->addObject(previewButton);
            }
        }

        auto applySprite = ButtonSprite::create("Apply", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        if (applySprite) {
            auto applyButton = CCMenuItemSpriteExtra::create(
                applySprite,
                this,
                menu_selector(CreatorLabEditorUI::onApplyStamp)
            );
            applyButton->setID("creatorlab-apply-stamp-button");
            menu->addChild(applyButton);
            if (m_uiItems) {
                m_uiItems->addObject(applyButton);
            }
        }

        menu->updateLayout();
        return true;
    }

    void onCreatorLab(CCObject*) {
        FLAlertLayer::create(
            "CreatorLab",
            "CreatorLab creator toolkit\n\n"
            "Stamp Capture prototype is available from the Stamp button.\n"
            "Neon Circuit is the first planned stamp style.",
            "Let's create!"
        )->show();
    }

    void onBrowseStamps(CCObject*) {
        auto stampDir = Mod::get()->getSaveDir() / "stamps";
        std::error_code ec;
        std::filesystem::directory_iterator it(
            std::filesystem::path(stampDir.string()), ec
        );
        if (ec) {
            FLAlertLayer::create(
                "Stamp Browser",
                "The stamps folder does not exist yet, or it could not be read.\n\n"
                "Capture a stamp first using the Stamp button.",
                "OK"
            )->show();
            return;
        }

        std::vector<std::string> files;
        const std::filesystem::directory_iterator end;
        while (it != end && !ec) {
            const auto& entry = *it;
            if (entry.is_regular_file(ec) && !ec && entry.path().extension() == ".json") {
                files.push_back(entry.path().filename().string());
            }
            it.increment(ec);
        }
        if (ec) {
            FLAlertLayer::create("Stamp Browser", "Could not read the stamps folder.", "OK")->show();
            log::warn("CreatorLab: error while listing stamps: {}", ec.message());
            return;
        }

        std::sort(files.begin(), files.end(), std::greater<>());
        if (files.empty()) {
            FLAlertLayer::create(
                "Stamp Browser",
                "No saved stamps yet.\n\nSelect decoration objects and press Stamp to capture your first one.",
                "OK"
            )->show();
            return;
        }

        // Each tap selects the next saved stamp for the Apply button.
        auto current = std::find(files.begin(), files.end(), m_selectedStampFile);
        if (current == files.end()) {
            m_selectedStampFile = files.front();
        } else {
            ++current;
            if (current == files.end()) current = files.begin();
            m_selectedStampFile = *current;
        }

        std::ostringstream message;
        message << "Selected stamp:\n" << m_selectedStampFile
                << "\n\nStamp files: " << files.size()
                << "\nTap Stamps again to select another file.\n"
                << "Press Apply to place the selected stamp in your area.";
        FLAlertLayer::create("Stamp Browser", message.str(), "Close")->show();
    }

    void onPreviewStamp(CCObject*) {
        auto stampDir = Mod::get()->getSaveDir() / "stamps";
        std::error_code ec;
        std::filesystem::directory_iterator it(std::filesystem::path(stampDir.string()), ec);
        if (ec) {
            FLAlertLayer::create("Stamp Preview", "No saved stamps found. Capture a stamp first.", "OK")->show();
            return;
        }

        std::vector<std::filesystem::path> files;
        const std::filesystem::directory_iterator end;
        while (it != end && !ec) {
            const auto& entry = *it;
            if (entry.is_regular_file(ec) && !ec && entry.path().extension() == ".json") {
                files.push_back(entry.path());
            }
            it.increment(ec);
        }
        if (ec || files.empty()) {
            FLAlertLayer::create("Stamp Preview", "Could not find a saved stamp file.", "OK")->show();
            return;
        }
        std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
            return a.filename().string() > b.filename().string();
        });

        auto chosenStamp = files.front();
        if (!m_selectedStampFile.empty()) {
            auto chosen = std::find_if(files.begin(), files.end(), [this](const auto& path) {
                return path.filename().string() == m_selectedStampFile;
            });
            if (chosen != files.end()) chosenStamp = *chosen;
        }

        std::ifstream input(chosenStamp.string());
        if (!input) {
            FLAlertLayer::create("Stamp Preview", "Could not open the selected stamp.", "OK")->show();
            return;
        }
        std::string data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

        std::regex namePattern("\\\"name\\\"\\\\s*:\\\\s*\\\"([^\\\"]*)\\\"");
        std::smatch nameMatch;
        std::string stampName = chosenStamp.filename().string();
        if (std::regex_search(data, nameMatch, namePattern)) stampName = nameMatch[1].str();

        std::regex objectPattern("\\\"object_id\\\"\\\\s*:\\\\s*(-?\\\\d+)");
        const auto objectCount = static_cast<size_t>(
            std::distance(std::sregex_iterator(data.begin(), data.end(), objectPattern), std::sregex_iterator())
        );

        auto readBound = [&data](const std::string& key, float& value) -> bool {
            std::regex pattern(std::string("\\\"") + key + "\\\"\\\\s*:\\\\s*(-?[0-9]+(?:\\\\.[0-9]+)?)");
            std::smatch match;
            if (!std::regex_search(data, match, pattern)) return false;
            try {
                value = std::stof(match[1].str());
                return std::isfinite(value);
            } catch (...) {
                return false;
            }
        };

        float minX, minY, maxX, maxY;
        std::ostringstream message;
        message << "Stamp: " << stampName << "\n"
                << "File: " << chosenStamp.filename().string() << "\n"
                << "Objects: " << objectCount << "\n\n";
        if (readBound("min_x", minX) && readBound("min_y", minY) &&
            readBound("max_x", maxX) && readBound("max_y", maxY)) {
            message << "Position bounds: " << (maxX - minX) << " x " << (maxY - minY) << "\n\n";
        } else {
            message << "Bounds: unavailable in this stamp file.\n\n";
        }
        message << "This is an information preview only. It does not place or change any objects.\n"
                << "A visual ghost preview will be added after the placement API is verified.";
        FLAlertLayer::create("Stamp Preview", message.str(), "Close")->show();
    }

    void onApplyStamp(CCObject*) {
        auto selected = this->getSelectedObjects();
        if (!selected || selected->count() == 0) {
            FLAlertLayer::create(
                "Apply Stamp",
                "Select objects to define the target area, then press Apply.\n\n"
                "The selected objects are only used as area markers and will not be changed.",
                "OK"
            )->show();
            return;
        }

        bool hasArea = false;
        float minX = 0.f, minY = 0.f, maxX = 0.f, maxY = 0.f;
        for (unsigned int i = 0; i < selected->count(); ++i) {
            auto object = typeinfo_cast<GameObject*>(selected->objectAtIndex(i));
            if (!object) continue;
            const float x = object->getPositionX();
            const float y = object->getPositionY();
            if (!hasArea) {
                minX = maxX = x;
                minY = maxY = y;
                hasArea = true;
            } else {
                minX = std::min(minX, x);
                minY = std::min(minY, y);
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);
            }
        }
        if (!hasArea) {
            FLAlertLayer::create("Apply Stamp", "The selection has no valid objects to define an area.", "OK")->show();
            return;
        }

        auto stampDir = Mod::get()->getSaveDir() / "stamps";
        std::error_code ec;
        std::filesystem::directory_iterator it(std::filesystem::path(stampDir.string()), ec);
        if (ec) {
            FLAlertLayer::create("Apply Stamp", "No saved stamps folder was found. Capture a stamp first.", "OK")->show();
            return;
        }

        std::vector<std::filesystem::path> stampFiles;
        const std::filesystem::directory_iterator end;
        while (it != end && !ec) {
            const auto& entry = *it;
            if (entry.is_regular_file(ec) && !ec && entry.path().extension() == ".json") {
                stampFiles.push_back(entry.path());
            }
            it.increment(ec);
        }
        if (ec || stampFiles.empty()) {
            FLAlertLayer::create("Apply Stamp", "Could not find a saved stamp file.", "OK")->show();
            return;
        }
        std::sort(stampFiles.begin(), stampFiles.end(), [](const auto& a, const auto& b) {
            return a.filename().string() > b.filename().string();
        });

        auto chosenStamp = stampFiles.front();
        if (!m_selectedStampFile.empty()) {
            auto chosen = std::find_if(stampFiles.begin(), stampFiles.end(), [this](const auto& path) {
                return path.filename().string() == m_selectedStampFile;
            });
            if (chosen != stampFiles.end()) chosenStamp = *chosen;
        }

        std::ifstream input(chosenStamp.string());
        if (!input) {
            FLAlertLayer::create("Apply Stamp", "Could not open the selected stamp file.", "OK")->show();
            return;
        }
        std::string stampData((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

        auto readNumber = [&stampData](const std::string& key, float& value) -> bool {
            std::regex pattern(std::string("\"") + key + "\"\\s*:\\s*(-?[0-9]+(?:\\.[0-9]+)?(?:[eE][+-]?[0-9]+)?)");
            std::smatch match;
            if (!std::regex_search(stampData, match, pattern)) return false;
            try {
                value = std::stof(match[1].str());
                return std::isfinite(value);
            } catch (...) {
                return false;
            }
        };

        float stampMinX, stampMinY, stampMaxX, stampMaxY;
        if (!readNumber("min_x", stampMinX) || !readNumber("min_y", stampMinY) ||
            !readNumber("max_x", stampMaxX) || !readNumber("max_y", stampMaxY)) {
            FLAlertLayer::create("Apply Stamp", "This stamp has invalid or missing bounds.", "OK")->show();
            return;
        }

        const float areaWidth = maxX - minX;
        const float areaHeight = maxY - minY;
        const float stampWidth = stampMaxX - stampMinX;
        const float stampHeight = stampMaxY - stampMinY;
        if (stampWidth > areaWidth || stampHeight > areaHeight) {
            FLAlertLayer::create(
                "Apply Stamp",
                "The stamp does not fit inside the selected area.\n\n"
                "Nothing was placed. Select a larger area.",
                "OK"
            )->show();
            return;
        }

        const float targetX = (minX + maxX) / 2.f;
        const float targetY = (minY + maxY) / 2.f;
        const std::regex objectPattern(
            R"(\{\s*"object_id"\s*:\s*(-?\d+)\s*,\s*"x"\s*:\s*(-?(?:[0-9]+\.?[0-9]*|\.[0-9]+))\s*,\s*"y"\s*:\s*(-?(?:[0-9]+\.?[0-9]*|\.[0-9]+))\s*,\s*"rotation"\s*:\s*(-?(?:[0-9]+\.?[0-9]*|\.[0-9]+))\s*,\s*"scale_x"\s*:\s*(-?(?:[0-9]+\.?[0-9]*|\.[0-9]+))\s*,\s*"scale_y"\s*:\s*(-?(?:[0-9]+\.?[0-9]*|\.[0-9]+))\s*\})"
        );
        std::string objectString;
        unsigned int objectCount = 0;
        for (std::sregex_iterator match(stampData.begin(), stampData.end(), objectPattern), endMatch;
             match != endMatch; ++match) {
            const auto& m = *match;
            try {
                const int objectID = std::stoi(m[1].str());
                const float x = targetX + std::stof(m[2].str());
                const float y = targetY + std::stof(m[3].str());
                const float rotation = std::stof(m[4].str());
                const float scaleX = std::stof(m[5].str());
                const float scaleY = std::stof(m[6].str());
                if (objectID <= 0 || !std::isfinite(x) || !std::isfinite(y) ||
                    !std::isfinite(rotation) || !std::isfinite(scaleX) || !std::isfinite(scaleY)) {
                    continue;
                }
                // Only serialize ID and transform fields. No groups, colors, triggers, or editor metadata.
                objectString += fmt::format(
                    "1,{},2,{:.3f},3,{:.3f},6,{:.3f},32,{:.3f},42,{:.3f};",
                    objectID, x, y, rotation, scaleX, scaleY
                );
                ++objectCount;
            } catch (...) {
                continue;
            }
        }

        if (objectCount == 0) {
            FLAlertLayer::create("Apply Stamp", "No valid object records were found in this stamp.", "OK")->show();
            return;
        }

        // The game creates new objects from this string; the selected area markers are not edited.
        auto created = m_editorLayer->createObjectsFromString(objectString, true, true);
        if (!created || created->count() == 0) {
            FLAlertLayer::create("Apply Stamp", "The game could not create the stamp objects.", "OK")->show();
            return;
        }

        FLAlertLayer::create(
            "Stamp Applied!",
            fmt::format(
                "Placed {} new objects inside the selected area's center.\n\n"
                "The selected objects were left untouched; no group or color data was applied.",
                created->count()
            ),
            "Great!"
        )->show();
    }

    void onCaptureStamp(CCObject*) {
        auto selected = this->getSelectedObjects();
        if (!selected || selected->count() == 0) {
            FLAlertLayer::create(
                "Stamp Capture",
                "Select one or more decoration objects in the editor, then press Stamp.\n\n"
                "The capture prototype saves object IDs and positions relative to the first selected object.",
                "OK"
            )->show();
            return;
        }

        bool foundObject = false;
        float minX = 0.f;
        float minY = 0.f;
        float maxX = 0.f;
        float maxY = 0.f;

        for (unsigned int i = 0; i < selected->count(); ++i) {
            auto object = typeinfo_cast<GameObject*>(selected->objectAtIndex(i));
            if (!object) {
                continue;
            }
            const float x = object->getPositionX();
            const float y = object->getPositionY();
            if (!foundObject) {
                minX = maxX = x;
                minY = maxY = y;
                foundObject = true;
            } else {
                minX = std::min(minX, x);
                minY = std::min(minY, y);
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);
            }
        }

        if (!foundObject) {
            FLAlertLayer::create("Stamp Capture", "The selection did not contain a valid object.", "OK")->show();
            return;
        }

        // Center the stamp anchor on the selected objects' position bounds.
        const float anchorX = (minX + maxX) / 2.f;
        const float anchorY = (minY + maxY) / 2.f;

        std::ostringstream json;
        json << std::fixed << std::setprecision(3);
        json << "{\n"
             << "  \"format\": \"creatorlab-stamp\",\n"
             << "  \"format_version\": 1,\n"
             << "  \"id\": \"captured-stamp\",\n"
             << "  \"name\": \"Captured Stamp\",\n"
             << "  \"style\": \"custom\",\n"
             << "  \"anchor\": { \"x\": " << anchorX << ", \"y\": " << anchorY << " },\n"
             << "  \"bounds\": { \"min_x\": " << (minX - anchorX)
             << ", \"min_y\": " << (minY - anchorY)
             << ", \"max_x\": " << (maxX - anchorX)
             << ", \"max_y\": " << (maxY - anchorY) << " },\n"
             << "  \"objects\": [\n";

        bool firstEntry = true;
        unsigned int savedCount = 0;
        for (unsigned int i = 0; i < selected->count(); ++i) {
            auto object = typeinfo_cast<GameObject*>(selected->objectAtIndex(i));
            if (!object) {
                continue;
            }
            if (!firstEntry) {
                json << ",\n";
            }
            firstEntry = false;
            ++savedCount;

            json << "    { \"object_id\": " << object->m_objectID
                 << ", \"x\": " << (object->getPositionX() - anchorX)
                 << ", \"y\": " << (object->getPositionY() - anchorY)
                 << ", \"rotation\": " << object->getRotation()
                 << ", \"scale_x\": " << object->getScaleX()
                 << ", \"scale_y\": " << object->getScaleY() << " }";
        }

        if (savedCount == 0) {
            FLAlertLayer::create("Stamp Capture", "No valid editor objects were found in the selection.", "OK")->show();
            return;
        }

        json << "\n  ],\n"
             << "  \"capture_note\": \"Prototype: object IDs, relative positions, rotation, and scale only.\"\n"
             << "}\n";

        auto stampDir = Mod::get()->getSaveDir() / "stamps";
        auto dirResult = utils::file::createDirectoryAll(stampDir);
        if (!dirResult) {
            FLAlertLayer::create("Stamp Capture", "Could not create the stamps folder.", "OK")->show();
            log::error("CreatorLab: failed to create stamp directory: {}", dirResult.unwrapErr());
            return;
        }

        auto now = std::chrono::system_clock::now().time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        auto filePath = stampDir / fmt::format("stamp-{}.json", millis);
        auto writeResult = utils::file::writeStringSafe(filePath, json.str());
        if (!writeResult) {
            FLAlertLayer::create("Stamp Capture", "Could not save the stamp file.", "OK")->show();
            log::error("CreatorLab: failed to save stamp: {}", writeResult.unwrapErr());
            return;
        }

        FLAlertLayer::create(
            "Stamp Captured!",
            fmt::format(
                "Saved {} selected objects as a stamp file.\n\n"
                "Saved properties: object ID, relative position, rotation, and scale.\n"
                "Colors, flip flags, groups, and connection ports are not captured yet.",
                savedCount
            ),
            "Great!"
        )->show();
    }
};
