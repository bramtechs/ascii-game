#include <memory>
#include <string>
#include <vector>

#include "dialog.hpp"

using namespace std;

Dialog::Dialog(string speaker, DialogNode tree)
{
    this->speaker = speaker;
    this->tree = std::make_shared<DialogNode>(new DialogNode(tree));
    this->currentNode = this->tree;
}

Dialog::Dialog(string speaker, function<DialogNode()> tree) : Dialog(speaker, tree())
{
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

DialogNode::DialogNode() : DialogNode("...")
{
}

DialogNode& DialogNode::append(string key, DialogNode node)
{
    nodes[key] = std::make_shared<DialogNode>(new DialogNode(node));
    return *this;
}

void Dialog::draw()
{
    const int marginLeft = 2;

    window = drawFullscreenWindow();
    int maxx = getmaxx(window);
    int maxy = getmaxy(window);

    string title = "Dialog with " + speaker;
    mvwprintw(window, 2, marginLeft, "%s", title.c_str());

    DialogNode* currentNode = this->currentNode.get();
    if (currentNode != nullptr) {
        // draw title
        mvwprintw(window, 4, marginLeft, "%s", currentNode->text.c_str());
        drawTranscript(6, marginLeft);
        drawChoices(maxy - 2, marginLeft, currentNode->nodes);
    }

    wrefresh(window);
}

int Dialog::drawChoices(int y, int x, DialogNodeMap choices)
{
    static int selected = 0;

    int i = 0;
    int yy = y - choices.size() - 1;
    for (auto& [key, choice] : choices) {
        const char* prefix = selected == i ? "> %s" : "  %s";
        mvwprintw(window, yy + i++, x, prefix, key.c_str());
    }
    const char* prefix = selected == choices.size() ? "> %s" : "  %s";
    mvwprintw(window, yy + i++, x, prefix, "Goodbye");

    return NO_SELECTION;
}

void Dialog::drawTranscript(int y, int x)
{
    // TODO
}
