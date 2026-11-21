#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/utils/file.hpp>

#include <algorithm>\n#include <chrono>
#include <iomanip>
#include <sstream>

using namespace geode::prelude;

// CreatorLab editor entry points and first Stamp Capture prototype.
class $modify(CreatorLabEditorUI, EditorUI) {
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
