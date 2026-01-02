#include "dialogue_system.h"

namespace subverse {

void DialogueSystem::setText(const std::string& speaker, const std::string& text) {
    currentLine_.speaker = speaker;
    currentLine_.text = text;
    currentText_ = text;
}

void DialogueSystem::setChoices(const std::vector<Choice>& choices) {
    choices_ = choices;
}

void DialogueSystem::clearChoices() {
    choices_.clear();
}

} // namespace subverse
