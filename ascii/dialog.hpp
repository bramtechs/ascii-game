#pragma once

#include <curses.h>
#include <unordered_map>
#include <functional>
#include <memory>

#include "gui.hpp"

constexpr int NO_SELECTION = -1;
constexpr int GOODBYE = -2;

struct DialogNode;
typedef std::unordered_map<std::string, std::shared_ptr<DialogNode>> DialogNodeMap;

struct DialogNode {
    std::string text;
    DialogNodeMap nodes;

    DialogNode(DialogNode* node);
    DialogNode(std::string text);
    DialogNode();

    DialogNode& append(std::string key, DialogNode node);
};

class Dialog {
   public:
    std::string speaker;

    Dialog(std::string speaker, DialogNode tree);
    Dialog(std::string speaker, std::function<DialogNode()> tree);

    void draw();

   private:
    std::shared_ptr<DialogNode> tree;
    std::shared_ptr<DialogNode> currentNode;

    // gui
    WINDOW* window;
    int updateAndDrawChoices(int y, int x, DialogNodeMap choices);
    void drawTranscript(int y, int x);
};
