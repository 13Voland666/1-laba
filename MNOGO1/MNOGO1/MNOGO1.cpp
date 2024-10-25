#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <mutex>
#include <locale>

std::mutex mtx;

// Функция для нахождения самого длинного слова
void find_longest_word(const std::vector<std::string>& words, std::string& longest_word) {
    for (const auto& word : words) {
        if (word.length() > longest_word.length()) {
            longest_word = word;
        }
    }
}

// Функция для подсчета количества слов
void count_words(const std::vector<std::string>& words, int& word_count) {
    word_count = words.size();
}

// Функция для подсчета частоты символов в самом длинном слове
void count_letter_frequency(const std::string& longest_word, std::unordered_map<char, int>& letter_frequency) {
    for (char letter : longest_word) {
        std::lock_guard<std::mutex> lock(mtx); // Защита от одновременного доступа
        letter_frequency[letter]++;
    }
}

int main() {
    // Устанавливаем локаль для корректного отображения кириллицы
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    std::string file_path = "X:\\Politex\\mnogopotok\\1 laba\\data.txt";
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::wcerr << L"Не удалось открыть файл: " << file_path.c_str() << std::endl;
        return 1;
    }

    // Чтение данных из файла
    std::vector<std::string> words;
    std::string line;
    while (std::getline(file, line)) {
        words.push_back(line);
    }
    file.close();

    // Переменные для результатов
    std::string longest_word;
    int word_count = 0;
    std::unordered_map<char, int> letter_frequency;

    // Начало замера времени
    auto start_time = std::chrono::high_resolution_clock::now();

    // Создание и запуск потоков для выполнения разных задач
    std::thread thread1(find_longest_word, std::ref(words), std::ref(longest_word));
    std::thread thread2(count_words, std::ref(words), std::ref(word_count));

    // Ожидание завершения первого потока, чтобы использовать результат в третьем потоке
    thread1.join();

    // Запуск третьего потока для подсчета частоты символов
    std::thread thread3(count_letter_frequency, std::ref(longest_word), std::ref(letter_frequency));

    // Ожидание завершения всех потоков
    thread2.join();
    thread3.join();

    // Конец замера времени
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> execution_time = end_time - start_time;

    // Вывод результатов
    std::wcout << L"Самое длинное слово: " << longest_word.c_str() << std::endl;
    std::wcout << L"Количество слов: " << word_count << std::endl;
    std::wcout << L"Частота букв в самом длинном слове:" << std::endl;
    for (const auto& pair : letter_frequency) {
        std::wcout << pair.first << L": " << pair.second << std::endl;
    }

    // Вывод времени выполнения
    std::wcout << L"\nВремя выполнения программы (многопоточно): " << execution_time.count() << L" секунд" << std::endl;

    return 0;
}
