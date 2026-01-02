#pragma once
#include <string>
#include <vector>
#include <map>

namespace subverse {

struct StoryNode {
    std::string id;
    std::string type; // "dialogue", "choice", "scene"
    std::string speaker;
    std::string text;
    std::string background;
    std::string character;
    std::vector<std::string> choices;
    std::vector<std::string> targets;
    std::string next;
};

class StoryManager {
public:
    void loadScript(const std::string& scriptContent);
    void start();
    void advance();
    void selectChoice(int index);
    
    const StoryNode* getCurrentNode() const;
    bool isFinished() const { return finished_; }
    
private:
    void parseScript(const std::string& content);
    void gotoNode(const std::string& nodeId);
    
    std::map<std::string, StoryNode> nodes_;
    std::string currentNodeId_;
    bool finished_ = false;
};

} // namespace subverse
