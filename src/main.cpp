#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

// CreatorLab's first in-editor entry point.
// The actual generators will be implemented in separate modules.
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
        menu->updateLayout();

        return true;
    }

    void onCreatorLab(CCObject*) {
        FLAlertLayer::create(
            "CreatorLab",
            "Welcome to CreatorLab!\n\n"
            "Your independent creator toolkit for Geometry Dash.\n\n"
            "Planned generators:\n"
            "• Auto Decoration\n"
            "• Backgrounds and Structures\n"
            "• Effects, Objects, and Transitions\n"
            "• Colors, Patterns, Text, and Atmosphere\n\n"
            "The editor entry point is ready. Generator tools are being added next.",
            "Let's create!"
        )->show();
    }
};
