#include <curses.h>
#include <unordered_map>
#include <functional>
#include <memory>

#include "gui.hpp"

constexpr int NO_SELECTION = -1;

struct DialogNode {
    std::string text;
    std::unordered_map<std::string, std::shared_ptr<DialogNode>> nodes;

    DialogNode(DialogNode* node);
    DialogNode(std::string text);

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

    // gui
    WINDOW* window;
    int drawChoices(int y, int x, std::vector<std::string> choices);
};
