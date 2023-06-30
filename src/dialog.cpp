#include <memory>
#include <string>
#include <vector>

#include "dialog.hpp"

using namespace std;

Dialog::Dialog(string speaker, DialogNode tree)
{
    this->speaker = speaker;
    this->tree = std::make_shared<DialogNode>(new DialogNode(tree));
}

Dialog::Dialog(string speaker, function<DialogNode()> tree)
{
    this->speaker = speaker;
    this->tree = std::make_shared<DialogNode>(tree());
}

DialogNode::DialogNode(DialogNode* node)
{
    this->text = node->text;
    this->nodes = node->nodes;
}

DialogNode::DialogNode(string text)
{
    this->text = text;
    this->nodes = {};
}

DialogNode& DialogNode::append(string key, DialogNode node)
{
    nodes[key] = std::make_shared<DialogNode>(new DialogNode(node));
    return *this;
}

void Dialog::draw()
{
    window = drawFullscreenWindow();
    int maxx = getmaxx(window);
    int maxy = getmaxy(window);

    string title = "Dialog with " + speaker;
    mvwprintw(window, 2, maxx / 2 - 3, "%s", title.c_str());

    drawChoices(maxy - 2, 5, { "Yes", "No" });

    wrefresh(window);
}

int Dialog::drawChoices(int y, int x, vector<string> choices)
{
    static int selected = 0;

    int i = 0;
    int yy = y - choices.size();
    for (auto& choice : choices) {
        const char* prefix = selected == i ? "> %s" : "  %s";
        mvwprintw(window, yy + i++, x, prefix, choice.c_str());
    }

    return NO_SELECTION;
}
