#include "story_manager.h"
#include "logger.h"
#include <sstream>

namespace subverse {

void StoryManager::loadScript(const std::string& scriptContent) {
    parseScript(scriptContent);
    LOGI("Loaded %zu story nodes", nodes_.size());
}

void StoryManager::parseScript(const std::string& content) {
    // Simple parser for .vns format
    std::istringstream iss(content);
    std::string line;
    StoryNode* current = nullptr;
    
    while (std::getline(iss, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        if (line[0] == '@') {
            // Command
            size_t space = line.find(' ');
            std::string cmd = line.substr(1, space - 1);
            std::string arg = (space != std::string::npos) ? line.substr(space + 1) : "";
            
            if (cmd == "node") {
                current = &nodes_[arg];
                current->id = arg;
            } else if (current) {
                if (cmd == "scene") current->type = "scene";
                else if (cmd == "bg") current->background = arg;
                else if (cmd == "char") current->character = arg;
                else if (cmd == "choice") current->type = "choice";
                else if (cmd == "next") current->next = arg;
            }
        } else if (line[0] == '>') {
            // Choice option
            if (current) {
                size_t arrow = line.find("->");
                if (arrow != std::string::npos) {
                    std::string choiceText = line.substr(1, arrow - 1);
                    std::string target = line.substr(arrow + 2);
                    // trim
                    while (!choiceText.empty() && choiceText.back() == ' ') choiceText.pop_back();
                    while (!target.empty() && target.front() == ' ') target.erase(0, 1);
                    current->choices.push_back(choiceText);
                    current->targets.push_back(target);
                }
            }
        } else {
            // Dialogue line
            if (current) {
                size_t colon = line.find(':');
                if (colon != std::string::npos) {
                    current->type = "dialogue";
                    current->speaker = line.substr(0, colon);
                    current->text = line.substr(colon + 2); // skip ": "
                }
            }
        }
    }
}

void StoryManager::start() {
    if (!nodes_.empty()) {
        gotoNode(nodes_.begin()->first);
    }
}

void StoryManager::gotoNode(const std::string& nodeId) {
    if (nodes_.find(nodeId) == nodes_.end()) {
        LOGE("Node not found: %s", nodeId.c_str());
        finished_ = true;
        return;
    }
    currentNodeId_ = nodeId;
    LOGI("Entered node: %s", nodeId.c_str());
}

void StoryManager::advance() {
    auto* node = getCurrentNode();
    if (!node) {
        finished_ = true;
        return;
    }
    
    if (!node->next.empty()) {
        gotoNode(node->next);
    } else {
        finished_ = true;
    }
}

void StoryManager::selectChoice(int index) {
    auto* node = getCurrentNode();
    if (!node || index < 0 || index >= (int)node->targets.size()) return;
    
    gotoNode(node->targets[index]);
}

const StoryNode* StoryManager::getCurrentNode() const {
    auto it = nodes_.find(currentNodeId_);
    return (it != nodes_.end()) ? &it->second : nullptr;
}

} // namespace subverse
