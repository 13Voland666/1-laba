// single_threaded_version.h
#ifndef SINGLE_THREADED_VERSION_H
#define SINGLE_THREADED_VERSION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <locale>

// single_threaded_version.cpp
#include "single_threaded_version.h"

int single_threaded_version(const std::string& file_path) {
    // ������������� ������ ��� ����������� ����������� ���������
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    // ������ ������ �������
    auto start_time = std::chrono::high_resolution_clock::now();

    // ������ ������ �� �����
    std::vector<std::string> words;
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::wcerr << L"�� ������� ������� ����: " << file_path.c_str() << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        words.push_back(line);
    }
    file.close();

    // ����� ������ �������� �����
    std::string longest_word;
    for (const auto& word : words) {
        if (word.length() > longest_word.length()) {
            longest_word = word;
        }
    }

    // ������� ���������� ����
    int word_count = words.size();

    // ������� ������� �������� � ����� ������� �����
    std::unordered_map<char, int> letter_frequency;
    for (char letter : longest_word) {
        letter_frequency[letter]++;
    }

    // ����� ������ �������
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> execution_time = end_time - start_time;

    // ����� �����������
    std::wcout << L"����� ������� �����: " << longest_word.c_str() << std::endl;
    std::wcout << L"���������� ����: " << word_count << std::endl;
    std::wcout << L"������� ���� � ����� ������� �����:" << std::endl;
    for (const auto& pair : letter_frequency) {
        std::wcout << pair.first << L": " << pair.second << std::endl;
    }

    // ����� ������� ����������
    std::wcout << L"\n����� ���������� ��������� (�����������): " << execution_time.count() << L" ������" << std::endl;

    return 0;
}
