#pragma once
#include <string>
#include <vector>

namespace subverse {

struct DialogueLine {
    std::string speaker;
    std::string text;
};

struct Choice {
    std::string text;
    std::string target;
};

class DialogueSystem {
public:
    void setText(const std::string& speaker, const std::string& text);
    void setChoices(const std::vector<Choice>& choices);
    void clearChoices();
    
    bool hasText() const { return !currentText_.empty(); }
    bool hasChoices() const { return !choices_.empty(); }
    
    const DialogueLine& getCurrentLine() const { return currentLine_; }
    const std::vector<Choice>& getChoices() const { return choices_; }
    
private:
    DialogueLine currentLine_;
    std::string currentText_;
    std::vector<Choice> choices_;
};

} // namespace subverse
