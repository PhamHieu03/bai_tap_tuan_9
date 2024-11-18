#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

// Node để lưu thông tin của file
struct FileNode {
    string fileName;
    double fileSize; // Đơn vị: MB
    time_t creationTime; // Thời gian tạo file
    FileNode* next;

    FileNode(string name, double size, time_t time)
        : fileName(name), fileSize(size), creationTime(time), next(nullptr) {}
};

// Danh sách liên kết đơn
class FileList {
private:
    FileNode* head;

public:
    FileList() : head(nullptr) {}

    // Hàm chèn file theo thứ tự thời gian
    void insertFile(const string& name, double size, time_t time) {
        FileNode* newNode = new FileNode(name, size, time);

        if (!head || head->creationTime > time) {
            newNode->next = head;
            head = newNode;
        }
        else {
            FileNode* current = head;
            while (current->next && current->next->creationTime <= time) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Tính tổng kích thước các file
    double calculateTotalSize() const {
        double totalSize = 0.0;
        FileNode* current = head;
        while (current) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    // In danh sách file
    void displayFiles() const {
        FileNode* current = head;
        cout << "Danh sách file trong thư mục:\n";
        while (current) {
            cout << "Tên file: " << current->fileName
                << ", Kích thước: " << current->fileSize << " MB"
                << ", Thời gian tạo: " << asctime(localtime(&current->creationTime));
            current = current->next;
        }
    }

    // Xóa các file nhỏ nhất để giảm kích thước tổng xuống dưới 32GB
    void removeSmallestFiles(double maxSizeMB) {
        while (calculateTotalSize() > maxSizeMB) {
            FileNode* prev = nullptr, * current = head, * minNode = head, * minPrev = nullptr;

            // Tìm file nhỏ nhất
            while (current) {
                if (current->fileSize < minNode->fileSize) {
                    minPrev = prev;
                    minNode = current;
                }
                prev = current;
                current = current->next;
            }

            // Xóa file nhỏ nhất
            if (minPrev) {
                minPrev->next = minNode->next;
            }
            else {
                head = minNode->next;
            }
            cout << "Đã xóa file: " << minNode->fileName << ", Kích thước: " << minNode->fileSize << " MB\n";
            delete minNode;
        }
    }
};

int main() {
    FileList folder;

    // Thêm các file vào danh sách
    time_t now = time(0);
    folder.insertFile("File1.txt", 500, now - 60);
    folder.insertFile("File2.txt", 700, now - 120);
    folder.insertFile("File3.txt", 300, now - 30);
    folder.insertFile("File4.txt", 1200, now - 90);

    folder.displayFiles();

    cout << "\nTổng kích thước thư mục: " << folder.calculateTotalSize() << " MB\n";

    // Giả sử USB có kích thước 32GB = 32768 MB
    double maxUSBSize = 32768;
    folder.removeSmallestFiles(maxUSBSize);

    cout << "\nDanh sách file sau khi loại bỏ:\n";
    folder.displayFiles();

    return 0;
}
