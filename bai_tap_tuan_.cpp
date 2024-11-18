#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

// Cấu trúc node lưu từng từ trong danh sách liên kết
struct WordNode {
    string word;       // Từ
    WordNode* next;    // Con trỏ đến node tiếp theo

    WordNode(string w) : word(w), next(nullptr) {}
};

// Danh sách liên kết đơn
class WordList {
private:
    WordNode* head;

public:
    WordList() : head(nullptr) {}

    // Hàm thêm từ vào danh sách liên kết
    void addWord(const string& word) {
        WordNode* newNode = new WordNode(word);

        if (!head) {
            head = newNode;
        }
        else {
            WordNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Hàm hiển thị các từ trong danh sách
    void displayWords() const {
        WordNode* current = head;
        cout << "Câu hiện tại:\n";
        while (current) {
            cout << current->word << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Tìm từ xuất hiện nhiều nhất
    string findMostFrequentWord() const {
        unordered_map<string, int> wordCount;
        WordNode* current = head;

        // Đếm số lần xuất hiện của từng từ
        while (current) {
            wordCount[current->word]++;
            current = current->next;
        }

        // Tìm từ xuất hiện nhiều nhất
        string mostFrequentWord;
        int maxCount = 0;
        for (const auto& pair : wordCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequentWord = pair.first;
            }
        }

        return mostFrequentWord;
    }

    // Xóa từ láy
    void removeRedundantRepeats() {
        WordNode* current = head;

        while (current && current->next) {
            if (current->word == current->next->word) {
                WordNode* redundantNode = current->next;
                current->next = current->next->next;
                delete redundantNode;
            }
            else {
                current = current->next;
            }
        }
    }

    // Đếm số từ vựng (không trùng lặp)
    int countUniqueWords() const {
        unordered_map<string, bool> uniqueWords;
        WordNode* current = head;

        while (current) {
            uniqueWords[current->word] = true;
            current = current->next;
        }

        return uniqueWords.size();
    }
};

int main() {
    WordList sentence;

    // Thêm từ vào danh sách (câu mẫu)
    sentence.addWord("xanh");
    sentence.addWord("xanh");
    sentence.addWord("trời");
    sentence.addWord("cao");
    sentence.addWord("cao");
    sentence.addWord("xanh");

    cout << "Câu ban đầu:\n";
    sentence.displayWords();

    // Tìm từ xuất hiện nhiều nhất
    string mostFrequentWord = sentence.findMostFrequentWord();
    cout << "\nTừ xuất hiện nhiều nhất: " << mostFrequentWord << endl;

    // Loại bỏ từ láy
    cout << "\nLoại bỏ từ láy...\n";
    sentence.removeRedundantRepeats();
    sentence.displayWords();

    // Đếm số từ vựng (không trùng lặp)
    int uniqueWordCount = sentence.countUniqueWords();
    cout << "\nSố từ vựng không trùng lặp: " << uniqueWordCount << endl;

    return 0;
}
