import time


# Функция для однопоточного выполнения
def single_threaded_version(file_path):
    # Начало замера времени
    start_time = time.time()

    # Чтение данных из файла с явной кодировкой cp1251
    with open(file_path, 'r', encoding='cp1251') as file:
        words = [line.strip() for line in file]

    # Находим самое длинное слово
    longest_word = ""
    for word in words:
        if len(word) > len(longest_word):
            longest_word = word

    # Подсчет количества слов
    word_count = len(words)

    # Подсчет частоты символов в самом длинном слове
    letter_frequency = {}
    for letter in longest_word:
        if letter in letter_frequency:
            letter_frequency[letter] += 1
        else:
            letter_frequency[letter] = 1

    # Конец замера времени
    end_time = time.time()

    # Вывод результатов
    print(f"Самое длинное слово: {longest_word}")
    print(f"Количество слов: {word_count}")
    print("Частота букв в самом длинном слове:")
    for letter, freq in letter_frequency.items():
        print(f"{letter}: {freq}")

    # Подсчет и вывод времени выполнения
    execution_time1 = end_time - start_time
   
    return (execution_time1)
